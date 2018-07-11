
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

double PI = 3.14159265358979323846;

int w ,h;

double tileSize;

double toRadian(double a){
    return a / 180.0 * PI;
}


double* spherical2cartesian(double the, double phi){

    double x = sin(phi)*cos(the);
    double y = sin(phi)*sin(the);
    double z = cos(phi);

    double *temp = new double[3];
    temp[0] = x;
    temp[1] = y;
    temp[2] = z;

    return temp;
}


double* spherical2coordinates(double the, double phi){

    double i,j;

    if(the > PI){
        i = (the - PI) /2/PI *w;
    }
    else{
        i = (PI + the)/2/PI * w;
    }

    j = phi /  PI * h;

    double *result = new double[2];
    result [0] = i;
    result [1] = j;

    return result;
}

//double* cartesian2coordinates(double x, double y, double z){
//
//    double the;
//
//    if(x != 0) {
//        the = atan2(y,x);
//
//    } else {
//        the = toRadian(90);
//    }
//
//    double phi = acos(z);
//    return spherical2coordinates(the,phi);
//}


double* cartesian2spherical(double x, double y, double z){

    double the;

    if(x != 0) {
        the = atan2(y,x);

    } else {
        the = toRadian(90);
    }

    double phi = acos(z);

    double *result = new double[2];
    result [0] = the;
    result [1] = phi;

    return result;
}
void matrixMultiplication(double* vector, double matrix[3][3], double res[3]) {

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            res[i] += matrix[i][j] * vector[j];
        }
    }

}

void biLinearInterpolation(Mat image,Mat fov,double i,double j) {

    Vec3b p1 = image.at<Vec3b>(j,i);
    Vec3b p2 = image.at<Vec3b>(j+1,i);
    Vec3b p3 = image.at<Vec3b>(j +1 ,i +1);
    Vec3b p4 = image.at<Vec3b>(j,i+1);
    fov.at<Vec3b>(i, j) = 0.25*(p1 + p2 + p3 + p4);
}
/*
double computeR(double the) {
    double r;
    if()
    double r = tileSize / (2 * cos(the));
    printf("r:%f\n", r);
    return r;

}
*/
double* findPixel(int index, double x,double y) {

    int vertical;
    if (index > 2) {
        vertical = 1;
    }
    else {
        vertical = 0;
    }
    double n = (tileSize * (index%3))  + y * tileSize;
    double m = (tileSize * vertical) + x * tileSize;

    //printf("index: %d,x:%lf,y:%lf\n",index,x, y);
    //printf("n:%lf,m:%lf\n",n, m);
    double *result = new double[2];
    result [0] = n;
    result [1] = m;

    return result;
}

double* convert_xyz_to_cube_uv(double x, double y, double z) {

    double absX = fabs(x);
    double absY = fabs(y);
    double absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    double maxAxis, uc, vc;

    int index;
    // POSITIVE X
    if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -z;
        vc = y;
        index = 0;
    }
    // NEGATIVE X
    if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = z;
        vc = y;
        index = 1;
    }
    // POSITIVE Y
    if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        maxAxis = absY;
        uc = x;
        vc = -z;
        index = 2;
    }
    // NEGATIVE Y
    if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        maxAxis = absY;
        uc = x;
        vc = z;
        index = 3;
    }
    // POSITIVE Z
    if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = x;
        vc = y;
        index = 2;
    }
    // NEGATIVE Z
    if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = -x;
        vc = y;
        index = 3;
    }

    // Convert range from -1 to 1 to 0 to 1
    double u = 0.5f * (uc / maxAxis + 1.0f);
    double v = 0.5f * (vc / maxAxis + 1.0f);

    return findPixel(index, u, v);
}

int main(int argc, char** argv ) {

    int option = 1;

	//load image
    Mat image = imread("cube.jpg", CV_LOAD_IMAGE_COLOR);

	//get width and height
    w = image.cols;
    h = image.rows;
    tileSize = w/3.0;
	//parameters for FoV
    int fovX = 90,fovY = 60,fw = w/4.0 +1,fh = h/3.0+1;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    double hp = 45,ht = 0;
    double htr = toRadian(ht);
    double hpr = toRadian(hp);

	//rotation matrices
    double rot_y [3][3] = {
        {cos(hpr), 0, -sin(hpr)},
        {0, 1, 0},
        {sin(hpr), 0, cos(hpr)}
    };

//    double rot_x [3][3] = {
//            {1, 0, 0},
//            {0, cos(htr), -sin(htr)},
//            {0, sin(htr), cos(htr)}
//    };
    double rot_z [3][3] = {
        {cos(htr), sin(htr), 0},
        {-sin(htr), cos(htr), 0},
        {0, 0, 1}
    };

	//initialize fov image
    Mat fov(fh, fw, CV_8UC3, Scalar(0, 0, 0));

    int a = 0, b = 0;

    for (double i = 90  - fovY/2.0; i < 90 + fovY/2.0; i+= fovY*1.0/fh, b++) {

        for (double j = -fovX/2.0; j < fovX/2.0; j+= fovX*1.0/fw, a++) {

            //rotation along y axis
            double p2[] = {0.0, 0.0, 0.0};
            matrixMultiplication(spherical2cartesian(toRadian((j < 0) ? j + 360 : j), toRadian((i < 0) ? i + 180 : i)),
                                 rot_y, p2);

            //rotate along z axis
            double p3[] = {0.0, 0.0, 0.0};
            matrixMultiplication(p2, rot_z, p3);

//            double *spherical = cartesian2spherical(p3[0], p3[1], p3[2]);
//
//            if (option == 0) {
//
//                //convert 3D catesian to 2d coordinates
//                double *res = spherical2coordinates(spherical[0],spherical[1]);
//
//                //assign the pixel value
//                Point temp = Point((int) (res[1]), (int) (res[0]));
//                fov.at<Vec3b>(Point(a, b)) = image.at<Vec3b>(temp.x, temp.y);
//            }
//            else{
               // printf("a:%d,b:%d\n",a,b);
		        //printf("X: %lf,Y: %lf,Z:%lf\n",p3[0],p3[1],p3[2]);
                double *temp = convert_xyz_to_cube_uv(p3[0], p3[1], p3[2]);
                printf("tempX: %d, tempY:%d\n",(int)(temp[0]),(int)(temp[1]));
                fov.at<Vec3b>(Point(a, b)) = image.at<Vec3b>((int)(temp[1]), (int)(temp[0]));

//            }
        }
        a=0;
    }

	//save the fov image
    imwrite("fov.jpg", fov);
    fov.release();

    return 0;


}

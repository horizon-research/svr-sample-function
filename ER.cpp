
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

double PI = 3.14159265358979323846;

int w ,h;

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

double* cartesian2coordinates(double x, double y, double z){

    double the;

    if(x != 0) {
        the = atan2(y,x);

    } else {
        the = toRadian(90);
    }

    double phi = acos(z);
    return spherical2coordinates(the,phi);
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

int main(int argc, char** argv ) {

	//load image
    Mat image = imread("360.jpg", CV_LOAD_IMAGE_COLOR);

	//get width and height
    w = image.cols;
    h = image.rows;

	//parameters for FoV
    int fovX = 90,fovY = 60,fw = w/4.0,fh = h/3.0;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    double hp = 90,ht = 0;
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
			double p2[] = { 0.0,0.0,0.0 };
			matrixMultiplication(spherical2cartesian(toRadian((j < 0) ? j + 360 : j), toRadian((i < 0) ? i + 180 : i)), rot_y, p2);

			//rotate along z axis
			double p3[] = { 0.0,0.0,0.0 };
			matrixMultiplication(p2,rot_z,p3);

			//convert 3D catesian to 2d coordinates
           		double *res = cartesian2coordinates(p3[0],p3[1],p3[2]);

			//assign the pixel value
			Point temp = Point((int)(res[1]), (int)(res[0]));
            		fov.at<Vec3b>(Point(a,b)) = image.at<Vec3b>(temp.x, temp.y);
        }
        a=0;
    }

	//save the fov image
    imwrite("fov.jpg", fov);

    return 0;


}


#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>

using namespace cv;

double PI = 3.14159265358979323846;

int w ,h;

double tileSize;
double tileSizeX,tileSizeY;


double toRadian(double a){
    return a / 180.0 * PI;
}

int nearestNeighbor(double num){

	int res = (int)(num + 0.5);
	return res;
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
        i = (the - PI) /2.0/PI *w;
    }
    else{
        i = (PI + the)/2.0/PI * w;
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


double* findPixel(int index, double x,double y) {
   // printf("Index:%d\n",index);
    int vertical;
    if (index > 2) {
        vertical = 1;
    }
    else {
        vertical = 0;
    }
    double n = (tileSize * (index%3))  + y * tileSize;
    double m = (tileSize * vertical) + x * tileSize;

    double *result = new double[2];
    result [0] = n;
    result [1] = m;

    return result;
}


//from wikipedia: https://en.wikipedia.org/wiki/Cube_mapping
double* convert_xyz_to_cube_uv(double x, double y, double z) {
    double theta;

    if(x != 0) {
        theta = atan2(y,x)/ PI * 180.0;

    } else {
        theta = 90;
    }

    double phi = acos(z)/ PI * 180.0;
    //printf("Theta:  %lf , Phi: %lf\n", theta,phi);
    double absX = fabs(x);
    double absY = fabs(y);
    double absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    double maxAxis, uc, vc;
    double u,v;
    int index;
    // POSITIVE X
    if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -z;
        vc = y;
        index = 4;
    }
        // NEGATIVE X
    else if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -z;
        vc = -y;
        index = 5;
        //printf("Index: %d,X: %lf,Y: %lf,Z:%lf\n",index,x,y,z);
    }
        // POSITIVE Y
    else if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        maxAxis = absY;
        uc = -z;
        vc = -x;
        index = 1;
        //printf("Index: %d,X: %lf,Y: %lf,Z:%lf\n",index,x,y,z);
    }
        // NEGATIVE Y
    else  if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        maxAxis = absY;
        uc = -z;
        vc = x;
        index = 0;
        //printf("Index: %d,X: %lf,Y: %lf,Z:%lf\n",index,x,y,z);
    }
        // POSITIVE Z
    else  if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = x;
        vc = y;
        index = 2;
    }
        // NEGATIVE Z
    else  if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = -x;
        vc = y;
        index = 3;
        //printf("Index: %d,X: %lf,Y: %lf,Z:%lf\n",index,x,y,z);
    }
    //printf("%d,%lf,%lf\n",index,theta,phi);
    // Convert range from -1 to 1 to 0 to 1
    u = 0.5f * (uc / maxAxis + 1.0f);
    v = 0.5f * (vc / maxAxis + 1.0f);
	
    return findPixel(index, u, (1-v));
}

double* findPixel_EAC(int index, double u, double v){
    //printf("Index: %d\n", index);
    //printf("U: %lf, V: %lf\n",u,v);
    double *result = new double[2];
    double n,m;
    if(index <= 2){

        n = (tileSizeX * (index%3))  + u * tileSizeX;
	    m = v * tileSizeY;

    }
    else{

        switch(index){
            case 3:
                n = u * tileSizeX;
                m = tileSizeY + (1 - v) * tileSizeY;
                break;

            case 4:
                n = tileSizeX + (1 - v) * tileSizeX;
                m = tileSizeY + (1 - u) * tileSizeY;
                break;

            case 5:
                n = tileSizeX * 2  +  u * tileSizeX;
                m = tileSizeY  + (1 - v) * tileSizeY;
                break;
        }
    } 
    result[0] = n;
    result[1] = m;
    //printf("Tile: %lf, %lf\n",tileSizeX,tileSizeY);
    //printf("N: %lf, M: %lf\n",result[0], result[1]);
    return result;
}
double* convert_EAC(double x, double y, double z){
    double absX = fabs(x);
    double absY = fabs(y);
    double absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    double u = 0,v = 0;
    int index;

    double theta;

    if(x != 0) {
        theta = atan2(y,x)/ PI * 180.0;

    } else {
        theta = 90;
    }

    double phi = acos(z)/ PI * 180.0;

    // Front
    if (isXPositive && absX >= absY && absX >= absZ) {
        index = 1;
        v = (phi - 45)/90.0;
        u = (theta + 45)/90.0;


    }
    // Back
    else if (!isXPositive && absX >= absY && absX >= absZ) {
        // 135 -180 -135 - -180
        index = 4;
        v = (phi - 45)/90.0;
        if(theta < 0){
            u = (theta +135)/-90.0;
        }
        else{
            u = 0.5 + (180 - theta)/90.0;
        }

    }
    // Left
    else if (isYPositive && absY >= absX && absY >= absZ) {

        index = 2;
        v = (phi - 45)/90.0;

        u = (theta - 45)/90.0;

    }
    // Right
    else  if (!isYPositive && absY >= absX && absY >= absZ) {

        index = 0;
        v = (phi - 45)/90.0;
        u = (theta + 135)/90.0;
    }
    // Up
    else  if (isZPositive && absZ >= absX && absZ >= absY) {

        index = 5;
//        u = (theta + 180)/360;
//        v = phi / 55.0;

    }
    // Down
    else  if (!isZPositive && absZ >= absX && absZ >= absY) {

        index = 3;

//        u = (theta + 180)/360;
//        v = (phi - 125) / 55.0;
       
    }

    //printf("Index: %d,X: %lf,Y: %lf,Z:%lf\n",index,x,y,z);

    return findPixel_EAC(index,u,v);

}


int main(int argc, char** argv) {

    int option = argv[3][0] - '0';
    // load image
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    // get width and height
    w = image.cols;
    h = image.rows;
    tileSize = w/3.0;
    tileSizeX = w/3.0;
    tileSizeY = h/2.0;

    // parameters for FoV
    int fovX = 90,fovY = 90,fw = 388 ,fh = 310;
    if(option == 0){
        fh = h*(fovY/180.0);
    }

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    // both are relative rotation angles
    double hp = atof(argv[5]),ht = atof(argv[4]);
    // convert to radian
    double htr = toRadian(ht);
    double hpr = toRadian(hp);

    // rotation matrices
    double rot_y [3][3] = {
            {cos(hpr), 0, -sin(hpr)},
            {0, 1, 0},
            {sin(hpr), 0, cos(hpr)}
    };

    double rot_z [3][3] = {
            {cos(htr), sin(htr), 0},
            {-sin(htr), cos(htr), 0},
            {0, 0, 1}
    };

    // initialize fov image
    Mat fov(fh, fw, CV_8UC3, Scalar(0, 0, 0));

    int a = 0, b = 0;
    // default head orientation is 0,90
    for (double i = 90  - fovY/2.0; i < 90 + fovY/2.0; i+= fovY*1.0/fh, b++) {
        for (double j = -fovX/2.0; j < fovX/2.0; j+= fovX*1.0/fw, a++) {

            // rotation along y axis
            double p2[] = {0.0, 0.0, 0.0};
            matrixMultiplication(spherical2cartesian(toRadian((j < 0) ? j + 360 : j), toRadian((i < 0) ? i + 180 : i)),
                                 rot_y, p2);

            // rotate along z axis
            double p3[] = {0.0, 0.0, 0.0};
            matrixMultiplication(p2, rot_z, p3);
            double *res;
            if (option == 0) {
                //printf("ER\n");
                // convert 3D catesian to 2D coordinates
                res = cartesian2coordinates(p3[0], p3[1], p3[2]);


            }
            else if(option == 1){
                //printf("CUBEMAP\n");
            // convert 3D catesian to cube UVs
                res = convert_xyz_to_cube_uv(p3[0], p3[1], p3[2]);

            }
            else {
                // printf("EAC\n");
                 res = convert_EAC(p3[0], p3[1], p3[2]);
                //convert_EAC(p3[0], p3[1], p3[2]);
            }


            // assign the pixel value
            fov.at<Vec3b>(Point(a, b)) = image.at<Vec3b>(nearestNeighbor (res[1]), nearestNeighbor (res[0]));

        }
        a=0;
    }

    // save the fov image
    imwrite(argv[2], fov);

    return 0;


}

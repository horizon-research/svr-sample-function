
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <math.h>

using namespace cv;
using namespace std;

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

void spherical2cartesian(double the, double phi, double result[3]){

    double x = sin(phi) * cos(the);
    double y = sin(phi) * sin(the);
    double z = cos(phi);


    result[0] = x;
    result[1] = y;
    result[2] = z;

}


void spherical2coordinates(double the, double phi, double result[2]){

    double i,j;

    if(the > PI){
        i = (the - PI) / 2.0 / PI * w;
    }
    else{
        i = (PI + the) / 2.0 / PI * w;
    }

    j = phi / PI * h;

    result [0] = i;
    result [1] = j;
}

void cartesian2coordinates(double x, double y, double z, double result[2]){

    double the;

    if(x != 0) {
        the = atan2(y, x);

    } else {
        the = toRadian(90.0);
    }

    double phi = acos(z);

    spherical2coordinates(the, phi, result);
}


void matrixMultiplication(double* vector, double matrix[3][3], double res[3]) {

    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {

            res[i] += matrix[i][j] * vector[j];

        }
    }

}


void findPixel(int index, double x,double y, double result[2]) {

    int vertical;

    if (index > 2) {
        vertical = 1;
    }
    else {
        vertical = 0;
    }

    double n = (tileSize * (index % 3))  + y * tileSize;
    double m = (tileSize * vertical) + x * tileSize;

    result [0] = n;
    result [1] = m;

}

void convert_cube_uv_to_xyz(int index, double u, double v, double cartesian[3]){
  // convert range 0 to 1 to -1 to 1
  double uc = 2.0f * u - 1.0f;
  double vc = 2.0f * v - 1.0f;

  double x = 0,y = 0,z = 0;

  switch (index){

    case 4: x =  1.0f; y =    vc; z =   -uc; break;  // POSITIVE X
    case 5: x = -1.0f; y =   -vc; z =   -uc; break;  // NEGATIVE X
    case 1: x =   -vc; y =  1.0f; z =   -uc; break;  // POSITIVE Y
    case 0: x =    vc; y = -1.0f; z =   -uc; break;  // NEGATIVE Y
    case 2: x =    uc; y =    vc; z =  1.0f; break;  // POSITIVE Z
    case 3: x =   -uc; y =    vc; z = -1.0f; break;  // NEGATIVE Z

  }

  double xp = x * sqrt(1 - y*y/2.0 - z*z/2.0 + y*y*z*z/3.0);
  double yp = y * sqrt(1 - z*z/2.0 - x*x/2.0 + z*z*x*x/3.0);
  double zp = z * sqrt(1 - x*x/2.0 - y*y/2.0 + x*x*y*y/3.0);

  cartesian[0] = xp;
  cartesian[1] = yp;
  cartesian[2] = zp;

}

//from wikipedia: https://en.wikipedia.org/wiki/Cube_mapping
void convert_xyz_to_cube_uv(double x, double y, double z, double result[2]) {

    double maxAxis, uc, vc;
    double u, v;
    int index;

    double absX = fabs(x);
    double absY = fabs(y);
    double absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;


    // POSITIVE X
    // Front
    if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        index = 4;
        maxAxis = absX;
        uc = -z;
        vc = y;

    }

    // NEGATIVE X
    // Back
    else if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        index = 5;
        maxAxis = absX;
        uc = -z;
        vc = -y;

    }

    // POSITIVE Y
    // Left
    else if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        index = 1;
        maxAxis = absY;
        uc = -z;
        vc = -x;

    }

    // NEGATIVE Y
    // Right
    else  if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        index = 0;
        maxAxis = absY;
        uc = -z;
        vc = x;

    }

    // POSITIVE Z
    // Up
    else  if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        index = 2;
        maxAxis = absZ;
        uc = x;
        vc = y;

    }

    // NEGATIVE Z
    // Down
    else  if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y

        index = 3;
        maxAxis = absZ;
        uc = -x;
        vc = y;

    }

    // Convert range from -1 to 1 to 0 to 1
    u = 0.5f * (uc / maxAxis + 1.0f);
    v = 0.5f * (vc / maxAxis + 1.0f);
	
    findPixel(index, u, (1 - v), result);
}

// void findPixel_EAC(int index, double u, double v, double result[2]){

//     double n,m;

//     // Left Front Right
//     if(index <= 2){

//         n = (tileSizeX * (index % 3))  + v * tileSizeX;
// 	    m = u * tileSizeY;

//     }
//     // Down Back Up
//     else{

//         switch(index){
//             case 3:
//                 n = u * tileSizeX;
//                 m = tileSizeY + (1 - v) * tileSizeY;
//                 break;

//             case 4:
//                 n = tileSizeX + (1 - u) * tileSizeX + 1;
//                 m = tileSizeY + v * tileSizeY + 1;
//                 break;

//             case 5:
//                 n = tileSizeX * 2.0f  +  u * tileSizeX;
//                 m = tileSizeY  + (1 - v) * tileSizeY;
//                 break;
//         }
//     }
//     result[0] = n - 1;
//     result[1] = m - 1;

// }

// void convert_EAC(double x, double y, double z, double result[2]){

//     double maxAxis, uc, vc;
//     double u, v;
//     int index;

//     double absX = fabs(x);
//     double absY = fabs(y);
//     double absZ = fabs(z);

//     int isXPositive = x > 0 ? 1 : 0;
//     int isYPositive = y > 0 ? 1 : 0;
//     int isZPositive = z > 0 ? 1 : 0;

//     // Front
//     if (isXPositive && absX >= absY && absX >= absZ) {

//         index = 1;
//         maxAxis = absX;
//         uc = -z;
//         vc = y;

//     }
//     // Back
//     else if (!isXPositive && absX >= absY && absX >= absZ) {

//         index = 4;
//         maxAxis = absX;
//         uc = -z;
//         vc = -y;

//     }
//     // Left
//     else if (isYPositive && absY >= absX && absY >= absZ) {

//         index = 2;
//         maxAxis = absY;
//         uc = -z;
//         vc = -x;

//     }
//     // Right
//     else if (!isYPositive && absY >= absX && absY >= absZ) {

//         index = 0;
//         maxAxis = absY;
//         uc = -z;
//         vc = x;

//     }
//     // Up
//     else if (isZPositive && absZ >= absX && absZ >= absY) {

//         index = 5;
//         maxAxis = absZ;
//         uc = x;
//         vc = y;

//     }
//     // Down
//     else if (!isZPositive && absZ >= absX && absZ >= absY) {

//         index = 3;
//         maxAxis = absZ;
//         uc = -x;
//         vc = y;

//     }


//     u = 2.0f * atan((uc / maxAxis))/PI + 0.5f;
//     v = 2.0f * atan((vc / maxAxis))/PI + 0.5f;

//     findPixel_EAC(index,u,v, result);

// }

void cube2uv(int x,int y, double result[3]) {

    int xc = (x / tileSize) < 3 ? (x / tileSize) : 2;

    int yc = (y / tileSize) < 2 ? (y / tileSize) : 1;

    double index = 0;

    if(yc > 0){
        index = xc + 3;
    }
    else{
        index = xc;
    }

    double v = (x - xc * tileSize) / (1.0 * tileSize);
    double u = (y - yc * tileSize) / (1.0 * tileSize);

    result[0] = index;
    result[1] = u;
    result[2] = v;

}


int main(int argc, char** argv) {

	// ofstream myfile;
 // 	myfile.open ("indices.txt");

    // load image
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    // Mat pat = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    // get width and height
    w = image.cols;
    h = image.rows;
    tileSize = w/3.0;
    tileSizeX = w/3.0;
    tileSizeY = h/2.0;

    // parameters for FoV
    int fovX = 360,fovY = 180,fw = tileSize*3,fh = tileSize*2;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    // both are relative rotation angles
    double hp = 0,ht = 0;

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
    Mat fov(tileSize*2, tileSize*3, CV_8UC3);

    int index = 0;

    for(int b = 0; b < fw; b++){
        for(int a = 0; a < fh; a++){


            // printf("NEXT ROUND\n");
            double uvs[] = {0.0, 0.0, 0.0};

            cube2uv(b, a, uvs);

            //printf("UV: %lf %lf %lf\n", uvs[0], uvs[1] ,uvs[2]);

            double cartesian[] = {0.0, 0.0, 0.0};

            convert_cube_uv_to_xyz((int)(uvs[0]), uvs[1] ,uvs[2], cartesian);

            // printf("Cartesian: %lf %lf %lf\n", cartesian[0], cartesian[1], cartesian[2]);

            double res[] = {0.0, 0.0};

            cartesian2coordinates(cartesian[0], cartesian[1], cartesian[2], res);

            // printf("Res: %lf %lf \n", res[0], res[1]);

            fov.at<Vec3b>(a,b) = image.at<Vec3b>(nearestNeighbor (res[1]), nearestNeighbor (res[0]));   

            // printf("Res(Int): %d %d \n",nearestNeighbor (res[0]), nearestNeighbor (res[1]));

        }
    }
    // save the fov image
    imwrite("cubeMap.jpg", fov);


    return 0;


}

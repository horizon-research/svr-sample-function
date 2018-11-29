
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace cv;

double PI = 3.14159265358979323846;

int w, h;
double hp,ht;

double tileSize;
double tileSizeX, tileSizeY;
int fovX = 90, fovY = 90, fw,fh;
int count = 0;


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
    //printf("x: %lf, y:%lf, z:%lf\n",x, y, z);
}

void spherical2coordinates(double the, double phi, double result[2]){

    double i, j;

    if (the > PI){

        i = (the - PI) / 2.0 / PI * w;

    }
    else{

        i = (PI + the) / 2.0 / PI * w;

    }

    j = phi / PI * h;

    result[0] = i;
    result[1] = j;
}

void cartesian2coordinates(double x, double y, double z, double result[2]){

    double the;

    if (x != 0){

        the = atan2(y, x);

    }
    else{

        the = toRadian(90.0);

    }

    double phi = acos(z);
    spherical2coordinates(the, phi, result);
}

//New approach
void coordinates2spherical(double i, double j, double result[2]){
    double theta, phi;

    if (i >= w / 2.0){

        theta = (2 * i * PI / w) - PI;

    }
    else{

        theta = (2 * i * PI / w) + PI;

    }
    phi = j * PI / h;
    //printf("theta: %lf , phi: %lf\n", theta,phi);
    result[0] = theta;
    result[1] = phi;
}


void cartesian2coordinates_inverse(double x, double y, double z, double result[2]){

    double the;
    // pay atentions to atan2 vs atan
    if (x != 0){

        the = atan2(y, x);

    }
    else{

        the = toRadian(90.0);

    }

    double phi = acos(z);

    the = the / PI * 180.0;
    phi = phi / PI * 180.0;

    //printf("the: %lf, phi: %lf\n", the, phi);
    if(the >= -fovX/2.0 && the <= fovX/2 && phi >= 90 -fovY/2.0 && phi <= 90 +fovY/2.0){
       
	    result[0] = (the + fovX/2.0)* fw /90.0;
        result[1] = (phi -  90  + fovY/2.0) * fh/ 90.0;

        count++;
    }
    else{

        result[0] = 0;
        result[1] = 0;
    }
}


void coordinates2cartesian(double i, double j, double result[3]){

    double angles [] = {0.0, 0.0};

    coordinates2spherical(i, j, angles);

    spherical2cartesian(angles[0],angles[1],result);

}

void matrixMultiplication(double *vector, double matrix[3][3], double res[3]){

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){

            res[i] += matrix[i][j] * vector[j];

        }
    }
}

void findPixel(int index, double x, double y, double result[2]){

    int vertical;

    if (index > 2){

        vertical = 1;

    }
    else{

        vertical = 0;

    }

    double n = (tileSize * (index % 3)) + y * tileSize;
    double m = (tileSize * vertical) + x * tileSize;

    result[0] = n;
    result[1] = m;
}

//from wikipedia: https://en.wikipedia.org/wiki/Cube_mapping
void convert_xyz_to_cube_uv(double x, double y, double z, double result[2]){

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
    if (isXPositive && absX >= absY && absX >= absZ){
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        index = 4;
        maxAxis = absX;
        uc = -z;
        vc = y;

    }

    // NEGATIVE X
    // Back
    else if (!isXPositive && absX >= absY && absX >= absZ){
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        index = 5;
        maxAxis = absX;
        uc = -z;
        vc = -y;

    }

    // POSITIVE Y
    // Left
    else if (isYPositive && absY >= absX && absY >= absZ){
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        index = 1;
        maxAxis = absY;
        uc = -z;
        vc = -x;

    }

    // NEGATIVE Y
    // Right
    else if (!isYPositive && absY >= absX && absY >= absZ){
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        index = 0;
        maxAxis = absY;
        uc = -z;
        vc = x;

    }

    // POSITIVE Z
    // Up
    else if (isZPositive && absZ >= absX && absZ >= absY){
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        index = 2;
        maxAxis = absZ;
        uc = x;
        vc = y;

    }

    // NEGATIVE Z
    // Down
    else if (!isZPositive && absZ >= absX && absZ >= absY){
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

void findPixel_EAC(int index, double u, double v, double result[2]){

    double n, m;

    // Left Front Right
    if (index <= 2){

        n = (tileSizeX * (index % 3)) + v * tileSizeX;
        m = u * tileSizeY;

    }
    // Down Back Up
    else{

        switch (index){

        case 3:
            n = u * tileSizeX;
            m = tileSizeY + (1 - v) * tileSizeY;
            break;

        case 4:
            n = tileSizeX + (1 - u) * tileSizeX + 1;
            m = tileSizeY + v * tileSizeY + 1;
            break;

        case 5:
            n = tileSizeX * 2.0f + u * tileSizeX;
            m = tileSizeY + (1 - v) * tileSizeY;
            break;

        }
    }
    result[0] = n - 1;
    result[1] = m - 1;
}

void convert_EAC(double x, double y, double z, double result[2]){

    double maxAxis, uc, vc;
    double u, v;
    int index;

    double absX = fabs(x);
    double absY = fabs(y);
    double absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    // Front
    if (isXPositive && absX >= absY && absX >= absZ){

        index = 1;
        maxAxis = absX;
        uc = -z;
        vc = y;

    }
    // Back
    else if (!isXPositive && absX >= absY && absX >= absZ){

        index = 4;
        maxAxis = absX;
        uc = -z;
        vc = -y;

    }
    // Left
    else if (isYPositive && absY >= absX && absY >= absZ){

        index = 2;
        maxAxis = absY;
        uc = -z;
        vc = -x;

    }
    // Right
    else if (!isYPositive && absY >= absX && absY >= absZ){

        index = 0;
        maxAxis = absY;
        uc = -z;
        vc = x;

    }
    // Up
    else if (isZPositive && absZ >= absX && absZ >= absY){

        index = 5;
        maxAxis = absZ;
        uc = x;
        vc = y;

    }
    // Down
    else if (!isZPositive && absZ >= absX && absZ >= absY){

        index = 3;
        maxAxis = absZ;
        uc = -x;
        vc = y;

    }

    u = 2.0f * atan((uc / maxAxis)) / PI + 0.5f;
    v = 2.0f * atan((vc / maxAxis)) / PI + 0.5f;

    findPixel_EAC(index, u, v, result);
}

int main(int argc, char **argv){

    //Input:
    //
    //
    //Output:
    //
    
    int option = argv[3][0] - '0';
    // load image
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    //Mat pat = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    // get width and height
    w = image.cols;
    h = image.rows;
    tileSize = w / 3.0;
    tileSizeX = w / 3.0;
    tileSizeY = h / 2.0;

    // parameters for FoV
    fw = w * (fovX / 360.0) + 1, fh = h * (fovY / 360.0) + 1;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    // both are relative rotation angles
    hp = atof(argv[5]), ht = atof(argv[4]);

    if (option == 0){

        fh = h * (fovY / 180.0);
        //hp = (hp / 360.0) * 180.0;
    }

    // convert to radian
    double htr = toRadian(ht);
    double hpr = toRadian(hp);

    // rotation matrices
    double rot_y[3][3] = {
        {cos(hpr), 0, -sin(hpr)},
        {0, 1, 0},
        {sin(hpr), 0, cos(hpr)}};

    double rot_y_inverse[3][3] = {
        {cos(hpr), 0, sin(hpr)},
        {0, 1, 0},
        {-sin(hpr), 0, cos(hpr)}};

    double rot_z[3][3] = {
        {cos(htr), sin(htr), 0},
        {-sin(htr), cos(htr), 0},
        {0, 0, 1}};

    double rot_z_inverse[3][3] = {
        {cos(htr), -sin(htr), 0},
        {sin(htr), cos(htr), 0},
        {0, 0, 1}};


    // initialize fov image
    Mat fov(fh, fw, CV_8UC3);

    //border on the input frame that map to output pixels

    double maxX = -INFINITY;
    double minX = INFINITY;
    double maxY = -INFINITY;
    double minY = INFINITY;



    // default head orientation is 0,90

    int a = 0, b = 0;
    double jT = -fovX / 2.0;
    double jR = fovX / 2.0;
    double jB = -fovX / 2.0;
    double jL = 360 -fovX / 2.0;
    double iT = 90 - fovY / 2.0;
    double iR = 90 - fovY / 2.0;
    double iB = 90 + fovY / 2.0;
    double iL = 90 - fovY / 2.0;

    double i = 0.0;
    double j = 0.0;



    for(int k = 0; k < 2*(fh+fw); k++){

        //Top
        if (k < fw){
            i = iT;
            j = jT;
            jT +=  fovX * 1.0 / fw;
        }

        //Right
        if ((k >= fw) && (k < fw+fh)){
            i = iR;
            j = jR;
            iR += fovY * 1.0 / fh;
        }

        //Bottom
        if ((k >= fw+fh) && (k < 2*fw+fh)){
            i = iB;
            j = jB;
            jB +=  fovX * 1.0 / fw;
        }

        //Left
        if ((k >= 2*fw+fh) && (k < 2*(fw+fh))){
            i = iL;
            j = jL;
            iL += fovY * 1.0 / fh;
        }

        // rotation along y axis
        double p1[] = {0.0, 0.0, 0.0};
        spherical2cartesian(toRadian(j), toRadian((i < 0) ? (i + 180) : i), p1);

        double p2[] = {0.0, 0.0, 0.0};
        matrixMultiplication(p1, rot_y, p2);

        // rotate along z axis
        double p3[] = {0.0, 0.0, 0.0};
        matrixMultiplication(p2, rot_z, p3);

        double res[] = {0.0, 0.0};

        // convert 3D catesian to 2D coordinates
        cartesian2coordinates(p3[0], p3[1], p3[2], res);

        if (b >= fh) break;

        if (minX > res[0]) minX = res[0];
        if (maxX < res[0]) maxX = res[0];
        if (minY > res[1]) minY = res[1];
        if (maxY < res[1]) maxY = res[1];


    }

    if (hp <= -45 || hp >= 315){

        maxY = h;
        maxX = w;
        minX = 0.0;

    }
    if(hp >= 45) {

        minY = 0.0;
        maxX = w;
        minX = 0.0;

    }

    printf("%lf, %lf , %lf, %lf\n", maxX, maxY, minX, minY);
    //for input pixel in the ouput range, calculate the outpout cordinnates
    int x , y;
    int another = 0;

    for (y = 0; y < h; y++){
        for (x = 0; x < w; x++){

            //if pixel map to output get input index 
            if (x <= maxX && x >= minX && y <= maxY && y >= minY){
                another++;
                double cartesian []  ={0.0, 0.0, 0.0};
                coordinates2cartesian(x, y, cartesian);
                
		        double p1[] = {0.0, 0.0, 0.0};
                matrixMultiplication(cartesian, rot_z_inverse , p1);

                // rotate along z axis
                double p2[] = {0.0, 0.0, 0.0};
                matrixMultiplication( p1, rot_y_inverse, p2);


                double res[] = {0.0,0.0};
                cartesian2coordinates_inverse(p2[0], p2[1], p2[2], res);
                fov.at<Vec3b>(nearestNeighbor(res[1]), nearestNeighbor(res[0])) = image.at<Vec3b>(y,x);

            }
        }
    }
    int blackPixels = 0;

    for(int h = 0; h < fh; h++){
        for(int v = 0; v < fw; v++){
            if(fov.at<Vec3b>(h, v)[0] == 0 && fov.at<Vec3b>(h, v)[1] == 0 && fov.at<Vec3b>(h, v)[2] == 0){
                blackPixels++;
                double r = 0, g = 0, b = 0;
                double count = 0;

                if(h - 1 >= 0){
                    r += fov.at<Vec3b>(h - 1, v)[0];
                    g += fov.at<Vec3b>(h - 1, v)[1];
                    b += fov.at<Vec3b>(h - 1, v)[2];
                    count += 1;
                }
                if(h + 1 < fh){
                    r += fov.at<Vec3b>(h + 1, v)[0];
                    g += fov.at<Vec3b>(h + 1, v)[1];
                    b += fov.at<Vec3b>(h + 1, v)[2];
                    count += 1;
                }
                if(v - 1 >= 0){
                    r += fov.at<Vec3b>(h, v - 1)[0];
                    g += fov.at<Vec3b>(h, v - 1)[1];
                    b += fov.at<Vec3b>(h, v - 1)[2];
                    count += 1;
                }
                if(v + 1 < fw){
                    r += fov.at<Vec3b>(h, v + 1)[0];
                    g += fov.at<Vec3b>(h, v + 1)[1];
                    b += fov.at<Vec3b>(h, v + 1)[2];
                    count += 1;
                }

                fov.at<Vec3b>(h, v)[0] = r / count;
                fov.at<Vec3b>(h, v)[1] = g / count;
                fov.at<Vec3b>(h, v)[2] = b / count;

            }
        }
    }

    // save the fov image
    imwrite(argv[2], fov);
    //imwrite("input2.jpg", pat);
    printf("pixels = %d\n",count);
    printf("black pixels = %d\n",blackPixels);
    printf("another = %d\n",another);

    return 0;
}

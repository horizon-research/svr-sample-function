
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
    //printf("X: %f, Y:%f.Z:%f\n",x,y,z);
    return temp;
}

double* coordinates2spherical(int i, int j){

    double the = (i - w/ 2.0) / w  * PI;

    double phi = (j - h / 2.0)/ h * PI;

    //printf("theta: %f, phi:%f\n", the,phi);
    return spherical2cartesian(the,phi);
    // return sphericalr2cartesian(the,phi);
}

double* spherical2coordinates(double the, double phi){

//    double i = the / PI * w + w/2.0;
//    double j = phi / PI * h + h/2.0;
    //printf("the:%lf, phi:%lf \n", the, phi);
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

double* cartesian2coordinates(double l, double m, double n){
    //printf("x: %lf, y %lf , z %lf\n", l,m,n);
    double the;
    if(l != 0) {
        the = atan2(m,l);

    } else {
        the = toRadian(90);
    }

    double phi = acos(n);
    return spherical2coordinates(the,phi);
}


void matrix_x_vector(int n, double* y, double x[3][3], double A[3]) {
    int i, j; // i = row; j = column;
    // Load up A[n][n]
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            A[i] += x[i][j] * y[j];
        }
    }

}

void biInterpolation(Mat image,Mat fov,double i,double j) {
    // printf("i:%f, j %f \n", i,j);
    Vec3b p1 = image.at<Vec3b>(j,i);
    Vec3b p2 = image.at<Vec3b>(j+1,i);
    Vec3b p3 = image.at<Vec3b>(j +1 ,i +1);
    Vec3b p4 = image.at<Vec3b>(j,i+1);
    fov.at<Vec3b>(i, j) = 0.25*(p1 + p2 + p3 + p4);

}

int main(int argc, char** argv ) {
    Mat image = imread("360.jpg", CV_LOAD_IMAGE_COLOR);
    w = image.cols;
    h = image.rows;
    int fovX = 90,fovY = 60,fw = w/4.0,fh = h/3.0;
    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    double hp = -90,ht = 0;
    double htr = toRadian(ht);
    double hpr = toRadian(hp);

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


    Mat img(fh, fw, CV_8UC3, Scalar(0, 0, 0));
    int a = 0, b = 0;
    for (double i = 90  - fovY/2.0; i < 90 + fovY/2.0; i+= fovY*1.0/fh, b++) {
        for (double j = -fovX/2.0; j < fovX/2.0; j+= fovX*1.0/fw, a++) {

            double p2 [] = {0.0,0.0,0.0};
            matrix_x_vector(3,spherical2cartesian(toRadian((j<0)?j+360:j),toRadian((i<0)?i+180:i)),rot_y,p2);
            double p3 [] = {0.0,0.0,0.0};
            matrix_x_vector(3,p2,rot_z,p3);
            double *res = cartesian2coordinates(p3[0],p3[1],p3[2]);

            Point temp = Point((int)(res[1]),(int)(res[0]));
            img.at<Vec3b>(Point(a,b)) = image.at<Vec3b>(temp.x, temp.y);
        }
        a=0;
    }


    imwrite("fov.jpg", img);

    return 0;


}

#include "samplefunction.h"

int main() {

    int option = 1;

	//load image
//    hls::Mat<>image = cvLoadImage("cube.jpg", CV_LOAD_IMAGE_COLOR);

	//get width and height
//    int w = image.cols;
//    int h = image.rows;
	int width = 6144;
	int height = 4096;

	//parameters for FoV
    float hp = 0, ht = 0;
    int fovX = 60,fovY = 90,fw = width/6.0 ,fh = height/4.0;//1024 1024

    static float coordinates [1024][1024][2];

    convert(width,height,hp,ht,fw,fh,fovX,fovY,option,coordinates);

	//initialize fov image
    //hls::Mat fov(fh, fw, CV_8UC3, hls::Scalar(0, 0, 0));


//    IplImage* dst = cvCreateImage(cvSize(fw,fh), image.depth, image.channels);
//	//save the fov image
//    cvSaveImage(OUTPUT_IMAGE, dst);
//    cvReleaseImage(&fov);
    return 0;
}

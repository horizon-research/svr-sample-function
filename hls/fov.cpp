

#include "samplefunction.h"

int main(){

	//parameters for FoV
	fp hp = 0.0;
    fp ht = 0.0;

	int option = 1;

	//load image
//    hls::Mat<>image = cvLoadImage("cube.jpg", CV_LOAD_IMAGE_COLOR);

	//get width and height
//    int w = image.cols;
//    int h = image.rows;
    static int pixels[1024][1024][2];

    crt(hp,ht,option,pixels);

	//initialize fov image
    //hls::Mat fov(fh, fw, CV_8UC3, hls::Scalar(0, 0, 0));


//    IplImage* dst = cvCreateImage(cvSize(fw,fh), image.depth, image.channels);
//	//save the fov image
//    cvSaveImage(OUTPUT_IMAGE, dst);
//    cvReleaseImage(&fov);
    return 0;
  }

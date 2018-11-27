#include "reverse.h"
#include "hls_opencv.h"
#include <iostream>

int main(){

	IplImage* src;
	IplImage* dst;
	AXI_STREAM src_axi, dst_axi;

	//parameters for FoV
	double hp = 0.0;
	double ht = 0.0;

	// Load Input Image
	src = cvLoadImage("4k.jpg");
	dst = cvCreateImage(cvSize(fw,fh), src->depth, src->nChannels);

	// Image to AXI4 Data Stream
	IplImage2AXIvideo(src, src_axi);
	// Sample Function
    //crt(width,height,hp,ht,option,pixels);
    crt(src_axi, dst_axi, ht, hp);

	// AXI4 Data Stream to Image
	AXIvideo2IplImage(dst_axi, dst);

	// Save image
	cvSaveImage("fov.jpg", dst);

	// Release Memory
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
    return 0;
  }


#include "reverse.h"
#include "hls_opencv.h"
#include <iostream>

int main(){

	//parameters for FoV
	fp hp = 0.0;
    fp ht = 0.0;
	const int w = 720, h = 480;
    const int fw = w/4,fh = h/4;

	IplImage* src;
	IplImage* dst;
	AXI_STREAM src_axi, dst_axi;

	// Load Input Image
	src = cvLoadImage("480p.jpg");
	dst = cvCreateImage(cvSize(fw,fh), src->depth, src->nChannels);

	// Image to AXI4 Data Stream
	IplImage2AXIvideo(src, src_axi);
	// Sample Function
    //crt(width,height,hp,ht,option,pixels);
    crt(src_axi, dst_axi);

	// AXI4 Data Stream to Image
	AXIvideo2IplImage(dst_axi, dst);

	// Save image
	cvSaveImage("fov.jpg", dst);

	// Release Memory
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
    return 0;
  }


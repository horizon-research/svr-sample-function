#include "reverse.h"
#include "hls_opencv.h"
#include <iostream>

int main(){

	//parameters for FoV
	fp hp = 0.0;
    fp ht = 0.0;

	// Parameters for Sample Function
	int option = 0;
	int width = 1920;
	int height = 967;

	//static int pixels[481][483][2];

	IplImage* src;
	IplImage* dst;
	AXI_STREAM src_axi, dst_axi;

	// Load Input Image
	src = cvLoadImage("er.bmp");
	dst = cvCreateImage(cvSize(483,481), src->depth, src->nChannels);

	// Image to AXI4 Data Stream
	IplImage2AXIvideo(src, src_axi);
	// Sample Function
    //crt(width,height,hp,ht,option,pixels);
    crt(src_axi, dst_axi);
//
//    ofstream myfile;
//
//    myfile.open ("test.txt");
//
//    for(int a = 0; a < 1024 ; a++){
//    	for(int b = 0; b < 1024; b++){
//    		myfile << pixels[a][b][0]<< "," << pixels[a][b][1] << std::endl;
//    	}
//    }
//
//    myfile.close();

	// AXI4 Data Stream to Image
	AXIvideo2IplImage(dst_axi, dst);

	// Save image
	cvSaveImage("fov.jpg", dst);

	// Release Memory
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
    return 0;
  }


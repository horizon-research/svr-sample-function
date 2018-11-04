#include "samplefunction.h"
#include "hls_opencv.h"
#include <iostream>

//#include <fstream>
//using namespace std;

int main(){
	//parameters for FoV
	fp hp = 0.0;
    fp ht = 0.0;

	IplImage* src;
	IplImage* dst;
	AXI_STREAM src_axi, dst_axi;

	// Load Input Image
	src = cvLoadImage("er.bmp");
	dst = cvCreateImage(cvSize(481,483), src->depth, src->nChannels);

	// Image to AXI4 Data Stream
	IplImage2AXIvideo(src, src_axi);

	// Sample Function
    //crt(width,height,hp,ht,option,src_axi,dst_axi);
	crt(src_axi,dst_axi);
    // AXI4 Data Stream to Image
    AXIvideo2IplImage(dst_axi, dst);

    // Save image
    cvSaveImage("fov.jpg", dst);

    // Release Memory
    cvReleaseImage(&src);
    cvReleaseImage(&dst);
//

    return 0;
  }

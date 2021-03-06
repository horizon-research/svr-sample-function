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
	src = cvLoadImage("cube.jpg");
	dst = cvCreateImage(cvSize(1024,1024), src->depth, src->nChannels);

	// Image to AXI4 Data Stream
	IplImage2AXIvideo(src, src_axi);

	// Parameters for Sample Function
	int option = 1;
	int width = 6144;
	int height = 4096;

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

    return 0;
  }

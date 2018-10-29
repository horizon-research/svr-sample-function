#include "reverse.h"

int main(){

	//parameters for FoV
	fp hp = 0.0;
    fp ht = 0.0;

	// Parameters for Sample Function
	int option = 0;
	int width = 1920;
	int height = 967;

	static int pixels[481][483][2];
	// Sample Function
    crt(width,height,hp,ht,option,pixels);

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


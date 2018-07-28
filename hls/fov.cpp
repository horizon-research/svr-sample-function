#include "samplefunction.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){

	//parameters for FoV
	fp hp = 0.0;
    fp ht = 0.0;

	int option = 1;
	int width = 6144;
	int height = 4096;

    static int pixels[1024][1024][2];

    crt(width,height,hp,ht,option,pixels);

    ofstream myfile;

    myfile.open ("test.txt");

    for(int a = 0; a < 1024 ; a++){
    	for(int b = 0; b < 1024; b++){
    		myfile << pixels[a][b][0]<< "," << pixels[a][b][1] << std::endl;
    	}
    }

    myfile.close();

    return 0;
  }

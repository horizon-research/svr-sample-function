#include "samplefunction.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){

    //parameters for FoV
    double hp = 0.0;
    double ht = 0.0;

    static int fov[fh][fw][2];

    crt(hp, ht, fov);

    ofstream myfile;
    myfile.open ("indices.txt");

    for(int j = 0; j < fh; j++){
        for(int i = 0; i < fw; i++){

            myfile << fov[j][i][0]<< "," << fov[j][i][1] << "\n";
        }
    }

    myfile.close();
    return 0;
  }

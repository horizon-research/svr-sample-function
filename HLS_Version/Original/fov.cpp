#include "samplefunction.h"
#include <iostream>

int main(){

    //parameters for FoV
    double hp = 0.0;
    double ht = 0.0;

    int option = 0;
    int fov[fh][fw][2];

    crt(hp, ht, option, fov);

    for(int i = 0; i < fw; i++){
        for(int j = 0; j < fh; j++){
            printf("x: %d, y: %d\n", fov[j][i][0], fov[j][i][1]);
        }
    }


    return 0;
  }

#include "samplefunction.h"


fp PI = 3.1415926;
const int fov_x = 90, fov_y = 90;
angle fovX = fov_x,fovY = fov_y;

fp toRadian(angle a){

    fp piOver180 = 0.0174532925; //1/180

    return a * piOver180;

}

int nearestNeighbor(indices num){

    fp half = 0.5;
    int res = (int)(num + half);
    return res;
}

void spherical2cartesian(fp the, fp phi,fp result [3]){

    fp sphi,cphi,sthe,cthe;

    sphi = hls::sin(phi);
    cphi = hls::cos(phi);
    sthe = hls::sin(the);
    cthe = hls::cos(the);

    fp x = sphi*cthe;
    fp y = sphi*sthe;
    fp z = cphi;

    result[0] = x;
    result[1] = y;
    result[2] = z;
}

void spherical2coordinates(fp the, fp phi,indices result [2]){


    indices i ,j;

    fp two = 2 * PI;

    if(the > PI){
        i = (the - PI) / two * INPUT_WIDTH;
    }
    else{
        i = (PI + the) / two * INPUT_WIDTH;
    }

    j = phi /  PI * INPUT_HEIGHT;

    result [0] = i;
    result [1] = j;

}

void cartesian2coordinates(fp x, fp y, fp z,indices result [2]){

    fp the,phi;

    if(x != 0) {
       the = hls::atan2(y,x);

    } else {
        the = 1.57079632679;
    }

    phi =  hls::acos(z);

    spherical2coordinates(the,phi,result);
}

void matrixMultiplication(fp vector[3], fp matrix[3][3], fp result[3]) {

    result[0] = matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2];
    result[1] = matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2];
    result[2] = matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2];

}


fp absVal(fp num){
    if(num < 0){
        return -num;
    }

    return num;
}

//void crt(int width,int height,angle hp, angle ht,int option,AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){
//
void crt(double theta, double phi, int option, int fov[fh][fw][2]){

	#pragma HLS INTERFACE ap_fifo port=fov
    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first

	angle ht = theta, hp = phi;
    fp htr = toRadian(ht);
    fp hpr = toRadian(hp);

    fp str,ctr,cpr,spr;

    ctr = hls::cos(htr);
    str = hls::sin(htr);
    cpr = hls::cos(hpr);
    spr = hls::sin(hpr);

    //rotation matrices
    fp rot_y [3][3] = {
        {cpr, 0, -spr},
        {0, 1, 0},
        {spr, 0, cpr}
    };

    fp rot_z [3][3] = {
        {ctr, str, 0},
        {-str, ctr, 0},
        {0, 0, 1}
    };

    angle negativeOne = -1;
    angle two = 2.0;
    angle i = fovY / two , j = negativeOne * (fovX/two);

    fp p1[] = {0.0, 0.0, 0.0};
    fp p2[] = {0.0, 0.0, 0.0};
    fp p3[] = {0.0, 0.0, 0.0};
    indices res[] = {0.0, 0.0};
    angle jincrement = (double)(fov_x) / fw; // fovX / fw
    angle iincrement = (double)(fov_y) / fh; // fovY / fh
    fp pi_2 = 360.0;
    fp pi_half = 180.0;
    angle tempJ,tempI;

    indices half = 0.5, one = 1;
    for (int a = 0; a < fh; a++) {
            for (int b = 0; b < fw; b++) {

                #pragma HLS PIPELINE

                if(j < 0){
                    tempJ = j + pi_2;
                }
                else{
                    tempJ = j;
                }

                if(i < 0){
                    tempI = i + pi_half;
                }
                else{
                    tempI = i;
                }


                spherical2cartesian(toRadian(tempJ), toRadian(tempI),p1);
                //rotation along y axis

                matrixMultiplication(p1,rot_y, p2);

                //rotate along z axis

                matrixMultiplication(p2, rot_z, p3);


                // convert 3D Cartesian to 2d coordinates
                cartesian2coordinates(p3[0], p3[1], p3[2],res);

                fov[a][b][0]= nearestNeighbor(res[0]);
                fov[a][b][1]= nearestNeighbor(res[1]);

                j+= jincrement ;
            }
            i += iincrement;
            j = negativeOne * (fovX/two);
    }
    //printf("Writing Finished\n");



}




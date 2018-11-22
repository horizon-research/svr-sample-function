#include "samplefunction.h"

angle hp = 45.0;
angle ht = 45.0;
fp PI = 3.1415926;
    const int w = 720, h = 480;
const int fw = w/6,fh = h/6;
const int fov_x = 60, fov_y = 60;
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
        i = (the - PI) / two * w;
    }
    else{
        i = (PI + the) / two * w;
    }

    j = phi /  PI * h;

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
void crt(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){

    #pragma HLS INTERFACE axis port=INPUT_STREAM bundle=VIDEO_IN
    #pragma HLS INTERFACE axis port=OUTPUT_STREAM bundle=VIDEO_OUT

    #pragma HLS dataflow

    hls::Mat<fh,fw,HLS_8UC3> output;
    hls::Mat<h,w,HLS_8UC3> input;

    hls::AXIvideo2Mat(INPUT_STREAM, input);

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first

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

    RGB_PIXEL tempImage [w][h];

    int count = 0;
    for(int l = 0; l < h; l++){
        for(int v = 0; v < w; v++){
            tempImage[v][l] = input.read();

        }
    }


    count = 0;
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

                //output.write(tempImage[nearestNeighbor(res[0])][nearestNeighbor(res[1])]);

//
                indices u = res[0] - half;
                indices v = res[1] - half;
                indices x = (int)(u);
                indices y = (int)(v);
                indices u_ratio = u - x;
                indices v_ratio = v - y;
                indices u_opposite = one - u_ratio;
                indices v_opposite = one - v_ratio;

                RGB_PIXEL tempPixel;
                

                tempPixel.val[0] = (tempImage[x][y].val[0] * u_opposite + tempImage[x + 1][y].val[0] * u_ratio) * v_opposite
                        + (tempImage[x][y+1].val[0]* u_opposite  + tempImage[x + 1][y + 1].val[0] * u_ratio) * v_ratio;

                tempPixel.val[1] = (tempImage[x][y].val[1] * u_opposite + tempImage[x + 1][y].val[1] * u_ratio) * v_opposite
                        + (tempImage[x][y+1].val[1]* u_opposite  + tempImage[x + 1][y + 1].val[1] * u_ratio) * v_ratio;

                tempPixel.val[2] = (tempImage[x][y].val[2] * u_opposite + tempImage[x + 1][y].val[2] * u_ratio) * v_opposite
                                        + (tempImage[x][y+1].val[2]* u_opposite  + tempImage[x + 1][y + 1].val[2] * u_ratio) * v_ratio;
                output.write(tempPixel);
                //printf("Write %d, %d, %d\n",fw,fh,count++);

                j+= jincrement ;
            }
            i += iincrement;
            j = negativeOne * (fovX/two);
    }
    //printf("Writing Finished\n");
    hls::Mat2AXIvideo(output, OUTPUT_STREAM);


}




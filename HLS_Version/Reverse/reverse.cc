#include "reverse.h"

fp PI = 3.14159265358979323846;
fp half_pi = 180.0, two = 2.0, pi = 360.0;

int fovX = 90, fovY = 90;

fp toRadian(fp a){

	fp piOver180 = 0.0174532925; //1/180

    return a * piOver180;
}

int nearestNeighbor(fp num){

    int res = (int)(num.to_float() + 0.5);

    return res;
}

void spherical2cartesian(fp the, fp phi, fp result[3]){

    fp x = hls::sin(phi) * hls::cos(the);
    fp y = hls::sin(phi) * hls::sin(the);
    fp z = hls::cos(phi);

    result[0] = x;
    result[1] = y;
    result[2] = z;
    //printf("x: %lf, y:%lf, z:%lf\n",x, y, z);
}

void spherical2coordinates(fp the, fp phi, fp result[2]){

    fp i, j;
    fp two = 2.0;
    if (the > PI){

        i = (the - PI) / two / PI * INPUT_WIDTH;

    }
    else{

        i = (PI + the) / two / PI * INPUT_WIDTH;

    }

    j = phi / PI * INPUT_HEIGHT;

    result[0] = i;
    result[1] = j;
}

void cartesian2coordinates(fp x, fp y, fp z, fp result[2]){

    fp the;

    if (x != 0){

        the = hls::atan2(y, x);

    }
    else{

        the = toRadian(90.0);

    }

    fp phi = hls::acos(z);
    spherical2coordinates(the, phi, result);
}

//New approach
void coordinates2spherical(fp i, fp j, fp result[2]){
    fp theta, phi;

    if (i >= INPUT_WIDTH / 2.0){

        theta = (2 * i * PI / INPUT_WIDTH) - PI;

    }
    else{

        theta = (2 * i * PI / INPUT_WIDTH) + PI;

    }
    phi = j * PI / INPUT_HEIGHT;
    //printf("theta: %lf , phi: %lf\n", theta,phi);
    result[0] = theta;
    result[1] = phi;
}


void cartesian2coordinates_inverse(fp x, fp y, fp z, fp result[2]){

    fp the;
    // pay atentions to atan2 vs atan
    if (x != 0){

        the = hls::atan2(y, x);

    }
    else{

        the = toRadian(90.0);

    }

    fp phi = hls::acos(z);

    the = the / PI * half_pi;
    phi = phi / PI * half_pi;

    fp leftbound = -fovX/2.0;
    fp rightbound = fovX/2.0;
    fp topbound = 90 -fovY/2.0;
    fp bottombound = 90 +fovY/2.0;

    //printf("the: %lf, phi: %lf\n", the, phi);
    if(the >= leftbound && the <= rightbound && phi >= topbound && phi <= bottombound){

	    result[0] = (the.to_float() + fovX/2.0)* fw /90.0;
        result[1] = (phi.to_float() - 90 + fovY/2.0) * fh / 90.0;

    }
    else{

        result[0] = 0;
        result[1] = 0;
    }
}


void coordinates2cartesian(fp i, fp j, fp result[3]){

    fp angles [] = {0.0, 0.0};

    coordinates2spherical(i, j, angles);

    spherical2cartesian(angles[0],angles[1],result);

}

void matrixMultiplication(fp vector[3], fp matrix[3][3], fp res[3]){

    res[0] = matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2];
	res[1] = matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2];
	res[2] = matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2];
}


void crt(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM, double theta, double phi){

	// #pragma HLS ARRAY_PARTITION variable=fov complete dim=3
	// #pragma HLS INTERFACE ap_fifo port=fov
	#pragma HLS INTERFACE axis port=INPUT_STREAM bundle=VIDEO_IN
	#pragma HLS INTERFACE axis port=OUTPUT_STREAM bundle=VIDEO_OUT

	#pragma HLS dataflow

	hls::Mat<fh,fw,HLS_8UC3> output;
	hls::Mat<INPUT_HEIGHT,INPUT_WIDTH,HLS_8UC3> input;

	hls::AXIvideo2Mat(INPUT_STREAM, input);

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    // both are relative rotation angles

	fp ht = theta, hp = phi;
    // convert to radian
    fp htr = toRadian(theta);
    fp hpr = toRadian(phi);

    fp cos_theta = hls::cos(htr);
    fp cos_phi = hls::cos(hpr);
    fp sin_theta = hls::sin(htr);
    fp sin_phi = hls::sin(hpr);

    // rotation matrices
    fp rot_y[3][3] = {
        {cos_phi, 0, -sin_phi},
        {0, 1, 0},
        {sin_phi, 0, cos_phi}};

    fp rot_y_inverse[3][3] = {
        {cos_phi, 0, sin_phi},
        {0, 1, 0},
        {-sin_phi, 0,cos_phi}};

    fp rot_z[3][3] = {
        {cos_theta, sin_theta, 0},
        {-sin_theta, cos_theta, 0},
        {0, 0, 1}};

    fp rot_z_inverse[3][3] = {
        {cos_theta, -sin_theta, 0},
        {sin_theta, cos_theta, 0},
        {0, 0, 1}};

    //border on the input frame that map to output pixels

    float maxX = -1;
    float minX = 4000;
    float maxY = -1;
    float minY = 4000;



    // default head orientation is 0,90

    fp jT = -fovX / 2.0;
    fp jR = fovX / 2.0;
    fp jB = -fovX / 2.0;
    fp jL = 360 -fovX / 2.0;
    fp iT = 90 - fovY / 2.0;
    fp iR = 90 - fovY / 2.0;
    fp iB = 90 + fovY / 2.0;
    fp iL = 90 - fovY / 2.0;

    fp i = 0.0;
    fp j = 0.0;

    fp iIncrement = fovY * 1.0 / fh;
    fp jIncrement = fovX * 1.0 / fw;
    fp zero = 0.0;

    for(int k = 0; k < 2*(fh+fw); k++){
		#pragma HLS PIPELINE
		fp p1[] = {0.0, 0.0, 0.0};
		fp p2[] = {0.0, 0.0, 0.0};
		fp p3[] = {0.0, 0.0, 0.0};
		fp res[] = {0.0, 0.0};

        //Top
        if (k < fw){
            i = iT;
            j = jT;
            jT += jIncrement;
        }

        //Right
        if ((k >= fw) && (k < fw+fh)){
            i = iR;
            j = jR;
            iR += iIncrement;
        }

        //Bottom
        if ((k >= fw+fh) && (k < 2*fw+fh)){
            i = iB;
            j = jB;
            jB += jIncrement;
        }

        //Left
        if ((k >= 2*fw+fh) && (k < 2*(fw+fh))){
            i = iL;
            j = jL;
            iL += iIncrement;
        }

        fp tempI = i, tempJ = j;

        if(i < zero){
        	tempI = i + half_pi;
        }
        if(j < zero){
        	tempJ = j + pi;
        }

        // rotation along y axis

        spherical2cartesian(toRadian(tempJ), toRadian(tempI), p1);


        matrixMultiplication(p1, rot_y, p2);

        // rotate along z axis

        matrixMultiplication(p2, rot_z, p3);

        // convert 3D catesian to 2D coordinates
        cartesian2coordinates(p3[0], p3[1], p3[2], res);

        float tempRes0 = res[0].to_float();
        float tempRes1 = res[1].to_float();

        if (minX > tempRes0) minX = tempRes0;
        if (maxX < tempRes0) maxX = tempRes0;
        if (minY > tempRes1) minY = tempRes1;
        if (maxY < tempRes1) maxY = tempRes1;


    }



    if (hp <= -45 || hp >= 315){

        maxY = INPUT_HEIGHT;
        maxX = INPUT_WIDTH;
        minX = 0.0;

    }
    if(hp >= 45) {

        minY = 0.0;
        maxX = INPUT_WIDTH;
        minX = 0.0;

    }

    //for input pixel in the ouput range, calculate the outpout cordinnates
    int x , y;
    static RGB_PIXEL fov[fw][fh];
	//#pragma HLS ARRAY_PARTITION variable=fov complete dim=2

    for (y = 0; y < INPUT_HEIGHT; y++){
        for (x = 0; x < INPUT_WIDTH; x++){
			#pragma HLS PIPELINE
            //if pixel map to output get input index
            if (x <= maxX && x >= minX && y <= maxY && y >= minY){

            	fp cartesian []  = {0.0, 0.0, 0.0};
                coordinates2cartesian(x, y, cartesian);
                //printf("Cartesian:x: %lf, y :%lf, z :%lf\n", p1[0], p1[1], p1[2]);
                fp p1[] = {0.0, 0.0, 0.0};

                matrixMultiplication(cartesian, rot_z_inverse , p1);

              //  printf("P1:x: %lf, y :%lf, z :%lf\n", p2[0], p2[1], p2[2]);
                // rotate along z axis
        		fp p2[] = {0.0, 0.0, 0.0};
                matrixMultiplication(p1, rot_y_inverse, p2);

               // printf("P2:x: %lf, y :%lf, z :%lf\n", p3[0], p3[1], p3[2]);
                fp res[] = {0.0, 0.0};
                cartesian2coordinates_inverse(p2[0], p2[1], p2[2], res);

                fov[nearestNeighbor(res[0])][nearestNeighbor(res[1])] = input.read();

            }
            else{
            	input.read();
            }

//            if(x > maxX && y > maxY){
//				for(int h = 0; h < fh; h++){
//					for(int v = 0; v < fw; v++){
//						#pragma HLS PIPELINE
//						if(fov[v][h].val[0] == 0 && fov[v][h].val[1] == 0 && fov[v][h].val[2] == 0){
//
//							fp r = 0, g = 0, b = 0;
//							fp count = 0;
//
//							if(h - 1 >= 0){
//								r += fov[v][h - 1].val[0];
//								g += fov[v][h - 1].val[1];
//								b += fov[v][h - 1].val[2];
//								count += 1;
//							}
//							if(h + 1 < fh){
//								r += fov[v][h + 1].val[0];
//								g += fov[v][h + 1].val[1];
//								b += fov[v][h + 1].val[2];
//								count += 1;
//							}
//							if(v - 1 >= 0){
//								r += fov[v - 1][h].val[0];
//								g += fov[v - 1][h].val[1];
//								b += fov[v - 1][h].val[2];
//								count += 1;
//							}
//							if(v + 1 < fw){
//								r += fov[v + 1][h].val[0];
//								g += fov[v + 1][h].val[1];
//								b += fov[v + 1][h].val[2];
//								count += 1;
//							}
//
//							fov[v][h].val[0] = r / count;
//							fov[v][h].val[1] = g / count;
//							fov[v][h].val[2] = b / count;
//
//						}
//					}
//				}
//				break;
//            }
        }
    }


//


    for(int v = 0; v < fh; v++){
		for(int h = 0; h < fw; h++){

    		output.write(fov[h][v]);
    	}
    }

   hls::Mat2AXIvideo(output, OUTPUT_STREAM);
}

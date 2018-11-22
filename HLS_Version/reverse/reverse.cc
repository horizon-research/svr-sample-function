#include "reverse.h"

indices anglePI = 3.1415926;
fp PI = 3.1415926;

	const int w = 720, h = 480;

const int fov_x = 90, fov_y = 90;
angle fovX = fov_x,fovY = fov_y;
const int fw = w/4;
const int fh = w/4;


indices fwIndex = fw, fhIndex = fh;
angle hp = 0.0,ht = 0.0;

indices wIndex = w ,hIndex = h;
angle angle45 = 45, angleNegative45 = -45, angle135 = 135;
angle angle90 = 90,angle180 = 180,angle315 = 315;



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

    //printf("x: %lf, y:%lf, z:%lf\n",x.to_float(), y.to_float(), z.to_float());
}

void spherical2coordinates(fp the, fp phi,indices result [2]){


    indices i ,j;

    fp two = 2*PI;

    if(the > PI){
        i = (the - PI)/two * wIndex;
    }
    else{
        i = (PI + the)/two * wIndex;
    }

    j = phi /  PI * hIndex;

    result [0] = i;
    result [1] = j;

}

void cartesian2coordinates(fp x, fp y, fp z,indices result [2]){

    fp the,phi;

    if(x != 0) {
       the = hls::atan2(y,x);

    } else {
        the = 1.57079632679;//90
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

//New approach
void coordinates2spherical(indices i, indices j, angle result[2]){
    angle theta, phi;
    indices two = 2;

    if (i >= wIndex / two){

        theta = (two * i / wIndex * anglePI) - anglePI;

    }
    else{

        theta = (two * i/ wIndex * anglePI) + anglePI;

    }
    phi = j / hIndex * anglePI;

    //printf("theta: %lf , phi: %lf\n", theta.to_float(),phi.to_float());
    result[0] = theta;
    result[1] = phi;
}


void cartesian2coordinates_inverse(fp x, fp y, fp z, indices result[2]){

	//printf("x: %lf, y :%lf, z :%lf\n", x.to_float(),y.to_float(),z.to_float());
    angle the;
    // pay atentions to atan2 vs atan
    if (x != 0){

        the = hls::atan2(y, x);

    }
    else{

        the = toRadian(angle90);

    }

    angle phi = hls::acos(z);

    the = the / PI * angle180;
    phi = phi / PI * angle180;

   if(the >= angleNegative45 && the <= angle45 && phi >= angle45 && phi <= angle135){

	    result[0] = (the + angle45) / fovX * fwIndex ;
        result[1] = (phi - angle90  + angle45) / fovY * fhIndex;

      // count++;
   }
   else{

       result[0] = 0;
       result[1] = 0;
   }
}


void coordinates2cartesian(indices i, indices j, fp result[3]){

    angle angles [] = {0.0, 0.0};

    coordinates2spherical(i, j, angles);

    spherical2cartesian(angles[0],angles[1],result);

}


//void crt(int width,int height,angle hp, angle ht,int option,int fov[481][483][2]) {

void crt(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){

	// #pragma HLS ARRAY_PARTITION variable=fov complete dim=3
	// #pragma HLS INTERFACE ap_fifo port=fov
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

    fp rot_y_inverse[3][3] = {
		{cpr, 0, spr},
		{0, 1, 0},
		{-spr, 0, cpr}
    };

    fp rot_z_inverse[3][3] = {
		{ctr, -str, 0},
		{str, ctr, 0},
		{0, 0, 1}
    };

	fp p1[] = {0.0, 0.0, 0.0};
	fp p2[] = {0.0, 0.0, 0.0};
	fp p3[] = {0.0, 0.0, 0.0};
	indices res[] = {0.0, 0.0};
	angle jincrement = fov_x/fw; // fovX / fw
	angle iincrement = fov_y/fh; // fovY / fh
	fp pi_2 = 360.0;
	fp pi_half = 180.0;
	angle tempJ,tempI;

	double maxX = -1;
	double maxY = -1;
	double minX = 20000;
	double minY = 20000;

	// default head orientation is 0,90
	angle two = 2.0;
	angle jT = -fovX / two;
	angle jR = fovX / two;
	angle jB = -fovX / two;
	angle jL = 360 -fovX / two;
	angle iT = 90 - fovY / two;
	angle iR = 90 - fovY / two;
	angle iB = 90 + fovY / two;
	angle iL = 90 - fovY / two;

	angle i = 0.0;
	angle j = 0.0;



	for(int k = 0; k < 2*(fh+fw); k++){
		#pragma HLS PIPELINE
		//Top
		if (k < fw){
			i = iT;
			j = jT;
			jT +=  fovX / fw;
		}

		//Right
		if ((k >= fw) && (k < fw+fh)){
			i = iR;
			j = jR;
			iR += fovY / fh;
		}

		//Bottom
		if ((k >= fw+fh) && (k < two*fw+fh)){
			i = iB;
			j = jB;
			jB +=  fovX / fw;
		}

		//Left
		if ((k >= two*fw+fh) && (k < two*(fw+fh))){
			i = iL;
			j = jL;
			iL += fovY / fh;
		}

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
		// rotation along y axis
		angle p1[] = {0.0, 0.0, 0.0};
		spherical2cartesian(toRadian(j), toRadian(i), p1);

		angle p2[] = {0.0, 0.0, 0.0};
		matrixMultiplication(p1, rot_y, p2);

		// rotate along z axis
		angle p3[] = {0.0, 0.0, 0.0};
		matrixMultiplication(p2, rot_z, p3);

		angle res[] = {0.0, 0.0};

		// convert 3D catesian to 2D coordinates
		cartesian2coordinates(p3[0], p3[1], p3[2], res);

		if (minX > res[0]) minX = res[0];
		if (maxX < res[0]) maxX = res[0];
		if (minY > res[1]) minY = res[1];
		if (maxY < res[1]) maxY = res[1];


	}


	if(hp <= angleNegative45 || hp >= angle315){

		maxY = h;
		maxX = w;
		minX = 0.0;

	}

   if(hp >= angle45) {

       minY = 0.0;
       maxX = w;
       minX = 0.0;

   }
   RGB_PIXEL fov[fw][fh];

    //printf("Max: x :%lf , y:%lf, Min: x :%lf , y:%lf\n", maxX, maxY, minX, minY);
   int x = 0, y = 0;

   for (y = 0; y < h; y++){
          for (x = 0; x < w; x++){
			#pragma HLS PIPELINE

               //if pixel map to output get input index
               if (x <= maxX && x >= minX && y <= maxY && y >= minY){

            	   indices X = x;
            	   indices Y = y;

                   fp cartesian []  = {0.0, 0.0, 0.0};

                   coordinates2cartesian(X, Y, cartesian);

                   // rotate along z axis
                   matrixMultiplication(cartesian, rot_z_inverse , p1);

                   // rotate along y axis
                   matrixMultiplication(p1, rot_y_inverse, p2);

                   cartesian2coordinates_inverse(p2[0], p2[1], p2[2], res);

                   int tempX = nearestNeighbor(res[0]);
                   int tempY = nearestNeighbor(res[1]);

    		
                  fov[tempX][tempY] = input.read();
               }
               else{
               	input.read();
               }
          }
   }

   for(int m = 0; m < fh; m++){
   	for(int n = 0; n < fw; n++){
   		output.write(fov[n][m]);
   	}
   }
   //printf("count: %d\n",count);
   hls::Mat2AXIvideo(output, OUTPUT_STREAM);
}

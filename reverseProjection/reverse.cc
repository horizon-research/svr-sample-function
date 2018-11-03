#include "reverse.h"

fp PI = 3.1415926;
indexes w = 1920 ,h = 967;
angle angle45 = 45, angleNegative45 = -45, angle135 = 135;
indexes anglePI = 3.1415926;
angle angle90 = 90,angle180 = 180,angle315 = 315;
indexes fw = 481, fh = 483;
angle hp = 0,ht = 0;
int count = 0;


fp toRadian(angle a){

	fp piOver180 = 0.0174532925; //1/180

    return a * piOver180;

}

int nearestNeighbor(indexes num){

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

void spherical2coordinates(fp the, fp phi,indexes result [2]){


    indexes i ,j;

    fp two = 2*PI;

    if(the > PI){
        i = (the - PI)/two * w;
    }
    else{
        i = (PI + the)/two * w;
    }

    j = phi /  PI * h;

    result [0] = i;
    result [1] = j;

}

void cartesian2coordinates(fp x, fp y, fp z,indexes result [2]){

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
void coordinates2spherical(indexes i, indexes j, angle result[2]){
    angle theta, phi;
    indexes two = 2;

    if (i >= w / two){

        theta = (two * i / w * anglePI) - anglePI;

    }
    else{

        theta = (two * i/ w * anglePI) + anglePI;

    }
    phi = j / h * anglePI;

    //printf("theta: %lf , phi: %lf\n", theta.to_float(),phi.to_float());
    result[0] = theta;
    result[1] = phi;
}


void cartesian2coordinates_inverse(fp x, fp y, fp z, indexes result[2]){

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
   // printf("the: %lf, phi: %lf\n", the.to_float(),phi.to_float());
    the = the / PI * angle180;
    phi = phi / PI * angle180;
    //printf("the: %lf, phi: %lf\n", the.to_float(),phi.to_float());
    if(the >= angleNegative45 && the <= angle45 && phi >= angle45 && phi <= angle135){

	    result[0] = (the + angle45) / angle90 * fw ;
        result[1] = (phi - angle90  + angle45) / angle90 * fh;
        //printf("res: %lf , %lf\n", result[0].to_float(),result[1].to_float());
        count++;
    }
    else{

        result[0] = 0;
        result[1] = 0;
    }
}


void coordinates2cartesian(indexes i, indexes j, fp result[3]){

    angle angles [] = {0.0, 0.0};

    coordinates2spherical(i, j, angles);

    spherical2cartesian(angles[0],angles[1],result);

}


//void crt(int width,int height,angle hp, angle ht,int option,int fov[481][483][2]) {

void crt(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){
//
//	#pragma HLS ARRAY_PARTITION variable=fov complete dim=3
//	#pragma HLS INTERFACE ap_fifo port=fov
#pragma HLS INTERFACE axis port=INPUT_STREAM bundle=VIDEO_IN
#pragma HLS INTERFACE axis port=OUTPUT_STREAM bundle=VIDEO_OUT

#pragma HLS dataflow

	hls::Mat<483,481,HLS_8UC3> output;
	hls::Mat<967,1920,HLS_8UC3> input;

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


    angle i = 45, j = -30.0; // i = fovY / 2, j = -fovX/2

	fp p1[] = {0.0, 0.0, 0.0};
	fp p2[] = {0.0, 0.0, 0.0};
	fp p3[] = {0.0, 0.0, 0.0};
	indexes res[] = {0.0, 0.0};
	angle jincrement = 0.187110187; // fovX / fw
	angle iincrement = 0.186335403; // fovY / fh
	fp pi_2 = 360.0;
	fp pi_half = 180.0;
	angle tempJ,tempI;

	double maxX = -1;
	double maxY = -1;
	double minX = 2000;
	double minY = 2000;

	// left vertical
	int a = 0, b;
	angle leftbound = 315;
	angle vertical = 45;

	for(b = 0;b < 483; b++){
		#pragma HLS PIPELINE

		spherical2cartesian(toRadian(leftbound), toRadian(vertical), p1);
		matrixMultiplication(p1, rot_y, p2);
		matrixMultiplication(p2, rot_z, p3);
		cartesian2coordinates(p3[0], p3[1], p3[2], res);

		double temp0 = res[0].to_double();
		double temp1 = res[1].to_double();
		if (minX > temp0) minX = temp0;
		if (maxX < temp0) maxX = temp0;
		if (minY > temp1) minY = temp1;
		if (maxY < temp1) maxY = temp1;

		vertical += iincrement;
	}

	// right vertical

	vertical = 45;
	angle rightbound = 45;

	for(b = 0; b < 483; b++){
		#pragma HLS PIPELINE

		spherical2cartesian(toRadian(rightbound), toRadian(vertical), p1);
		matrixMultiplication(p1, rot_y, p2);
		matrixMultiplication(p2, rot_z, p3);
		cartesian2coordinates(p3[0], p3[1], p3[2], res);

		double temp0 = res[0].to_double();
		double temp1 = res[1].to_double();
		if (minX > temp0) minX = temp0;
		if (maxX < temp0) maxX = temp0;
		if (minY > temp1) minY = temp1;
		if (maxY < temp1) maxY = temp1;

		vertical += iincrement;
	}

	// top horizontal

	angle topbound = 45;
	angle horizontal = -45;
	angle angle360 = 360;
	angle zero = 0;
	angle tempH = 0;

	for(a = 0; a < 481; a++){
		#pragma HLS PIPELINE

		if(horizontal < zero){
			tempH = horizontal + angle360;
		}
		else{
			tempH = horizontal;
		}
		spherical2cartesian(toRadian(tempH), toRadian(topbound), p1);
		matrixMultiplication(p1, rot_y, p2);
		matrixMultiplication(p2, rot_z, p3);
		cartesian2coordinates(p3[0], p3[1], p3[2], res);

		double temp0 = res[0].to_double();
		double temp1 = res[1].to_double();

		if (minX > temp0) minX = temp0;
		if (maxX < temp0) maxX = temp0;
		if (minY > temp1) minY = temp1;
		if (maxY < temp1) maxY = temp1;

		horizontal += jincrement;
	}

	// bottom horizontal

	angle buttombound = 135;
	horizontal = -45;

	for(a = 0; a < 481; a++){
		#pragma HLS PIPELINE

		if(horizontal < zero){
			tempH = horizontal + angle360;
		}
		else{
			tempH = horizontal;
		}
		spherical2cartesian(toRadian(tempH), toRadian(buttombound), p1);
		matrixMultiplication(p1, rot_y, p2);
		matrixMultiplication(p2, rot_z, p3);
		cartesian2coordinates(p3[0], p3[1], p3[2], res);

		double temp0 = res[0].to_double();
		double temp1 = res[1].to_double();

		if (minX > temp0) minX = temp0;
		if (maxX < temp0) maxX = temp0;
		if (minY > temp1) minY = temp1;
		if (maxY < temp1) maxY = temp1;

		horizontal += jincrement;
	}

	if(hp <= angleNegative45 || hp >= angle315){

		maxY = 967;
		maxX = 1920;
		minX = 0.0;

	}

    if(hp >= angle45) {

        minY = 0.0;
        maxX = 1920;
        minX = 0.0;

    }
    RGB_PIXEL fov[481][483];

    //printf("Max: x :%lf , y:%lf, Min: x :%lf , y:%lf\n", maxX, maxY, minX, minY);
    int x, y;

    for (y = 0; y < 967; y++){
           for (x = 0; x < 1920; x++){
			#pragma HLS PIPELINE

               //if pixel map to output get input index
                if (x <= maxX && x >= minX && y <= maxY && y >= minY){

            	   indexes X = x;
            	   indexes Y = y;
                   fp cartesian []  = {0.0, 0.0, 0.0};
                   coordinates2cartesian(X, Y, cartesian);

                   matrixMultiplication(cartesian, rot_z_inverse , p1);

                   // rotate along z axis
                   matrixMultiplication(p1, rot_y_inverse, p2);

                   cartesian2coordinates_inverse(p2[0], p2[1], p2[2], res);

                   int tempX = nearestNeighbor(res[0]);
                   int tempY = nearestNeighbor(res[1]);

                   fov[tempX][tempY] = input.read();
                   //input.read();
                }
                else{
                	input.read();
                }
           }
       }


    for(int m = 0; m < 483; m++){
    	for(int n = 0; n < 481; n++){
    		output.write(fov[n][m]);
    	}
    }
    printf("count: %d\n",count);
    hls::Mat2AXIvideo(output, OUTPUT_STREAM);
}

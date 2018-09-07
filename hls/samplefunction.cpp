#include "samplefunction.h"

fp option = 1;
indexes width = 6144;
indexes height = 4096;
angle hp = 0.0;
angle ht = 0.0;
fp PI = 3.1415926;
indexes w = 6144 ,h = 4096;
indexes ts = 2048;

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
}

void spherical2coordinates(fp the, fp phi,indexes result [2]){


    indexes i ,j;

    fp two = 2*PI;

    if(the > PI){
        i = (the - PI)/two *w;
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

void findPixel(int index, fp x,fp y,indexes result [2]) {

    indexes vertical;

    indexes half = 0.5;

    if (index > 2) {
        vertical = 1.0;
    }else{
    	vertical = 0.0;
    }

    indexes mod = index%3;
    indexes n = ts * mod + y* ts;
    indexes m = ts * vertical + x * ts;

	result [0] = n;
	result [1] = m;

}

fp absVal(fp num){
	if(num < 0){
		return -num;
	}

	return num;
}
//from wikipedia: https://en.wikipedia.org/wiki/Cube_mapping
void convert_xyz_to_cube_uv(fp x, fp y, fp z,indexes result [2]) {

    fp absX = absVal(x);
    fp absY = absVal(y);
    fp absZ = absVal(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    fp maxAxis = 0, uc = 0, vc = 0;
    fp u,v;
    int index;

    // POSITIVE X
    if (isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from +z to -z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -z;
        vc = y;
        index = 4;
    }
    // NEGATIVE X
    else if (!isXPositive && absX >= absY && absX >= absZ) {
        // u (0 to 1) goes from -z to +z
        // v (0 to 1) goes from -y to +y
        maxAxis = absX;
        uc = -z;
        vc = -y;
        index = 5;

    }
    // POSITIVE Y
    else if (isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from +z to -z
        maxAxis = absY;
        uc = -z;
        vc = -x;
        index = 1;

    }
    // NEGATIVE Y
    else  if (!isYPositive && absY >= absX && absY >= absZ) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -z to +z
        maxAxis = absY;
        uc = -z;
        vc = x;
        index = 0;

    }
    // POSITIVE Z
    else  if (isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from -x to +x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = x;
        vc = y;
        index = 2;
    }
    // NEGATIVE Z
    else  if (!isZPositive && absZ >= absX && absZ >= absY) {
        // u (0 to 1) goes from +x to -x
        // v (0 to 1) goes from -y to +y
        maxAxis = absZ;
        uc = -x;
        vc = y;
        index = 3;

    }
    fp half = 0.5;
    fp one = 1;

    // Convert range from -1 to 1 to 0 to 1
    u = half * (uc / maxAxis + one);
    v = half * (vc / maxAxis + one);


    findPixel(index, u, (one - v),result);
}

void findPixel_EAC(int index, fp u,fp v,indexes result [2]){

    indexes n,m;
    indexes mod = index%3;
    indexes one = 1.0f;
    indexes two = 2.0f;
    // Left Front Right
    if(index <= 2){

        n = (ts * mod)  + v * ts;
	    m = u * ts;

    }
    // Down Back Up
    else{

        switch(index){
            case 3:
                n = u * ts;
                m = ts + (one - v) * ts;
                break;

            case 4:
                n = ts + (one - u) * ts + one;
                m = ts + v * ts + one;
                break;

            case 5:
                n = ts * two  +  u * ts;
                m = ts  + (one - v) * ts;
                break;
        }
    }
    result[0] = n - one;
    result[1] = m - one;

}

void convert_EAC(fp x, fp y, fp z,indexes result [2]){

    fp maxAxis, uc, vc;
    fp u, v;
    int index;

    fp absX = absVal(x);
	fp absY = absVal(y);
	fp absZ = absVal(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    // Front
    if (isXPositive && absX >= absY && absX >= absZ) {

        index = 1;
        maxAxis = absX;
        uc = -z;
        vc = y;

    }
    // Back
    else if (!isXPositive && absX >= absY && absX >= absZ) {

        index = 4;
        maxAxis = absX;
        uc = -z;
        vc = -y;

    }
    // Left
    else if (isYPositive && absY >= absX && absY >= absZ) {

        index = 2;
        maxAxis = absY;
        uc = -z;
        vc = -x;

    }
    // Right
    else if (!isYPositive && absY >= absX && absY >= absZ) {

        index = 0;
        maxAxis = absY;
        uc = -z;
        vc = x;

    }
    // Up
    else if (isZPositive && absZ >= absX && absZ >= absY) {

        index = 5;
        maxAxis = absZ;
        uc = x;
        vc = y;

    }
    // Down
    else if (!isZPositive && absZ >= absX && absZ >= absY) {

        index = 3;
        maxAxis = absZ;
        uc = -x;
        vc = y;

    }

    fp two = 2.0f;
    fp half = 0.5f;
    fp horizontal = uc / maxAxis;
    fp vertical = vc / maxAxis;
    u = two * hls::atan(horizontal)/PI + half;
    v = two * hls::atan(vertical)/PI + half;


    findPixel_EAC(index,u,v,result);

}

//void countPixel(hls::Mat<4096,6144,HLS_8UC3>image, RGB_PIXEL pixel, int indexI, int indexJ){
//	for(int j = 0; j <= indexJ; j++){
//		for(int i = 0; i < indexI; i++){
//			image.read();
//		}
//	}
//
//	pixel = image.read();
//}

//void crt(int width,int height,angle hp, angle ht,int option,AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){
//
void crt(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM){

	#pragma HLS INTERFACE axis register both port=INPUT_STREAM
	#pragma HLS INTERFACE axis register both port=OUTPUT_STREAM
//	#pragma HLS ARRAY_PARTITION variable=fov complete dim=3
//	#pragma HLS INTERFACE ap_fifo port=fov

	hls::Mat<1024,1024,HLS_8UC3> fov;
	hls::Mat<4096,6144,HLS_8UC3> input;

	hls::AXIvideo2Mat(INPUT_STREAM, input);

	RGB_PIXEL tempArr[100][100];

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

    angle i = 45.0, j = -30.0;

	fp p1[] = {0.0, 0.0, 0.0};
	fp p2[] = {0.0, 0.0, 0.0};
	fp p3[] = {0.0, 0.0, 0.0};
	indexes res[] = {0.0, 0.0};
	angle jincrement = 0.05859375;
	angle iincrement = 0.087890625;
	fp pi_2 = 360.0;
	fp pi_half = 180.0;
	angle tempJ,tempI;

    for (int a = 0; a < 1024; a++) {
    	    for (int b = 0; b < 1024; b++) {
			//#pragma HLS LOOP_TRIPCOUNT min=0 max=1024
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

				if (option == 0) {
				  // convert 3D Cartesian to 2d coordinates
				    cartesian2coordinates(p3[0], p3[1], p3[2],res);
				}
				else if (option == 1){

				    convert_xyz_to_cube_uv(p3[0], p3[1], p3[2],res);

				}
				else{
					convert_EAC(p3[0], p3[1], p3[2],res);
				}


				RGB_PIXEL temp = input.read();

//				countPixel(input, temp, nearestNeighbor(res[0]), nearestNeighbor(res[1]));
//				for(int j = 0; j < 4096; j++){
//					for(int i = 0; i < 6144; i++){
//
//						if (i == nearestNeighbor(res[0]) && j == nearestNeighbor(res[1])){
//							temp = input.read();
//							printf("read\n");
//
//						}
//						else{
//							input.read();
//						}
//					}
//				}

				fov.write(temp);
				printf("Write\n");

				j+= jincrement ;
    		}
    		i+= iincrement;
    		j = -30.0;
    }

    hls::Mat2AXIvideo(fov, OUTPUT_STREAM);

}




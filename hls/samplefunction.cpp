#include "samplefunction.h"

fp PI = 3.14159;

fp w ,h;

fp tileSize;

fp toRadian(fp a){
	fp pi = 180.0;
    return a * PI / pi;
}

int nearestNeighbor(fp num){
	fp half = 0.5;
	int res = (int)((num + half).to_float());
	return res;
}

void spherical2cartesian(fp the, fp phi,fp result [3]){
	fp sphi,cphi,sthe,cthe;
	sphi = sinf(phi);
	cphi = cosf(phi);
	sthe = sinf(the);
	cthe = cosf(the);

    fp x = sphi*cthe;
    fp y = sphi*sthe;
    fp z = cphi;

    result[0] = x;
    result[1] = y;
    result[2] = z;

}

void spherical2coordinates(fp the, fp phi,fp result [2]){

    fp i ,j;


    if(the > PI){
        i = (the - PI)/2/PI *w;
    }
    else{
        i = (PI + the)/2/PI * w;
    }

    j = phi /  PI * h;

    result [0] = i;
    result [1] = j;

}

void cartesian2coordinates(fp x, fp y, fp z,fp result [2]){

    fp the,phi;

    if(x != 0) {
       the = atan2f(y,x);

    } else {
        the = 1.5708f;
    }

    phi =  acosf(z);

    spherical2coordinates(the,phi,result);
}

void matrixMultiplication(fp vector[3], fp matrix[3][3], fp result[3]) {

	result[0] = matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2];
	result[1] = matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2];
	result[2] = matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2];

}

void findPixel(int index, fp x,fp y,fp result [2]) {

    int vertical;

    if (index > 2) {
        vertical = 1;
    }else{
    	vertical = 0;
    }

    fp n = (tileSize * (index%3))  + y * tileSize -1;
    fp m = (tileSize * vertical) + x * tileSize -1;

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
void convert_xyz_to_cube_uv(fp x, fp y, fp z,fp result [2]) {

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

void crt(int width,int height,fp hp, fp ht,int option,int fov[1024][1024][2]) {

	#pragma HLS ARRAY_PARTITION variable=fov complete dim=3
	#pragma HLS INTERFACE ap_fifo port=fov

	w = width;
	h = height;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    fp htr = toRadian(ht);
    fp hpr = toRadian(hp);
    fp three = 3.0;
    tileSize = w/three;

    fp str,ctr,cpr,spr;
    ctr = cosf(htr);
    str = sinf(htr);
    cpr = cosf(hpr);
    spr = sinf(hpr);

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

    fp i = 45.0, j = -30.0;

	fp p1[] = {0.0, 0.0, 0.0};
	fp p2[] = {0.0, 0.0, 0.0};
	fp p3[] = {0.0, 0.0, 0.0};
	fp res[] = {0.0, 0.0};
	fp jincrement = 0.05859;
	fp iincrement = 0.08789;
	fp pi_2 = 360;
	fp pi_half = 180.0;
    for (int a = 0; a < 1024; a++) {
	//#pragma HLS LOOP_TRIPCOUNT min=0 max=1024
    	    for (int b = 0; b < 1024; b++) {
			//#pragma HLS LOOP_TRIPCOUNT min=0 max=1024
			#pragma HLS PIPELINE

    	    	if(j < 0){
    	    		j += pi_2;
    	    	}

    	    	if(i < 0){
    	    		i += pi_half;
    	    	}
    			//rotation along y axis

    			spherical2cartesian(toRadian(j), toRadian(i),p1);

    			matrixMultiplication(p1,rot_y, p2);

    			//rotate along z axis

    			matrixMultiplication(p2, rot_z, p3);

				if (option == 0) {
				  // convert 3D Cartesian to 2d coordinates
				  cartesian2coordinates(p3[0], p3[1], p3[2],res);
				}
				else{

				  convert_xyz_to_cube_uv(p3[0], p3[1], p3[2],res);

				}

				fov[a][b][0] = nearestNeighbor(res[0]);
				fov[a][b][1] = nearestNeighbor(res[1]);

	    		j+= jincrement;

    		}
    		i+= iincrement;
    }
}




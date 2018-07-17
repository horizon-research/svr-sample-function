#include "samplefunction.h"


angles PI = 3.14159;

int w ,h;

angles tileSize;

angles toRadian(angles a){
	ap_fixed<4,6> pi = 180.0;
    return a * PI / pi;
}

void calSin(angles angle, angles output){

    ap_fixed<32,5> temp = angle;
    output = hls::sinf(temp);
}

void calCos(angles angle, angles output){

    ap_fixed<32,5> temp = angle;
    output = hls::cosf(temp);
}

void calAtan2(angles angle1,angles angle2, angles output){

	ap_fixed<32,5> temp1 = angle1;
	ap_fixed<32,5> temp2 = angle2;
	output = hls::atan2f(temp1,temp2);

}

void calAcos(angles angle, angles output){

    ap_fixed<32,5> temp = angle;
    output = hls::acosf(temp);

}

void spherical2cartesian(angles the, angles phi,angles result [3]){
	angles sphi,cphi,sthe,cthe;
	calSin(phi,sphi);
	calCos(phi,cphi);
	calSin(the,sthe);
	calCos(the,cthe);

    angles x = sphi*cthe;
    angles y = sphi*sthe;
    angles z = cphi;

    result[0] = x;
    result[1] = y;
    result[2] = z;

}

void spherical2coordinates(angles the, angles phi,indexes result [2]){

    angles i ,j;


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

void cartesian2coordinates(angles x, angles y, angles z,indexes result [2]){

    angles the,phi;

    if(x != 0) {
       calAtan2(y,x,the);

    } else {
        the = 1.5708;
    }

    calAcos(z,phi);

    spherical2coordinates(the,phi,result);
}

void matrixMultiplication(angles vector[3], angles matrix[3][3], angles result[3]) {

	result[0] = matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2];
	result[1] = matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2];
	result[2] = matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2];

}

void findPixel(int index, angles x,angles y,indexes result [2]) {

    int vertical;

    if (index > 2) {
        vertical = 1;
    }else{
    	vertical = 0;
    }

    indexes n = (tileSize * (index%3))  + y * tileSize -1;
    indexes m = (tileSize * vertical) + x * tileSize -1;

    result [0] = n;
    result [1] = m;

}

angles absVal(angles num){
	if(num < 0){
		return -num;
	}

	return num;
}
//from wikipedia: https://en.wikipedia.org/wiki/Cube_mapping
void convert_xyz_to_cube_uv(angles x, angles y, angles z,indexes result [2]) {

    angles absX = absVal(x);
    angles absY = absVal(y);
    angles absZ = absVal(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    ap_fixed<5,10> maxAxis = 0, uc = 0, vc = 0;
    angles u,v;
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
    angles half = 0.5;
    angles one = 1;

    // Convert range from -1 to 1 to 0 to 1
    u = half * (uc / maxAxis + one);
    v = half * (vc / maxAxis + one);

    findPixel(index, u, (one - v),result);
}

void convert(int width,int height,angles hp,angles ht,int fw,int fh, int fovX,int fovY,int option,float fov[1024][1024][2]) {

	w = width;
	h = height;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    angles htr = toRadian(ht);
    angles hpr = toRadian(hp);
    tileSize = w/3.0;

    angles str,ctr,cpr,spr;

    calCos(htr,ctr);
    calCos(hpr,cpr);
    calSin(htr,str);
    calSin(hpr,spr);

	//rotation matrices
    angles rot_y [3][3] = {
        {cpr, 0, -spr},
        {0, 1, 0},
        {spr, 0, cpr}
    };

    angles rot_z [3][3] = {
        {ctr, str, 0},
        {-str, ctr, 0},
        {0, 0, 1}
    };

    angles i = 45.0, j = -30.0;

	angles p1[] = {0.0, 0.0, 0.0};
	angles p2[] = {0.0, 0.0, 0.0};
	angles p3[] = {0.0, 0.0, 0.0};
	indexes res[] = {0.0, 0.0};
	ap_fixed<1,6> jincrement = 0.05859;
	ap_fixed<1,6> iincrement = 0.08789;
	ap_fixed<3,1> pi_2 = 360;
	ap_fixed<3,1> pi_half = 180;
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
				fov[a][b][0] = res[0];
				fov[a][b][1] = res[1];

	    		j+= jincrement;

    		}
    		i+= iincrement;
    }
}


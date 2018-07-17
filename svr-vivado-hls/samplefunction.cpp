#include "samplefunction.h"


float PI = 3.14159f;

int w ,h;

double tileSize;

float toRadian(float a){
    return a * PI / 180.0f;
}

void spherical2cartesian(float the, float phi,float result [3]){

	float sp = hls::sinf(phi);
    float x = sp * hls::cosf(the);
    float y = sp * hls::sinf(the);
    float z = hls::cosf(phi);

    result[0] = x;
    result[1] = y;
    result[2] = z;

}

void spherical2coordinates(float the, float phi,float result [2]){

    float i ,j;


    if(the > PI){
        i = (the - PI)/2.0f/PI *w;
    }
    else{
        i = (PI + the)/2.0f/PI * w;
    }

    j = phi /  PI * h;

    result [0] = i;
    result [1] = j;

}

void cartesian2coordinates(float x, float y, float z,float result [2]){

    float the;

    if(x != 0) {
        the = hls::atan2f(y,x);

    } else {
        the = 1.5708f;
    }

    float phi = hls::acosf(z);

    spherical2coordinates(the,phi,result);
}

void matrixMultiplication(float vector[3], float matrix[3][3], float result[3]) {

	result[0] = matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2];
	result[1] = matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2];
	result[2] = matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2];

}

void findPixel(int index, float x,float y,float result [2]) {

    int vertical;

    if (index > 2) {
        vertical = 1;
    }else{
    	vertical = 0;
    }

    float n = tileSize * (index%3) + y * tileSize -1;
    float m = tileSize * vertical + x * tileSize -1;

    result [0] = n;
    result [1] = m;

}

//from wikipedia: https://en.wikipedia.org/wiki/Cube_mapping
void convert_xyz_to_cube_uv(float x, float y, float z,float result [2]) {

    float absX = fabs(x);
    float absY = fabs(y);
    float absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    float maxAxis, uc, vc;
    float u,v;
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

    // Convert range from -1 to 1 to 0 to 1
    u = 0.5f * (uc / maxAxis + 1.0f);
    v = 0.5f * (vc / maxAxis + 1.0f);

    findPixel(index, u, (1.0f-v),result);
}

void convert(int width,int height,float hp,float ht,int fw,int fh, int fovX,int fovY,int option,float fov[1024][1024][2]) {

	w = width;
	h = height;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    float htr = toRadian(ht);
    float hpr = toRadian(hp);
    tileSize = w/3.0f;

	//rotation matrices
    float rot_y [3][3] = {
        {hls::cosf(hpr), 0, -hls::sinf(hpr)},
        {0, 1, 0},
        {hls::sinf(hpr), 0, hls::cosf(hpr)}
    };

    float rot_z [3][3] = {
        {hls::cosf(htr), hls::sinf(htr), 0},
        {-hls::sinf(htr), hls::cosf(htr), 0},
        {0, 0, 1}
    };

    float i = 45, j = -30.0;

	float p1[] = {0.0, 0.0, 0.0};
	float p2[] = {0.0, 0.0, 0.0};
	float p3[] = {0.0, 0.0, 0.0};
	float res[] = {0.0, 0.0};

    for (int a = 0; a < 1024; a++) {
	//#pragma HLS LOOP_TRIPCOUNT min=0 max=1024
    	    for (int b = 0; b < 1024; b++) {
			//#pragma HLS LOOP_TRIPCOUNT min=0 max=1024
			#pragma HLS PIPELINE

    			//rotation along y axis

    			spherical2cartesian(toRadian((j < 0) ? j + 360 : j), toRadian((i < 0) ? i + 180 : i),p1);

	    		j+= 0.05859f;

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

    		}
    	    i+= 0.08789f;
    }
}

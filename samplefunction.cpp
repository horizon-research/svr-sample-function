#include "samplefunction.h"


long double PI = 3.14159265358979323846;

int w ,h;

double tileSize;

double toRadian(double a){
    return a / 180.0 * PI;
}

void spherical2cartesian(long double the, long double phi,long double result [3]){

    long double x = sin(phi)*cos(the);
    long double y = sin(phi)*sin(the);
    long double z = cos(phi);

    result[0] = x;
    result[1] = y;
    result[2] = z;

}

void spherical2coordinates(long double the, long double phi,long double result [2]){

    long double i,j;

    if(the > PI){
        i = (the - PI) /2/PI *w;
    }
    else{
        i = (PI + the)/2/PI * w;
    }

    j = phi /  PI * h;

    result [0] = i;
    result [1] = j;

}

void cartesian2coordinates(long double x, long double y, long double z,long double result [2]){

    long double the;

    if(x != 0) {
        the = atan2(y,x);

    } else {
        the = toRadian(90);
    }

    long double phi = acos(z);
    spherical2coordinates(the,phi,result);
}

void matrixMultiplication(long double vector[3], long double matrix[3][3], long double result[3]) {


	result[0] = matrix[0][0] * vector[0] + matrix[0][1] * vector[1] + matrix[0][2] * vector[2];
	result[1] = matrix[1][0] * vector[0] + matrix[1][1] * vector[1] + matrix[1][2] * vector[2];
	result[0] = matrix[2][0] * vector[0] + matrix[2][1] * vector[1] + matrix[2][2] * vector[2];

}

void findPixel(int index, long double x,long double y,long double result [2]) {

    int vertical;
    if (index > 2) {
        vertical = 1;
    }
    else {
        vertical = 0;
    }
    long double n = (tileSize * (index%3))  + y * tileSize -1;
    long double m = (tileSize * vertical) + x * tileSize -1;

    result [0] = n;
    result [1] = m;

}

//from wikipedia: https://en.wikipedia.org/wiki/Cube_mapping
void convert_xyz_to_cube_uv(long double x, long double y, long double z,long double result [2]) {

    long double absX = fabs(x);
    long double absY = fabs(y);
    long double absZ = fabs(z);

    int isXPositive = x > 0 ? 1 : 0;
    int isYPositive = y > 0 ? 1 : 0;
    int isZPositive = z > 0 ? 1 : 0;

    long double maxAxis, uc, vc;
    long double u,v;
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

    findPixel(index, u, (1-v),result);
}

void convert(int width,int height,double hp,double ht,int fw,int fh, int fovX,int fovY,int option,long double fov[2000][2000][2]) {

	w = width;
	h = height;

    // ht is theta (horizontal), goes toward left first
    // hp is phi (vertical), goes toward up first
    long double htr = toRadian(ht);
    long double hpr = toRadian(hp);
    tileSize = w/3.0;

	//rotation matrices
    long double rot_y [3][3] = {
        {cos(hpr), 0, -sin(hpr)},
        {0, 1, 0},
        {sin(hpr), 0, cos(hpr)}
    };

    long double rot_z [3][3] = {
        {cos(htr), sin(htr), 0},
        {-sin(htr), cos(htr), 0},
        {0, 0, 1}
    };

    int a = 0,b = 0;

    for (long double i = 90  - fovY/2.0; i < 90 + fovY/2.0; i+= fovY*1.0/fh,b++) {
#pragma HLS LOOP_TRIPCOUNT min=0 max=100
    		for (long double j = -fovX/2.0; j < fovX/2.0; j+= fovX*1.0/fw,a++) {
#pragma HLS LOOP_TRIPCOUNT min=0 max=100

    			//rotation along y axis
    			long double p2[] = {0.0, 0.0, 0.0};
    			long double p1[] = {0.0, 0.0, 0.0};
    			spherical2cartesian(toRadian((j < 0) ? j + 360 : j), toRadian((i < 0) ? i + 180 : i),p1);
    			matrixMultiplication(p1,rot_y, p2);

    			//rotate along z axis
    			long double p3[] = {0.0, 0.0, 0.0};

    			matrixMultiplication(p2, rot_z, p3);

				long double res[] = {0.0, 0.0};
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
    		a = 0;

    }
}


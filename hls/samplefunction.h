#ifndef _SAMPLEFUNCTION_H_
#define _SAMPLEFUNCTION_H_

#include <cmath>
#include "ap_fixed.h"
#include  "hls_video.h"

typedef ap_fixed<32, 5, AP_RND, AP_WRAP> fp;
typedef hls::stream<ap_axiu<32,1,1,1> > AXI_STREAM;

#define WIDTH fp(6144)
#define HEIGHT fp(4096)
#define TILESIZE fp(2048)
#define PI fp(3.14159)

void crt(
	fp hp,
	fp ht,
	int option,
	int fov[1024][1024][2]
);

int nearestNeighbor(fp num);

fp toRadian(fp a);

fp absVal(fp num);

void spherical2cartesian(

	fp the,
	fp phi,
	fp result [3]
);

void spherical2coordinates(

	fp the,
	fp phi,
	fp result [2]
);

void cartesian2coordinates(

	fp x,
	fp y,
	fp z,
	fp result [2]

);

void matrixMultiplication(

	fp vector[3],
	fp matrix[3][3],
	fp result[3]

);

void findPixel(

	int index,
	fp x,
	fp y,
	fp result [2]

);

void convert_xyz_to_cube_uv(

	fp x,
	fp y,
	fp z,
	fp result [2]

);


#endif

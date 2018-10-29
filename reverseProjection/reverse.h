#ifndef _REVERSE_H_
#define _REVERSE_H_

#include "ap_fixed.h"
#include "hls_math.h"

typedef ap_fixed<17,14> indexes;
typedef ap_fixed<64,26> fp;
typedef ap_fixed<20,10> angle;

void crt(
	int width,
	int height,
	angle hp,
	angle ht,
	int option,
	int fov[481][483][2]
);

int nearestNeighbor(indexes num);

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
	indexes result [2]
);

void cartesian2coordinates(

	fp x,
	fp y,
	fp z,
	indexes result [2]

);

void matrixMultiplication(

	fp vector[3],
	fp matrix[3][3],
	fp result[3]

);


// new functions
void cartesian2coordintaes_inverse(

	fp x,
	fp y,
	fp z,
	indexes result[2]

);

void coordinates2spherical(

	indexes i,
	indexes j,
	fp result[2]

);

void cartesian2coordinates(

	fp x,
	fp y,
	fp z,
	indexes result[2]

);
void coordinates2cartesian(

	indexes i,
	indexes j,
	fp result[3]

);

#endif


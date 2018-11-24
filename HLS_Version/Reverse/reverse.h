#ifndef _REVERSE_H_
#define _REVERSE_H_

#define INPUT_WIDTH 720
#define INPUT_HEIGHT 480
#define fw 180
#define fh 120

#include "ap_fixed.h"
#include "hls_math.h"
#include "hls_video.h"

typedef ap_fixed<28,14> fp;

typedef hls::stream<ap_axiu<32,1,1,1> > AXI_STREAM;
typedef hls::Scalar<3, unsigned char> RGB_PIXEL;


void crt(
	AXI_STREAM& INPUT_STREAM,
	AXI_STREAM& OUTPUT_STREAM,
	double theta,
	double phi
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


// new functions
void cartesian2coordintaes_inverse(

	fp x,
	fp y,
	fp z,
	fp result[2]

);

void coordinates2spherical(

	fp i,
	fp j,
	fp result[2]

);

void cartesian2coordinates(

	fp x,
	fp y,
	fp z,
	fp result[2]

);
void coordinates2cartesian(

	fp i,
	fp j,
	fp result[3]

);


#endif


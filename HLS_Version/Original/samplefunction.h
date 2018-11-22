#ifndef _SAMPLEFUNCTION_H_
#define _SAMPLEFUNCTION_H_

#include "ap_fixed.h"
#include "hls_math.h"
#include "hls_video.h"

typedef ap_fixed<28,14> fp;
typedef ap_fixed<28,14> indices;
typedef ap_fixed<28,14> angle;
typedef hls::stream<ap_axiu<32,1,1,1> > AXI_STREAM;
typedef hls::Scalar<3, unsigned char> RGB_PIXEL;


void crt(
	AXI_STREAM& INPUT_STREAM,
	AXI_STREAM& OUTPUT_STREAM
);

int nearestNeighbor(indices num);

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
	indices result [2]
);

void cartesian2coordinates(

	fp x,
	fp y,
	fp z,
	indices result [2]

);

void matrixMultiplication(

	fp vector[3],
	fp matrix[3][3],
	fp result[3]

);


#endif

#ifndef _SAMPLEFUNCTION_H_
#define _SAMPLEFUNCTION_H_

#include "ap_fixed.h"
#include "hls_math.h"
#include "hls_video.h"

typedef ap_fixed<17,14> indexes;
typedef ap_fixed<28,10> fp;
typedef ap_fixed<20,10> angle;
typedef hls::stream<ap_axiu<32,1,1,1> > AXI_STREAM;
typedef hls::Scalar<3, unsigned char> RGB_PIXEL;

//void crt(
//	int width,
//	int height,
//	angle hp,
//	angle ht,
//	int option,
//	AXI_STREAM& INPUT_STREAM,
//	AXI_STREAM& OUTPUT_STREAM
//);

void crt(
	AXI_STREAM& INPUT_STREAM,
	AXI_STREAM& OUTPUT_STREAM
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

void findPixel(

	int index,
	fp x,
	fp y,
	indexes result [2]

);

void convert_xyz_to_cube_uv(

	fp x,
	fp y,
	fp z,
	indexes result [2]

);

void findPixel_EAC(

	int index,
	fp u,
	fp v,
	indexes result [2]

);

void convert_EAC(

	fp x,
	fp y,
	fp z,
	indexes result [2]

);

//void countPixel(
//
//	hls::Mat<4096,6144,HLS_8UC3>image,
//	RGB_PIXEL pixel,
//	int indexI,
//	int indexJ
//
//);

#endif

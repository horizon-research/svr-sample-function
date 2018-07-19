#ifndef SAMPLEFUNCTION_H
#define SAMPLEFUNCTION_H

#include <cmath>
#include <hls_math.h>
#include <ap_fixed.h>

typedef ap_fixed<29,3> degree;

extern void convert (

	int width,
	int height,
	float hp,
	float ht,
	int fw,
	int fh,
	int fovX,
	int fovY,
	int option,
	float fov[1024][1024][2]
);

extern float toRadian(degree a);

extern void spherical2cartesian(

	float the,
	float phi,
	float result [3]
);

extern void spherical2coordinates(

	float the,
	float phi,
	float result [2]
);

extern void cartesian2coordinates(

	float x,
	float y,
	float z,
	float result [2]

);

extern void matrixMultiplication(

	float vector[3],
	float matrix[3][3],
	float result[3]

);

extern void findPixel(

	int index,
	float x,
	float y,
	float result [2]

);

extern void convert_xyz_to_cube_uv(

	float x,
	float y,
	float z,
	float result [2]

);

#endif

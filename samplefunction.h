#ifndef SAMPLEFUNCTION_H
#define SAMPLEFUNCTION_H

#include <hls_math.h>

extern void convert (

	int width,
	int height,
	double hp,
	double ht,
	int fw,
	int fh,
	int fovX,
	int fovY,
	int option,
	long double fov[2000][2000][2]
);

extern double toRadian(double a);

extern void spherical2cartesian(

	long double the,
	long double phi,
	long double result [3]
);

extern void spherical2coordinates(

	long double the,
	long double phi,
	long double result [2]
);

extern void cartesian2coordinates(

	long double x,
	long double y,
	long double z,
	long double result [2]

);

extern void matrixMultiplication(

	long double vector[3],
	long double matrix[3][3],
	long double result[3]

);

extern void findPixel(

	int index,
	long double x,
	long double y,
	long double result [2]

);

extern void convert_xyz_to_cube_uv(

	long double x,
	long double y,
	long double z,
	long double result [2]

);

#endif

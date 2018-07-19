#ifndef SAMPLEFUNCTION_H
#define SAMPLEFUNCTION_H

#include <hls_math.h>
#include <ap_fixed.h>

typedef ap_fixed<11,5> fp;

extern void crt (

	int width,
	int height,
	fp hp,
	fp ht,
	int fw,
	int fh,
	int fovX,
	int fovY,
	int option,
	int fov[1024][1024][2]
);

extern fp toRadian(fp a);

extern fp absVal(fp num);

extern void calSin(

	fp angle,
	fp output

);

extern void calCos(

	fp angle,
	fp output

);

extern void calAtan2(

	fp angle1,
	fp angle2,
	fp output

);

extern void calAcos(

	fp angle,
	fp output

);

extern void spherical2cartesian(

	fp the,
	fp phi,
	fp result [3]
);

extern void spherical2coordinates(

	fp the,
	fp phi,
	fp result [2]
);

extern void cartesian2coordinates(

	fp x,
	fp y,
	fp z,
	fp result [2]

);

extern void matrixMultiplication(

	fp vector[3],
	fp matrix[3][3],
	fp result[3]

);

extern void findPixel(

	int index,
	fp x,
	fp y,
	fp result [2]

);

extern void convert_xyz_to_cube_uv(

	fp x,
	fp y,
	fp z,
	fp result [2]

);

#endif

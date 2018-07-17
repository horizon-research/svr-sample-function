#ifndef SAMPLEFUNCTION_H
#define SAMPLEFUNCTION_H

#include <hls_math.h>
#include <ap_fixed.h>

typedef ap_fixed<5,10> angles;
typedef ap_fixed<10,10> indexes;

extern void convert (

	int width,
	int height,
	angles hp,
	angles ht,
	int fw,
	int fh,
	int fovX,
	int fovY,
	int option,
	float fov[1024][1024][2]
);

extern angles toRadian(angles a);

extern angles absVal(angles num);

extern void calSin(

	angles angle,
	angles output

);

extern void calCos(

	angles angle,
	angles output

);

extern void calAtan2(

	angles angle1,
	angles angle2,
	angles output

);

extern void calAcos(

	angles angle,
	angles output

);

extern void spherical2cartesian(

	angles the,
	angles phi,
	angles result [3]
);

extern void spherical2coordinates(

	angles the,
	angles phi,
	indexes result [2]
);

extern void cartesian2coordinates(

	angles x,
	angles y,
	angles z,
	indexes result [2]

);

extern void matrixMultiplication(

	angles vector[3],
	angles matrix[3][3],
	angles result[3]

);

extern void findPixel(

	int index,
	angles x,
	angles y,
	indexes result [2]

);

extern void convert_xyz_to_cube_uv(

	angles x,
	angles y,
	angles z,
	indexes result [2]

);

#endif

/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/

#ifndef _LINESEG3_H
#define _LINESEG3_H

#include "point3.h"

struct lineSeg3 {
	point3 v0,v1;

	lineSeg3( const point3 &a, const point3 &b ){
		v0 = a; v1 = b;
	}
	lineSeg3(){}
};

#endif//_LINESEG3_H
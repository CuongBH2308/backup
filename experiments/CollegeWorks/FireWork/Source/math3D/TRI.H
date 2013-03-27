/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/

#ifndef _TRI_H
#define _TRI_H


//triangle
template <class type>
struct tri 
{

    type v[3]; // Array access useful in for loops,its 3 points
	
	tri()
	{
		// nothing
	}

	tri( type v0, type v1, type v2 )
	{
		v[0] = v0;
		v[1] = v1;
		v[2] = v2;
	}
};

#endif //_TRI_H
/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/

#ifndef _PLANE3_H
#define _PLANE3_H

#include "point3.h"
#include "bSphere3.h"
#include "polygon.h"

//平面

// Defines the three possible locations of a point in 
// relation to a plane
//点面之间 的关系
enum ePointLoc
{
	ptFront,
	ptBack,
	ptCoplanar
};

// Defines the four possible locations of a point list in 
// relation to a plane.  A point list is a more general
// example of a polygon.

//点集和面之间的关系
enum ePListLoc
{
	plistFront,
	plistBack,
	plistSplit,
	plistCoplanar
};

//球面之间的关系
enum eSphereLoc
{
	sphereFront, // Sphere was entirely in front
	sphereBack, // Sphere was entirely in back
	sphereCoplanar // Sphere was partially on either side
};
//表示线段
struct lineSeg3;

struct plane3 {

	//平面方程:n.v+d=0

	point3 n; // Normal of the plane

	float d; // Distance along the normal to the origin 

	plane3( float nX, float nY, float nZ, float D) : n( nX, nY, nZ ), d( D )
	{
		// All done.
	}
	plane3( const point3& N, float D) : n( N ), d( D )
	{
		// All done.
	}

	// Construct a plane from three 3-D points
	plane3( const point3& a, const point3& b, const point3& c);

	// Construct a plane from a normal direction and a point on the plane
	plane3( const point3& norm, const point3& loc);

	// Construct a plane from a polygon
	plane3( const polygon<point3>& poly );

	plane3()
	{
		// Do nothing
	}

	ePointLoc TestPoint( const point3& point ) const;// tests a point against this plane
	ePListLoc TestPoly( const polygon<point3> &poly ) const;// can test lines, polys, and bboxes.
	ePListLoc TestPList( point3 *list, int num ) const;// can test lines, polys, and bboxes.
	eSphereLoc TestBSphere( const bSphere3& sphere ) const;

	const point3 Split( const point3 &a, const point3 &b ) const;

	const point3 BringToPlane( const point3& pt );

	// These functions all assume the output polygons have adequate space in them.
	bool Clip( const polygon<point3>& in, polygon<point3> *out ) const;
	bool Split( const polygon<point3>& in, polygon<point3> *front, polygon<point3> *back ) const;
	bool Split( const lineSeg3& in, lineSeg3 *front, lineSeg3 *back ) const;

	// Flip the orientation of the plane
	void Flip();
};

inline plane3::plane3( const point3& a, const point3& b, const point3& c)
{
	n = (b-a)^(c-a);
	n.Normalize();
	d = -(n*a);  //n*a+d = 0 .because a is a point on the plane
}

inline plane3::plane3( const point3& norm, const point3& loc) : 
    n( norm ), d( -(norm*loc) ) //loc is a point on the plane
{
    // all done
}

inline plane3::plane3( const polygon<point3>& poly ) //多边形确定平面
{
	//三点确定一平面,我只取其三点即可
	point3 a = poly.pList[0];
	point3 b = poly.pList[1];
	point3 c = poly.pList[2];

	n = (b-a)^(c-a);
	n.Normalize();
	d = -(n*a);
}

// we're inlineing this because we do it constantly
inline ePointLoc plane3::TestPoint( point3 const &point ) const
{
	float dp = (point * n) + d; //calculate the distance between point and the plane

	if(dp > EPSILON)
	{
		return ptFront;
	}

	if(dp < -EPSILON )
	{
		return ptBack;
	}

	return ptCoplanar; // it was between EP and -EP
}

//求出直线与平面的交点
//why???  just look at sd mathematics p59  
// p = a+t(b-a)   1 
// n.p+d=0        2
//求出t,代入式1
inline const point3 plane3::Split( const point3 &a, const point3 &b ) const
{
	float aDot = (a * n);
	float bDot = (b * n);

	float scale = ( -d - aDot ) / ( bDot - aDot ); //why add -d here

	return a + (scale * (b - a));
}

//将点投影到平面上
inline const point3 plane3::BringToPlane( const point3& pt )
{
	float distToPlane = (pt * n); //

	return point3( pt - (d + distToPlane)*n );  //(d + distToPlane)点到平面的距离,对的
}

//// Flip the orientation of the plane
void inline plane3::Flip()
{
	n = -n;
	d = -d;
}

//returns true if point3==point3
inline bool operator==(plane3 const &a, plane3 const &b)
{
	if( fabs(a.d-b.d) < EPSILON )
		if( a.n == b.n )
			return true;
	return false;
};

#endif /*_PLANE3_H*/
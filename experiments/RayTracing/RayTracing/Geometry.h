#pragma once
#include <cassert>
#include <vector>
#include <istream>
#include <cmath>
#include <xmmintrin.h>

#include "Profiler.h"
using namespace std;
#define dbger_inline __forceinline
// Data structures
struct F3d
{
	float x, y, z;
};

struct vector3d
{
	vector3d():x(0), y(0), z(0){}
	vector3d(float _x, float _y, float _z):x(_x), y(_y), z(_z){}

	float x, y, z;

	//union
	//{
	//	struct {float x, y, z;};
	//	struct {float cell[3];};
	//};
};

struct point3d
{
	point3d():x(0), y(0), z(0){}
	point3d(float _x, float _y, float _z):x(_x), y(_y), z(_z){}


	float x, y, z;
	//union
	//{
	//	struct {float x, y, z;};
	//	struct {float cell[3];};
	//};
};

struct ray
{
	point3d origin;
	vector3d direction;
	float divx;
	float divy;
	float divz;
};

struct triangle
{
	point3d v0, v1, v2;
};

struct cube 
{
	point3d center;
	float halfsize;
};

struct box
{
	point3d minV;
	point3d maxV;
};
dbger_inline std::ostream& operator << (std::ostream& os , const vector3d& v)
{
	os << "vector3d(";
	os << v.x <<",";
	os << v.y <<",";
	os << v.z;
	os << ")";
	return os;
}

dbger_inline std::ostream& operator << (std::ostream& os , const point3d& p)
{
	os << "point3d(";
	os << p.x <<",";
	os << p.y <<",";
	os << p.z;
	os << ")";
	return os;
}

// functions
dbger_inline bool FloatEqual(float f1, float f2, int maxUlps = 4)
{
	//return fabs(f1 - f2) < 0.001;
	// Make sure maxUlps is non-negative and small enough that the
	// default NAN won't compare as equal to anything.
	assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
	int aInt = *(int*)&f1;
	// Make aInt lexicographically ordered as a twos-complement int
	if (aInt < 0)
		aInt = 0x80000000 - aInt;
	// Make bInt lexicographically ordered as a twos-complement int
	int bInt = *(int*)&f2;
	if (bInt < 0)
		bInt = 0x80000000 - bInt;
	int intDiff = abs(aInt - bInt);
	if (intDiff <= maxUlps)
		return true;
	return false;
}
dbger_inline vector3d operator - (const point3d& start, const point3d& end)
{
	return vector3d(start.x-end.x, start.y-end.y, start.z-end.z);
}

dbger_inline point3d operator + (const point3d& start, const vector3d& dir)
{
	//__m128 m1 = _mm_set_ps(start.x, start.y, start.z, 0.0f);
	//__m128 m2 = _mm_set_ps(dir.x, dir.y, dir.z, 0.0f);
	//__m128 mres = _mm_add_ps(m1, m2);

	//return point3d(mres.m128_f32[0], mres.m128_f32[1], mres.m128_f32[2]);
	return point3d(start.x+dir.x, start.y+dir.y, start.z+dir.z);
}

dbger_inline bool operator == (const point3d& p1, const point3d& p2)
{
	return (FloatEqual(p1.x, p2.x) && FloatEqual(p1.y, p2.y) && FloatEqual(p1.z,p2.z));
}

dbger_inline bool operator == (const vector3d& v1, const vector3d& v2)
{
	return (FloatEqual(v1.x, v2.x) && FloatEqual(v1.y, v2.y) && FloatEqual(v1.z,v2.z));
}

//vector3d operator + (const vector3d& v1, const vector3d& v2)
//{
//	return point3d(v1.x+v2.x, v1.y+v2.x, v1.z+v2.z);
//}
//
//vector3d operator - (const vector3d& v1, const vector3d& v2)
//{
//	return point3d(v1.x-v2.x, v1.y-v2.x, v1.z-v2.z);
//}

dbger_inline vector3d operator * (float f, const vector3d& v)
{
	return vector3d(f*v.x, f*v.y, f*v.z);
}


// Dot Product
dbger_inline float operator * (const vector3d& v1, const vector3d& v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// Cross Product
dbger_inline vector3d operator ^ (const vector3d& v1, const vector3d& v2)
{
	return vector3d(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}

dbger_inline void Normalize(vector3d& v)
{
	float norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x = v.x / norm;
	v.y = v.y / norm;
	v.z = v.z / norm;
}
dbger_inline bool RayTriangleIntersection(const ray& ray, const triangle& tri, point3d& intersection)
{
	//PROFILE_SCOPE("RayTriangleIntersection");
	//ray.origin + t * ray.direction = (1-(u+v)) * tri.v0 + u * tri.v1 + v * tri.v2;
	//if t<0, opposite diretion
	//if not 0.0=<u, v<=1.0, not in triangle
	vector3d edge1, edge2, tvec, pvec, qvec;
	float t, u, v, det, inv_det;
	edge1 = tri.v1 - tri.v0;
	edge2 = tri.v2 - tri.v0;
	pvec = ray.direction ^ edge2;
	det = pvec * edge1;
	if(FloatEqual(det, 0)) return false;

	// u
	inv_det = 1.0f / det;
	tvec = ray.origin - tri.v0;

	u = (tvec * pvec) * inv_det;
	if(u < 0.0 || u > 1.0) return false;

	// v
	qvec = tvec ^ edge1;
	v = inv_det * (ray.direction * qvec);
	if(v < 0.0 || v > 1.0) return false;

	if(u + v > 1.0f) return false;

	// t
	t = inv_det * (edge2 * qvec);
	if(t < 0.0) return false;

	intersection = ray.origin + t * ray.direction;

	return true;
}

// check the plug:
// error: && or || here - you need through unit testing
// cross product & point & plus fault

dbger_inline bool PointInCube(const point3d& p, const cube& c)
{
	if(((p.x <= c.center.x + c.halfsize) && (p.x >= c.center.x - c.halfsize)) && 
		((p.y <= c.center.y + c.halfsize) && (p.y >= c.center.y - c.halfsize)) &&
		((p.z <= c.center.z + c.halfsize) && (p.z >= c.center.z - c.halfsize)))
		return true;

	return false;
}



// Find a more effective one!!!
dbger_inline bool TriInCube(const triangle& t, const cube& c)
{
	//PROFILE_SCOPE("TriInCube");
	if (PointInCube(t.v0, c) && PointInCube(t.v1, c) && PointInCube(t.v2, c))
	{
		return true;
	}
	return false;
}

dbger_inline bool TriIntersectCube(const triangle& t, const cube& c)
{
	//PROFILE_SCOPE("TriInCube");
	if (PointInCube(t.v0, c) || PointInCube(t.v1, c) || PointInCube(t.v2, c))
	{
		return true;
	}
	return false;
}

dbger_inline bool RayIntersectWithCube(const ray& r, const cube& c)
{
	//PROFILE_SCOPE("RayIntersectWithCube");
	point3d minp = c.center + c.halfsize * vector3d(-1, -1, -1);
	point3d maxp = c.center + c.halfsize * vector3d(1, 1, 1);


	float txmin = 0, txmax = 0, tymin = 0, tymax = 0, tzmin = 0, tzmax = 0;

	//
	if (r.divx >= 0)
	{
		txmin = (minp.x - r.origin.x) * r.divx;
		txmax = (maxp.x - r.origin.x) * r.divx;
	}
	else
	{
		txmin = (maxp.x - r.origin.x) * r.divx;
		txmax = (minp.x - r.origin.x) * r.divx;
	}

	if (r.divy >= 0)
	{
		tymin = (minp.y - r.origin.y) * r.divy;
		tymax = (maxp.y - r.origin.y) * r.divy;
	}
	else
	{
		tymin = (maxp.y - r.origin.y) * r.divy;
		tymax = (minp.y - r.origin.y) * r.divy;
	}

	if (tymin > txmax || txmin > tymax) return false;
	if (tymin > txmin) txmin = tymin;
	if (tymax < txmax) txmax = tymax;

	if (r.divz >= 0)
	{
		tzmin = (minp.z - r.origin.z) * r.divz;
		tzmax = (maxp.z - r.origin.z) * r.divz;
	}
	else
	{
		tzmin = (maxp.z - r.origin.z) * r.divz;
		tzmax = (minp.z - r.origin.z) * r.divz;
	}
	if (txmin > tzmax || tzmin > txmax) return false;

	return true;
}

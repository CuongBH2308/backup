/////////////////////////////////////////////////////////////////////////
// All rights reserved
//
// Use and distribute freely, except: don't remove my name from the
// source or documentation (don't take credit for my work), mark your
// changes and extend the author list below, don't alter or remove this notice.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.
// xiezheheng@yahoo.com
//
// Author list: Zheheng XIE
//
/////////////////////////////////////////////////////////////////////////


#pragma once

/************************************************************************/
/* 
Local Coordinate System.
pt(a,b,c) in this local system is the same as pt(x,y,z) in world system 
*/
/************************************************************************/

#include "mh_point3.h"
#include "mh_vector3.h"
#include "mh_matrix44.h"

class MH_Plane;
class MH_CrdSys
{
public:
	MH_CrdSys(const MH_Plane& plane);
	MH_CrdSys(const MH_Point3& ptOrigin, const MH_Vector3& vZAxis);
	MH_CrdSys(const MH_Point3& ptOrigin, const MH_Vector3& vZAxis, const MH_Vector3& vXAxis);
	MH_CrdSys(const MH_Matrix44& mtx);
	virtual ~MH_CrdSys(void);

	// Generate the coordinate system
	void Generate(const MH_Point3& ptOrigin, const MH_Vector3& vZAxis);

	// Set cs's origin.
	void SetOrigin(const MH_Point3& ptOrgin);

	// Get cs's origin.
	const MH_Point3& GetOrigin() const;

	// Set X Axis
	void SetXAxis(const MH_Vector3& v);

	// Get cs's X axis.
	const MH_Vector3& GetXAxis() const;

	// Set Y Axis
	void SetYAxis(const MH_Vector3& v);

	// Get cs's Y axis.
	const MH_Vector3& GetYAxis() const;

	// Set Z Axis
	void SetZAxis(const MH_Vector3& v);

	// Get cs's Z axis.
	const MH_Vector3& GetZAxis() const;

	// Get point in world system
	// pt(a,b) in this local system is the same as pt(x,y,z) in world system 
	MH_Point3 PointAt(float a, float b) const;

	// Get point in world system
	// pt(a,b,c) in this local system is the same as pt(x,y,z) in world system 
	MH_Point3 PointAt(float a, float b, float c) const;

	// Get transform matrix
	// m_mtxTransform will help to transform pt in local system into world coordinate system 
	// Transpose([x,y,z,1]) = m_mtxTransform * Transpose([a,b,c,1])
	const MH_Matrix44& GetTransform() const;
private:
	MH_Point3  m_ptOrigin;
	MH_Vector3 m_vXAxis;
	MH_Vector3 m_vYAxis;
	MH_Vector3 m_vZAxis;
	MH_Matrix44 m_mtxTransform;
};

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


#include "StdAfx.h"
#include ".\mh_crdsys.h"
#include "MH_Plane.h"

MH_CrdSys::MH_CrdSys(const MH_Plane& plane)
{
	Generate(plane.GetPoint(), plane.GetNormal());
}

MH_CrdSys::MH_CrdSys(const MH_Point3& ptOrigin, const MH_Vector3& vZAxis)
{
	Generate(ptOrigin, vZAxis);
}

MH_CrdSys::MH_CrdSys(const MH_Point3& ptOrigin, const MH_Vector3& vZAxis, const MH_Vector3& vXAxis)
:m_ptOrigin(ptOrigin),
m_vXAxis(vXAxis),
m_vYAxis(vZAxis^vXAxis),
m_vZAxis(vZAxis)
{
	// 1st row 
	m_mtxTransform[0]	= m_vXAxis.m_f[0];
	m_mtxTransform[1]	= m_vYAxis.m_f[0];
	m_mtxTransform[2]	= m_vZAxis.m_f[0];
	m_mtxTransform[3]	= m_ptOrigin.m_f[0];

	// 2nd row
	m_mtxTransform[4]	= m_vXAxis.m_f[1];
	m_mtxTransform[5]	= m_vYAxis.m_f[1];
	m_mtxTransform[6]	= m_vZAxis.m_f[1];
	m_mtxTransform[7]	= m_ptOrigin.m_f[1];

	// 3rd row
	m_mtxTransform[8]	= m_vXAxis.m_f[2];
	m_mtxTransform[9]	= m_vYAxis.m_f[2];
	m_mtxTransform[10]	= m_vZAxis.m_f[2];
	m_mtxTransform[11]	= m_ptOrigin.m_f[2];

	// 4th
	m_mtxTransform[12] = 0;
	m_mtxTransform[13] = 0;
	m_mtxTransform[14] = 0;
	m_mtxTransform[15] = 1;
}

MH_CrdSys::MH_CrdSys(const MH_Matrix44& mtx)
{
	m_mtxTransform = mtx;

	// 1st row 
	m_vXAxis.m_f[0] = m_mtxTransform[0];
	m_vYAxis.m_f[0] = m_mtxTransform[1];
	m_vZAxis.m_f[0] = m_mtxTransform[2];
	m_ptOrigin.m_f[0] = m_mtxTransform[3];

	// 2nd row
	m_vXAxis.m_f[1] = m_mtxTransform[4];
	m_vYAxis.m_f[1] = m_mtxTransform[5];
	m_vZAxis.m_f[1] = m_mtxTransform[6];
	m_ptOrigin.m_f[1] = m_mtxTransform[7];

	// 3rd row
	m_vXAxis.m_f[2] = m_mtxTransform[8];
	m_vYAxis.m_f[2] = m_mtxTransform[9];
	m_vZAxis.m_f[2] = m_mtxTransform[10];
	m_ptOrigin.m_f[2] = m_mtxTransform[11];
}

MH_CrdSys::~MH_CrdSys(void)
{
}

// Generate the coordinate system
void MH_CrdSys::Generate(const MH_Point3& ptOrigin, const MH_Vector3& vZAxis)
{
	m_ptOrigin	= ptOrigin;
	m_vZAxis	= vZAxis;

	MH_Point3 ptInXYPlane;
	if(m_vZAxis.m_f[2] != 0.0)
	{
		ptInXYPlane.m_f[0] = m_ptOrigin.m_f[0]+1.0f;
		ptInXYPlane.m_f[1] = m_ptOrigin.m_f[1];
		ptInXYPlane.m_f[2] = m_ptOrigin.m_f[2]-m_vZAxis.m_f[0]/m_vZAxis.m_f[2];
	}
	else if(m_vZAxis.m_f[1] != 0.0)
	{
		ptInXYPlane.m_f[0] = m_ptOrigin.m_f[0]+1.0f;
		ptInXYPlane.m_f[1] = m_ptOrigin.m_f[1]-m_vZAxis.m_f[0]/m_vZAxis.m_f[1];
		ptInXYPlane.m_f[2] = m_ptOrigin.m_f[2];
	}
	else if(m_vZAxis.m_f[0] != 0.0)
	{
		ptInXYPlane.m_f[0] = m_ptOrigin.m_f[0]-m_vZAxis.m_f[1]/m_vZAxis.m_f[0];
		ptInXYPlane.m_f[1] = m_ptOrigin.m_f[1]+1.0f;
		ptInXYPlane.m_f[2] = m_ptOrigin.m_f[2];
	}
	m_vXAxis = ptInXYPlane-m_ptOrigin;
	m_vXAxis.Normalize();

	m_vYAxis = m_vZAxis^m_vXAxis;

	// 1st row 
	m_mtxTransform[0]	= m_vXAxis.m_f[0];
	m_mtxTransform[1]	= m_vYAxis.m_f[0];
	m_mtxTransform[2]	= m_vZAxis.m_f[0];
	m_mtxTransform[3]	= m_ptOrigin.m_f[0];

	// 2nd row
	m_mtxTransform[4]	= m_vXAxis.m_f[1];
	m_mtxTransform[5]	= m_vYAxis.m_f[1];
	m_mtxTransform[6]	= m_vZAxis.m_f[1];
	m_mtxTransform[7]	= m_ptOrigin.m_f[1];

	// 3rd row
	m_mtxTransform[8]	= m_vXAxis.m_f[2];
	m_mtxTransform[9]	= m_vYAxis.m_f[2];
	m_mtxTransform[10]	= m_vZAxis.m_f[2];
	m_mtxTransform[11]	= m_ptOrigin.m_f[2];

	// 4th
	m_mtxTransform[12] = 0;
	m_mtxTransform[13] = 0;
	m_mtxTransform[14] = 0;
	m_mtxTransform[15] = 1;
}

// Set cs's origin.
void MH_CrdSys::SetOrigin(const MH_Point3& ptOrgin)
{
	m_ptOrigin = ptOrgin;
}

// Get cs's origin.
const MH_Point3& MH_CrdSys::GetOrigin() const
{
	return m_ptOrigin;
}

// Set X Axis
void MH_CrdSys::SetXAxis(const MH_Vector3& v)
{
	m_vXAxis = v;
}

// Get cs's X axis.
const MH_Vector3& MH_CrdSys::GetXAxis() const
{
	return m_vXAxis;
}

// Set Y Axis
void MH_CrdSys::SetYAxis(const MH_Vector3& v)
{
	m_vYAxis = v;
}

// Get cs's Y axis.
const MH_Vector3& MH_CrdSys::GetYAxis() const
{
	return m_vYAxis;
}

// Set Z Axis
void MH_CrdSys::SetZAxis(const MH_Vector3& v)
{
	m_vZAxis = v;
}

// Get cs's Z axis.
const MH_Vector3& MH_CrdSys::GetZAxis() const
{
	return m_vZAxis;
}

// Get point in world system
// pt(a,b) in this local system is the same as pt(x,y,z) in world system 
MH_Point3 MH_CrdSys::PointAt(float a, float b) const
{
	return (m_ptOrigin + m_vXAxis*a + m_vYAxis*b);
}

// Get point in world system
// pt(a,b,c) in this local system is the same as pt(x,y,z) in world system 
MH_Point3 MH_CrdSys::PointAt(float a, float b, float c) const
{
	return (m_ptOrigin + m_vXAxis*a + m_vYAxis*b + m_vZAxis*c);
}

// Get transform matrix
// (x,y,z,1)t = m_mtxTransform * (a,b,c)t
// pt(a,b,c) in this local system is the same as pt(x,y,z) in world system 
const MH_Matrix44& MH_CrdSys::GetTransform() const
{
	return m_mtxTransform;
}

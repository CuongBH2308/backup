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
#include "mh_obj.h"

class MH_Matrix44;
class MH_Vector3 : public MH_Obj
{
public:
	MH_Vector3(void);
	MH_Vector3(float x, float y, float z);
	virtual ~MH_Vector3(void);

	// Transform this vector
	// v = mtx * [m_f[0], m_f[1], m_f[2], 1]t
	virtual void Transform(const MH_Matrix44& mtx);

	void Set(float x, float y, float z);

	// Normalize vector
	void Normalize();  

	// If m_f[0]==m_f[1]==m_f[2] return false
	bool IsValid() const;

	bool		operator ==(const MH_Vector3& A) const; // Equal (==)
	MH_Vector3& operator = (const MH_Vector3& A);       // ASSIGNMENT (=)
	MH_Vector3  operator + (const MH_Vector3& A) const; // ADDITION (+)
	MH_Vector3	operator - (const MH_Vector3& A) const; // SUBTRACTION (-)
	float operator * (const MH_Vector3& A) const;		// DOT-PRODUCT (*)
	MH_Vector3	operator ^ (const MH_Vector3& A) const; // CROSS-PRODUCT (/)
	MH_Vector3	operator * (const float s) const;		// MULTIPLY BY SCALAR (*)
	MH_Vector3	operator / (const float s) const;		// DIVIDE BY SCALAR (/)
	float		operator / (const MH_Vector3& A) const;	// This should be parallel to A
	void		operator +=(const MH_Vector3 A);        // ACCUMULATED VECTOR ADDITION (+=)
	void		operator -=(const MH_Vector3 A);        // ACCUMULATED VECTOR SUBTRACTION (+=)
	void		operator *=(const float s);				// ACCUMULATED SCALAR MULT (*=)
	void		operator /=(const float s);				// ACCUMULATED SCALAR DIV (/=)
	MH_Vector3  operator - (void) const;				// NEGATION (-)

	float m_f[3];
};

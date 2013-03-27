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

/************************************************************************/
/*
	| 00, 01, 02, 03 |
	| 10, 11, 12, 13 |
	| 20, 21, 22, 23 |
	| 30, 31, 32, 33 |                                                            
*/
/************************************************************************/

class MH_Vector3;
class MH_Matrix44 : public MH_Obj
{
	friend class MH_Point4;
public:
	MH_Matrix44(void);
	virtual ~MH_Matrix44(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Identify this matrix
	void Identity();

	// Cross-Product
	MH_Matrix44 operator*(const MH_Matrix44& m) const;

	// Assignment (=)
	MH_Matrix44& operator = (const MH_Matrix44& m);      

	// Get m_f[i/4][i%4]
	float& operator [] (const int& i);

	// Get m_f[i/4][i%4]
	const float& operator [] (const int& i) const;

	// Reverse-Matrix
	MH_Matrix44 Reverse() const;

	// Transpose-Matrix
	MH_Matrix44 Transpose() const;

	// Get the translation matrix
	static MH_Matrix44 Translate(const MH_Vector3& v);
private:
	float m_f[4][4];
};

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


#include "stdafx.h"
#include "dr_stvector3.h"

DR_StVector3::DR_StVector3(const SL_Ptr<DR_Fragment>& pFragment)
:DR_StVector(pFragment)
{
}

DR_StVector3::~DR_StVector3(void)
{
}

// Set the vector
void DR_StVector3::SetV(const MH_Vector3& v)
{
	m_vVector = v;
}

// Get the vector
const MH_Vector3& DR_StVector3::GetV() const
{
	return m_vVector;
}
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
#include "dr_stvector.h"
#include "mh_vector3.h"

class DR_StVector3 : public DR_StVector
{
public:
	DR_StVector3(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_StVector3(void);

	// Set the vector
	void SetV(const MH_Vector3& v);

	// Get the vector
	const MH_Vector3& GetV() const;
private:
	MH_Vector3 m_vVector;
};

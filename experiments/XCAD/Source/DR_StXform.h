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
#include "dr_st.h"
#include "mh_matrix44.h"

class DR_StXform : public DR_St
{
public:
	DR_StXform(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_StXform(void);

	// Set transform matrix
	void SetXform(const MH_Matrix44& mtx);

	// Get transform matrix
	const MH_Matrix44& GetXform() const;
private:
	MH_Matrix44 m_mtx;
};

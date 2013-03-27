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
#include "mh_plane.h"

//////////////////////////////////////////////////////////////////////////
// Plane 
//////////////////////////////////////////////////////////////////////////
class DR_StPlane : public DR_St
{
public:
	DR_StPlane(const SL_Ptr<DR_Fragment>& pFragment, const MH_Plane& plane);
	virtual ~DR_StPlane(void);

	// Set plane
	void SetPlane(const MH_Plane& plane);

	// Get plane
	const MH_Plane& GetPlane() const;
private:
	MH_Plane m_plane;
};

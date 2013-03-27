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
#include "gr_dlnode.h"

class DR_StPlane;
class GR_DLSrf;
class GR_DLNodeWorkplane : public GR_DLNode
{
public:
	GR_DLNodeWorkplane(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<DR_StPlane>& pStPlane, const MH_Vector3& vAxis);
	virtual ~GR_DLNodeWorkplane(void);

	// Get plane
	const SL_Ptr<DR_StPlane>& GetStPlane() const;

private:
	SL_Ptr<DR_StPlane>	m_pStPlane;
};

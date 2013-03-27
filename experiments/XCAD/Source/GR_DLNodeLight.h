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
#include "mh_point3.h"
#include "mh_vector3.h"

class GR_DLNodeLight : public GR_DLNode
{
public:
	GR_DLNodeLight(const SL_Ptr<GR_DLNode>& pParentNode,
		const MH_Point3& pt,
		GR_Selector* pSelector = NULL);
	GR_DLNodeLight(const SL_Ptr<GR_DLNode>& pParentNode,
		const MH_Point3& pt,
		const MH_Vector3& vDir,
		GR_Selector* pSelector = NULL);
	virtual ~GR_DLNodeLight(void);

private:
	MH_Point3	m_pt;
	MH_Vector3	m_vDir;
};

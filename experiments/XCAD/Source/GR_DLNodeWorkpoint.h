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

class DR_StPoint;
class GR_DLNode;
class GR_DLNodeWorkpoint : public GR_DLNode
{
public:
	GR_DLNodeWorkpoint(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<DR_StPoint>& pStPoint);
	virtual ~GR_DLNodeWorkpoint(void);

	// Get point
	const SL_Ptr<DR_StPoint>& GetStPoint() const;

private:
	SL_Ptr<DR_StPoint>	m_pStPoint;
};

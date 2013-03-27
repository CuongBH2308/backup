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

// The node of coordinate system

class GR_RR;
class GR_DLNodeWorkaxis;
class GR_DLNodeWorkpoint;
class GR_DLNodeWorkplane;
class GR_DLNodeCrdSys :	public GR_DLNode
{
public:
	GR_DLNodeCrdSys(const SL_Ptr<GR_DLNode>& pDLNode);
	virtual ~GR_DLNodeCrdSys(void);

private:
	SL_Ptr<GR_DLNodeWorkaxis>	m_pXAxis;
	SL_Ptr<GR_DLNodeWorkaxis>	m_pYAxis;
	SL_Ptr<GR_DLNodeWorkaxis>	m_pZAxis;
	SL_Ptr<GR_DLNodeWorkpoint>	m_pOrigin;
	SL_Ptr<GR_DLNodeWorkplane>	m_pXYPlane;
	SL_Ptr<GR_DLNodeWorkplane>	m_pYZPlane;
	SL_Ptr<GR_DLNodeWorkplane>	m_pXZPlane;
};

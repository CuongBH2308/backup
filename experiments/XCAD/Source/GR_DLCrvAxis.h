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
#include "gr_dlcrv.h"


class MH_CrvLineSeg;

// This class is for the x, y , z axis
class GR_DLCrvAxis : public GR_DLCrv
{
public:
	GR_DLCrvAxis(GR_DLNode* pParentNode, MH_CrvLineSeg* pLineSeg);
	virtual ~GR_DLCrvAxis(void);
};

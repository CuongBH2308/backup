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

class GR_RR;
class GR_DLCrv;
class UC_RotateDLNode :	public GR_DLNode
{
public:
	UC_RotateDLNode(GR_RR* pRR, GR_DLNode* pDLNode);
	virtual ~UC_RotateDLNode(void);

	// Render the child nodes and display list
	virtual bool Render() const;
	
	// Get m_pDLCrv;
	GR_DLCrv* GetDL() const;

private:
	GR_DLCrv* m_pDLCrv;
};

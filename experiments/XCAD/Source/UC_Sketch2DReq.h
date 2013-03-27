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
#include "fw_requesttxn.h"

class UC_Sketch2DReq : public FW_RequestTxn
{
public:
	// Create a sketch 2d based on a plane (pPlane)
	// plane can be 
	// 1. planar face
	// 2. work plane
//	UC_Sketch2DReq(FW_Document* pDoc, MH_Plane* pPlane);
	virtual ~UC_Sketch2DReq(void);

protected:
	virtual HRESULT OnExecute();
};

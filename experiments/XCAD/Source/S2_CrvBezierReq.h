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
#include "mh_crvbezier.h"

class FW_Document;
class GR_DLCrv;
class GR_DLNodeSketch2D;
class S2_CrvBezierReq : public FW_RequestTxn
{
public:
	// Used to created a line segment
	S2_CrvBezierReq(FW_Document* pDoc, GR_DLNodeSketch2D* pDLNodeSketch2D, const MH_CrvBezier& crvBezier);
	
	// De-constructor
	virtual ~S2_CrvBezierReq(void);

	// Record
	virtual HRESULT Script();

	// Prepare the data for Replay
	virtual HRESULT InitFromScript();

protected:
	virtual HRESULT OnExecute();

private:
	GR_DLNodeSketch2D*		m_DLNodeSketch2D;
	MH_CrvBezier			m_CrvBezier;
};

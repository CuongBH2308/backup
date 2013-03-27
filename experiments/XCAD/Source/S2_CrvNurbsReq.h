#pragma once
#include "fw_requesttxn.h"
#include "mh_crvnurbs.h"

class FW_Document;
class GR_DLCrv;
class GR_DLNodeSketch2D;
class S2_CrvNurbsReq : public FW_RequestTxn
{
public:
	// Used to created a line segment
	S2_CrvNurbsReq(FW_Document* pDoc, GR_DLNodeSketch2D* pDLNodeSketch2D, const MH_CrvNurbs& crvNurbs);
	
	// De-constructor
	virtual ~S2_CrvNurbsReq(void);

	// Record
	virtual HRESULT Script();

	// Prepare the data for Replay
	virtual HRESULT InitFromScript();

protected:
	virtual HRESULT OnExecute();

private:
	GR_DLNodeSketch2D*		m_DLNodeSketch2D;
	MH_CrvNurbs				m_CrvNurbs;
};

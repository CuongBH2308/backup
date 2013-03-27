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
#include "dr_collect.h"

class PT_FtrRevolveReq : public FW_RequestTxn
{
public:
	PT_FtrRevolveReq(FW_Document* pDoc, 
		const DR_StCrvPtrVect&	vStCrvProfile,
		const SL_Ptr<DR_StCrv>& pStCrvAxis);
	virtual ~PT_FtrRevolveReq(void);

	// Record
	virtual HRESULT Script();

	// Prepare the data for Replay
	virtual HRESULT InitFromScript();

protected:
	virtual HRESULT OnExecute();

private:
	DR_StCrvPtrVect		m_vStCrvProfile;
	SL_Ptr<DR_StCrv>	m_pStCrvAxis;
};

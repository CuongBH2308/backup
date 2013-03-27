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
#include "dr_dct.h"
#include "dr_collect.h"

class DR_StWire;
class DR_DCtWire : public DR_DCt
{
public:
	DR_DCtWire(const SL_Ptr<DR_Fragment>& pFragment,
		const DR_StCrvPtrVect& vCrv,
		const DR_StPointPtrVect& vPt,
		const SL_Ptr<DR_StWire>& pStWire);
	virtual ~DR_DCtWire(void);

	// Compute the output in new condition
	virtual HRESULT Compute();

private:
	//////////////////////////////////////////////////////////////////////////
	// m_vCrv and m_vPt are used to construct the wire
	// If m_vCrv.size() == m_vPt.size(), then it is a closed wire
	// If m_vCrv.size() == m_vPt.size()-1, then it is a open wire
	//////////////////////////////////////////////////////////////////////////
	DR_StCrvPtrVect		m_vCrv;
	DR_StPointPtrVect	m_vPt;

	// Output of this constraint
	SL_Ptr<DR_StWire>	m_pStWire;
};

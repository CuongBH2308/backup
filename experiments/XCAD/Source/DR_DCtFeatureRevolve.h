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
#include "dr_dctfeature.h"

class DR_StWire;
class DR_StCrv;
class DR_StBool;
class DR_StBody;
class DR_StReal;
class DR_DCtFeatureRevolve : public DR_DCtFeature
{
public:
	DR_DCtFeatureRevolve(const SL_Ptr<DR_Fragment>& pFragment,
		const SL_Ptr<DR_StWire>& pStWire,
		const SL_Ptr<DR_StCrv>& pStCrvAxis,
		const SL_Ptr<DR_StBody>& pStBodyResult);
	virtual ~DR_DCtFeatureRevolve(void);

	// Compute the output in new condition
	virtual HRESULT Compute();

private:
	SL_Ptr<DR_StWire>		m_pStWire;			// profile
	SL_Ptr<DR_StCrv>		m_pStCrvAxis;		// axis. Should be line or line segment
	SL_Ptr<DR_StReal>		m_pStRealUFrom;		// angle from
	SL_Ptr<DR_StReal>		m_pStRealUTo;		// angle to
	SL_Ptr<DR_StBool>		m_pStBoolSolid;		// wants solid if true
	SL_Ptr<DR_StBody>		m_pStBodyResult;	// result body
};

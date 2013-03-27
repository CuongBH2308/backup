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
#include "dr_stcrv.h"
#include "mh_crvlineseg.h"

class DR_StCrvLineSeg :	public DR_StCrv
{
public:
	DR_StCrvLineSeg(const SL_Ptr<DR_Fragment>& pFragment, const MH_CrvLineSeg& lineSeg);
	virtual ~DR_StCrvLineSeg(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Get curve
	virtual MH_Crv* GetCrv();

	// Get start DR_StPoint
	virtual SL_Ptr<DR_StPoint> GetStartPt() const;

	// Get end DR_StPoint
	virtual SL_Ptr<DR_StPoint> GetEndPt() const;

	// Set lineSeg
	void SetLineSeg(const MH_CrvLineSeg& lineSeg);

	// Get lineSeg
	const MH_CrvLineSeg& GetLineSeg() const;

private:
	MH_CrvLineSeg m_lineSeg;
};

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


#include "stdafx.h"
#include "dr_stcrvlineseg.h"
#include "dr_stpoint.h"
#include "dr_uctpointlineseg.h"

DR_StCrvLineSeg::DR_StCrvLineSeg(const SL_Ptr<DR_Fragment>& pFragment, const MH_CrvLineSeg& lineSeg)
:DR_StCrv(pFragment),
m_lineSeg(lineSeg)
{
}

DR_StCrvLineSeg::~DR_StCrvLineSeg(void)
{
}

// Transform this object
// virtual 
void DR_StCrvLineSeg::Transform(const MH_Matrix44& mtx)
{
	m_lineSeg.Transform(mtx);
}

// Get curve
// virtual 
MH_Crv* DR_StCrvLineSeg::GetCrv()
{
	return &m_lineSeg;
}

// Set lineSeg
void DR_StCrvLineSeg::SetLineSeg(const MH_CrvLineSeg& lineSeg)
{
	m_lineSeg = lineSeg;
}

// Get lineSeg
const MH_CrvLineSeg& DR_StCrvLineSeg::GetLineSeg() const
{
	return m_lineSeg;
}

// Get start DR_StPoint
// virtual 
SL_Ptr<DR_StPoint> DR_StCrvLineSeg::GetStartPt() const
{
	const DR_CtPtrVect& vInput = GetInputs();
	DR_CtPtrVect::const_iterator it = vInput.begin();
	DR_CtPtrVect::const_iterator itEnd = vInput.end();
	for(; it!= itEnd; ++it)
	{
		DR_UCtPointLineSeg* pUCtPointLineSeg = dynamic_cast<DR_UCtPointLineSeg*>((*it).GetTarget());
		if(pUCtPointLineSeg && pUCtPointLineSeg->GetStPoint().GetTarget() && pUCtPointLineSeg->GetType() == DR_UCtPointLineSeg::eStart)
			return pUCtPointLineSeg->GetStPoint();
	}
	return reinterpret_cast<DR_StPoint*>(NULL);
}

// Get end DR_StPoint
// virtual
SL_Ptr<DR_StPoint> DR_StCrvLineSeg::GetEndPt() const
{
	const DR_CtPtrVect& vInput = GetInputs();
	DR_CtPtrVect::const_iterator it = vInput.begin();
	DR_CtPtrVect::const_iterator itEnd = vInput.end();
	for(; it!= itEnd; ++it)
	{
		DR_UCtPointLineSeg* pUCtPointLineSeg = dynamic_cast<DR_UCtPointLineSeg*>((*it).GetTarget());
		if(pUCtPointLineSeg && pUCtPointLineSeg->GetStPoint().GetTarget() && pUCtPointLineSeg->GetType() == DR_UCtPointLineSeg::eEnd)
			return pUCtPointLineSeg->GetStPoint();
	}
	return reinterpret_cast<DR_StPoint*>(NULL);
}
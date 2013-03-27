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
#include "dr_stcrvnurbs.h"
#include "dr_stpoint.h"
#include "dr_uctcvcrvnurbs.h"

DR_StCrvNurbs::DR_StCrvNurbs(const SL_Ptr<DR_Fragment>& pFragment, const MH_CrvNurbs& nurbs)
:DR_StCrv(pFragment),
m_nurbs(nurbs)
{
}

DR_StCrvNurbs::~DR_StCrvNurbs(void)
{
}

// Transform this object
// virtual
void DR_StCrvNurbs::Transform(const MH_Matrix44& mtx)
{
	m_nurbs.Transform(mtx);
}

// Get curve
// virtual 
MH_Crv* DR_StCrvNurbs::GetCrv()
{
	return &m_nurbs;
}

// Get start DR_StPoint
// virtual 
SL_Ptr<DR_StPoint> DR_StCrvNurbs::GetStartPt() const
{
	const DR_CtPtrVect& vCt = GetInputs();
	DR_CtPtrVect::const_iterator it = vCt.begin();
	DR_CtPtrVect::const_iterator itEnd = vCt.end();
	for(; it!=itEnd; ++it)
	{
		DR_UCtCVCrvNurbs* pUCtCVCrvNurbs = dynamic_cast<DR_UCtCVCrvNurbs*>((*it).GetTarget());
		if(!pUCtCVCrvNurbs)
			continue;

		if(pUCtCVCrvNurbs->GetIndex() == 0)
			return pUCtCVCrvNurbs->GetStPoint();
	}
	return reinterpret_cast<DR_StPoint*>(NULL);
}

// Get end DR_StPoint
// virtual 
SL_Ptr<DR_StPoint> DR_StCrvNurbs::GetEndPt() const
{
	const DR_CtPtrVect& vCt = GetInputs();
	DR_CtPtrVect::const_iterator it = vCt.begin();
	DR_CtPtrVect::const_iterator itEnd = vCt.end();
	for(; it!=itEnd; ++it)
	{
		DR_UCtCVCrvNurbs* pUCtCVCrvNurbs = dynamic_cast<DR_UCtCVCrvNurbs*>((*it).GetTarget());
		if(!pUCtCVCrvNurbs)
			continue;

		if(pUCtCVCrvNurbs->GetIndex() == m_nurbs.GetCVs().size()-1)
			return pUCtCVCrvNurbs->GetStPoint();
	}
	return reinterpret_cast<DR_StPoint*>(NULL);
}

// Set Nurbs
void DR_StCrvNurbs::SetNurbs(const MH_CrvNurbs& nurbs)
{
	m_nurbs = nurbs;
}

// Get Nurbs
const MH_CrvNurbs& DR_StCrvNurbs::GetNurbs() const
{
	return m_nurbs;
}

// Set the nIndex-th CV
bool DR_StCrvNurbs::SetCV(size_t nIndex, const MH_CV& cv)
{
	return m_nurbs.SetCV(nIndex, cv);
}

// Set the nIndex-th CV
bool DR_StCrvNurbs::SetCV(size_t nIndex, const MH_Point3& pt)
{
	MH_CV cv;
	m_nurbs.GetCV(nIndex, cv);
	cv.SetPoint3(pt);
	return m_nurbs.SetCV(nIndex, cv);
}
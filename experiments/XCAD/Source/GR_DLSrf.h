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
#include "gr_dl.h"

class MH_Srf;
class MH_CrvRay;
class GR_DLSrf : public GR_DL
{
public:
	GR_DLSrf(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<MH_Srf>& pSrf);
	virtual ~GR_DLSrf(void);

	// Get the type of the DL
	virtual GR_DL::EType GetType();

	// Get math expression
	const SL_Ptr<MH_Srf>& GetSrf() const;

	// Is the DL selected
	virtual bool HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const;

private:
	SL_Ptr<MH_Srf> m_pSrf;
};

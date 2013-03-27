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
#include "gr_rrdlcrvopengl.h"
#include "gr_dlcrv.h"
#include "mh_crv.h"
#include "mh_util.h"

GR_RRDLCrvOpenGL::GR_RRDLCrvOpenGL(GR_DLCrv* pDLCrv)
:GR_RRDLOpenGL(pDLCrv),
m_pDLCrv(pDLCrv)
{
}

GR_RRDLCrvOpenGL::~GR_RRDLCrvOpenGL(void)
{
}

// Build this display list
// virtual 
bool GR_RRDLCrvOpenGL::OnBuild()
{
	if(!m_pDLCrv)
		return false;

	SL_Ptr<MH_Crv> pCrv = m_pDLCrv->GetCrv();
	if(!pCrv.GetTarget())
		return false;

	if(pCrv->GetPts().size()==0 || pCrv->IsInvalid())
	{
		pCrv->Tessellate(MH_Util::GetTessellateTolerance());
		pCrv->Invalidate(false);
	}

	const MH_CrvPtVect& vCrvPt = pCrv->GetPts();
	if(vCrvPt.size()>1)
	{
		MH_CrvPtVect::const_iterator it = vCrvPt.begin();
		MH_CrvPtVect::const_iterator itEnd = vCrvPt.end();

		::glBegin(GL_LINE_STRIP);
		for(; it != itEnd; ++it)
			::glVertex3f((*it).GetPoint3().m_f[0], (*it).GetPoint3().m_f[1], (*it).GetPoint3().m_f[2]);
		::glEnd();
		return true;
	}

	return false;
}
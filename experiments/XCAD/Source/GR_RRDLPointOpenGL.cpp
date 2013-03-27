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
#include "gr_rrdlpointopengl.h"
#include "gr_dlpoint.h"
#include "mh_point3.h"

GR_RRDLPointOpenGL::GR_RRDLPointOpenGL(GR_DLPoint* pDLPoint)
:GR_RRDLOpenGL(pDLPoint),
m_pDLPoint(pDLPoint)
{
}

GR_RRDLPointOpenGL::~GR_RRDLPointOpenGL(void)
{
}

// Build this display list
// virtual 
bool GR_RRDLPointOpenGL::OnBuild()
{
	if(!m_pDLPoint)
		return false;

	SL_Ptr<MH_Point3> pPt = m_pDLPoint->GetPoint();
	if(!pPt.GetTarget())
		return false;

	::glBegin(GL_POINTS);
	::glVertex3f(pPt->m_f[0], pPt->m_f[1], pPt->m_f[2]);
	::glEnd();

	return true;
}
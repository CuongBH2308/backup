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
#include "gr_rrdlopengl.h"
#include "gr_dl.h"

GR_RRDLOpenGL::GR_RRDLOpenGL(GR_DL* pDL)
:GR_RRDL(pDL),
m_nList(0)
{
}

GR_RRDLOpenGL::~GR_RRDLOpenGL(void)
{
	if(m_nList > 0)
		::glDeleteLists(m_nList,1);
}

// Build this display list
// virtual 
bool GR_RRDLOpenGL::Build()
{
	SL_Ptr<GR_DL> pDL = GetDL();
	ASSERT(pDL.GetTarget());

	// Generate 1 Display List
	if(m_nList == 0)
		m_nList	= ::glGenLists(1);

	// Create or replace a display list
	::glNewList(m_nList,GL_COMPILE);

	// Apply the attribute
	bool bOK = pDL->ApplyAttrib();
	ASSERT(bOK);

	// Build the display list
	bOK = OnBuild();
	//ASSERT(bOK);

	// Un-Apply the attribute
	bOK = pDL->ApplyAttrib(false);
	ASSERT(bOK);

	// End create / replace the display list
	::glEndList();

	return bOK;
}

// Render the display list
// virtual 
bool GR_RRDLOpenGL::OnRender() const
{
	SL_Ptr<GR_DL> pDL = GetDL();
	if(m_nList == 0 || !pDL.GetTarget())
		return false;

	::glPushAttrib(GL_TRANSFORM_BIT);
	::glMatrixMode(GL_MODELVIEW);
	::glMultMatrixf(&pDL->GetTransform().Transpose()[0]);
	::glCallList(m_nList);
	::glPopAttrib();
	return true;
}
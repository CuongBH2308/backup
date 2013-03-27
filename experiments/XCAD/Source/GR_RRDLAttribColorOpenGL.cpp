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
#include "gr_rrdlattribcoloropengl.h"
#include <gl\gl.h>
#include "gr_dlattribcolor.h"

GR_RRDLAttribColorOpenGL::GR_RRDLAttribColorOpenGL(GR_DLAttribColor* pDLAttribColor)
:m_pDLAttribColor(pDLAttribColor)
{
}

GR_RRDLAttribColorOpenGL::~GR_RRDLAttribColorOpenGL(void)
{
}

// Apply this attribute
// virtual
bool GR_RRDLAttribColorOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		GR_Color clr = m_pDLAttribColor->GetColor();
		::glPushAttrib(GL_CURRENT_BIT);
		::glColor4f(clr.GetRed(), clr.GetGreen(), clr.GetBlue(), clr.GetAlpha());
	}
	else
		::glPopAttrib();
	return true;
}
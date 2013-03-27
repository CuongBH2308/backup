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
#include "gr_rrdlattribcurvewidthopengl.h"
#include <gl\gl.h>
#include "gr_dlattribcurvewidth.h"

GR_RRDLAttribCurveWidthOpenGL::GR_RRDLAttribCurveWidthOpenGL(GR_DLAttribCurveWidth* pDLAttribCurveWidth)
:m_pDLAttribCurveWidth(pDLAttribCurveWidth)
{
}

GR_RRDLAttribCurveWidthOpenGL::~GR_RRDLAttribCurveWidthOpenGL(void)
{
}

// Apply this attribute
// virtual
bool GR_RRDLAttribCurveWidthOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		::glPushAttrib(GL_LINE_BIT);
		::glLineWidth(m_pDLAttribCurveWidth->GetWidth());
	}
	else
		::glPopAttrib();
	return true;
}
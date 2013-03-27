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
#include "gr_rrdlattribpointsizeopengl.h"
#include <gl\gl.h>
#include "gr_dlattribpointsize.h"

GR_RRDLAttribPointSizeOpenGL::GR_RRDLAttribPointSizeOpenGL(GR_DLAttribPointSize* pDLAttribPointSize)
:m_pDLAttribPointSize(pDLAttribPointSize)
{
}

GR_RRDLAttribPointSizeOpenGL::~GR_RRDLAttribPointSizeOpenGL(void)
{
}

// Apply this attribute
// virtual
bool GR_RRDLAttribPointSizeOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		::glPushAttrib(GL_POINT_BIT);
		::glPointSize(m_pDLAttribPointSize->GetSize());
	}
	else
		::glPopAttrib();
	return true;
}
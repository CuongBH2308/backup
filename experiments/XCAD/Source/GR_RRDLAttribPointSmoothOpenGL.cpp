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
#include "gr_rrdlattribpointsmoothopengl.h"
#include <gl\gl.h>
#include "gr_dlattribpointsmooth.h"

GR_RRDLAttribPointSmoothOpenGL::GR_RRDLAttribPointSmoothOpenGL(GR_DLAttribPointSmooth* pDLAttribPointSmooth)
:m_pDLAttribPointSmooth(pDLAttribPointSmooth)
{
}

GR_RRDLAttribPointSmoothOpenGL::~GR_RRDLAttribPointSmoothOpenGL(void)
{
}

// Apply this attribute
// virtual
bool GR_RRDLAttribPointSmoothOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		::glPushAttrib(GL_POINT_BIT);
		m_pDLAttribPointSmooth->GetSmooth() ?  
			::glEnable(GL_POINT_SMOOTH) : ::glDisable(GL_POINT_SMOOTH);
	}
	else
		::glPopAttrib();
	return true;
}
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
#include "gr_rrdlattribblendopengl.h"
#include <gl\gl.h>
#include "gr_dlattribblend.h"

GR_RRDLAttribBlendOpenGL::GR_RRDLAttribBlendOpenGL(GR_DLAttribBlend* pDLAttribBlend)
:m_pDLAttribBlend(pDLAttribBlend)
{
}

GR_RRDLAttribBlendOpenGL::~GR_RRDLAttribBlendOpenGL(void)
{
}

// Apply this attribute
// virtual 
bool GR_RRDLAttribBlendOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		// GL_BLEND,GL_DEPTH_TEST | Blending source and destination functions 
		::glPushAttrib(GL_ENABLE_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		if(m_pDLAttribBlend->GetBlend())
		{
			::glEnable(GL_BLEND);
			::glDisable(GL_DEPTH_TEST);
			::glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}
		else
		{
			::glDisable(GL_BLEND);
			::glEnable(GL_DEPTH_TEST);
		}
	}
	else
		::glPopAttrib();

	return true;
}
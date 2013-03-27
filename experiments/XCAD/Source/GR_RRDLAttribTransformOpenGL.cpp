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
#include "gr_rrdlattribtransformopengl.h"
#include <gl\gl.h>
#include "gr_dlattribtransform.h"

GR_RRDLAttribTransformOpenGL::GR_RRDLAttribTransformOpenGL(GR_DLAttribTransform* pDLAttribTransform)
:m_pDLAttribTransform(pDLAttribTransform)
{
}

GR_RRDLAttribTransformOpenGL::~GR_RRDLAttribTransformOpenGL(void)
{
}

// Apply this attribute
// virtual 
bool GR_RRDLAttribTransformOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		::glPushAttrib(GL_TRANSFORM_BIT);
		::glMatrixMode(GL_MODELVIEW);
		::glPushMatrix();
		::glMultMatrixf(&m_pDLAttribTransform->GetTransform().Transpose()[0]);
	}
	else
	{
		::glPopMatrix();
		::glPopAttrib();
	}

	return true;
}
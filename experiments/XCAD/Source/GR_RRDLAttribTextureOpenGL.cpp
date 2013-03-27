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
#include "gr_rrdlattribtextureopengl.h"
#include <gl\gl.h>
#include "gr_dlattribtexture.h"

GR_RRDLAttribTextureOpenGL::GR_RRDLAttribTextureOpenGL(GR_DLAttribTexture* pDLAttribTexture)
:m_pDLAttribTexture(pDLAttribTexture)
{
}

GR_RRDLAttribTextureOpenGL::~GR_RRDLAttribTextureOpenGL(void)
{
}


// Apply this attribute
// virtual 
bool GR_RRDLAttribTextureOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		::glGenTextures(1, &m_nName);
		::glBindTexture(GL_TEXTURE_2D, m_nName);
		::glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		::glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		::glTexImage2D(GL_TEXTURE_2D, 0, 3, m_pDLAttribTexture->GetWidth(), m_pDLAttribTexture->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_pDLAttribTexture->GetBytes());

		::glPushAttrib(GL_ENABLE_BIT);
		::glDisable(GL_BLEND);
		::glEnable(GL_TEXTURE_2D);
		::glBindTexture(GL_TEXTURE_2D, m_nName);
	}
	else
	{
		::glPopAttrib();
		::glDeleteTextures(1, &m_nName);
	}

	return true;
}
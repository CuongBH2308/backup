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
#include "gr_rrdlattriblightopengl.h"
#include <gl\gl.h>
#include "gr_dlattriblight.h"

GR_RRDLAttribLightOpenGL::GR_RRDLAttribLightOpenGL(GR_DLAttribLight* pDLAttribLight)
:m_pDLAttribLight(pDLAttribLight)
{
}

GR_RRDLAttribLightOpenGL::~GR_RRDLAttribLightOpenGL(void)
{
}

// Apply this attribute
// virtual
bool GR_RRDLAttribLightOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		// The light we will use
		GLenum nLight;

		// Look for an unused light
		for(nLight = GL_LIGHT0; nLight < (GL_LIGHT0+GL_MAX_LIGHTS); nLight++)
		{
			if( ::glIsEnabled(nLight) != GL_TRUE )
				break;
		}
		if( nLight == (GL_LIGHT0+GL_MAX_LIGHTS) )
			return false;

		// Check error
		GLenum err = ::glGetError();
		if(  err == GL_INVALID_ENUM || err == GL_INVALID_OPERATION )
			return false;

		::glPushAttrib(GL_ENABLE_BIT);

		// Hidden surface removal
		::glEnable(GL_DEPTH_TEST); 
		
		//// Counter clock-wise polygons face out
		//::glFrontFace(GL_CCW);

		//// Do not calculate inside of jet
		//::glEnable(GL_CULL_FACE);

		// Setup and enable light 0
		if(m_pDLAttribLight->GetAmbient().m_bValid)
			::glLightfv(nLight,GL_AMBIENT,m_pDLAttribLight->GetAmbient().m_fRGBA);

		if(m_pDLAttribLight->GetDiffuse().m_bValid)
			::glLightfv(nLight,GL_DIFFUSE,m_pDLAttribLight->GetDiffuse().m_fRGBA);

		if(m_pDLAttribLight->GetSpecular().m_bValid)
			::glLightfv(nLight,GL_SPECULAR,m_pDLAttribLight->GetSpecular().m_fRGBA);

		// Set light's position
		::glLightfv(nLight,GL_POSITION, m_pDLAttribLight->GetPosition().m_fPos);

		// Enable light-i
		::glEnable(nLight);

		// Enable lighting
		::glEnable(GL_LIGHTING);

		//// Enable color tracking
		//::glEnable(GL_COLOR_MATERIAL);

		//// Set Material properties to follow glColor values
		//::glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
	else
		::glPopAttrib();

	return true;
}
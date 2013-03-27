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
#include "gr_rrdlattribselectopengl.h"
#include <gl\gl.h>
#include "gr_dlattribselect.h"

GR_RRDLAttribSelectOpenGL::GR_RRDLAttribSelectOpenGL(GR_DLAttribSelect* pDLAttribSelect)
:m_pDLAttribSelect(pDLAttribSelect)
{
}

GR_RRDLAttribSelectOpenGL::~GR_RRDLAttribSelectOpenGL(void)
{
}

// Apply this attribute
// virtual 
bool GR_RRDLAttribSelectOpenGL::Apply(bool bApply)
{
	if(bApply)
	{
		// Current RGBA color  
		::glPushAttrib(GL_CURRENT_BIT);
		switch(m_pDLAttribSelect->GetStatus())
		{
		case GR_SelectionSet::eUnSel:
			break;
		case GR_SelectionSet::ePreSel:
			{
				const GR_Color& clr = m_pDLAttribSelect->GetColor(GR_SelectionSet::ePreSel);
                ::glColor4f(clr.GetRed(), clr.GetGreen(), clr.GetBlue(), clr.GetAlpha());
			}
			break;
		case GR_SelectionSet::eSel:
			{
				const GR_Color& clr = m_pDLAttribSelect->GetColor(GR_SelectionSet::eSel);
				::glColor4f(clr.GetRed(), clr.GetGreen(), clr.GetBlue(), clr.GetAlpha());
			}
			break;
		default:
			break;
		}
	}
	else
		::glPopAttrib();

	return true;
}
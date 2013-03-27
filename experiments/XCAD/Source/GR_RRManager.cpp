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
#include "gr_rrmanager.h"
#include "gr_rr.h"
#include "gr_rropengl.h"
#include "gr_rrd3d.h"
#include "gr_rrdlnodeopengl.h"
#include "gr_rrdlpointopengl.h"
#include "gr_rrdlcrvopengl.h"
#include "gr_rrdlsrfopengl.h"
#include "gr_rrdlattribcoloropengl.h"
#include "gr_rrdlattribpointsizeopengl.h"
#include "gr_rrdlattribpointsmoothopengl.h"
#include "gr_rrdlattribcurvewidthopengl.h"
#include "gr_rrdlattribcurvestippleopengl.h"
#include "gr_rrdlattribblendopengl.h"
#include "gr_rrdlattribtransformopengl.h"
#include "gr_rrdlattribselectopengl.h"
#include "gr_rrdlattribtextureopengl.h"
#include "gr_rrdlattriblightopengl.h"
#include "gr_dlnode.h"
#include "gr_dlpoint.h"
#include "gr_dlcrv.h"
#include "gr_dlsrf.h"
#include "gr_dlattrib.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribpointsize.h"
#include "gr_dlattribpointsmooth.h"
#include "gr_dlattribcurvewidth.h"
#include "gr_dlattribcurvestipple.h"
#include "gr_dlattribblend.h"
#include "gr_dlattribtransform.h"
#include "gr_dlattribselect.h"
#include "gr_dlattribtexture.h"
#include "gr_dlattriblight.h"
#include "sl_mm.h"

GR_RRManager::GR_RRManager(void)
:m_eRender(eOpenGL)
{
}

GR_RRManager::~GR_RRManager(void)
{
}

GR_RRManager* GR_RRManager::GetRRManager()
{
	static GR_RRManager rrManager;
	return &rrManager;
}

// Delete RR
void GR_RRManager::DeleteRR(GR_RR* pRR) const
{
	ASSERT(pRR);
	DEL_OBJ(pRR);
}

// Get render
GR_RR* GR_RRManager::GetRR() const
{
	GR_RR*	pRR = NULL;

	switch(m_eRender)
	{
	case eOpenGL:
		pRR = NEW_OBJ2(GR_RROpenGL)();
		break;
	case eD3D:
		//pRR = new GR_RRD3D();
		break;
	default:
		break;
	}

	return pRR;
}

// Get the renderer of the DL
GR_RRDL* GR_RRManager::GetRRDL(GR_DL* pDL) const
{
	GR_RRDL*	pRRDL = NULL;

	switch(m_eRender)
	{
	case eOpenGL:
		{
			if( GR_DLNode* pDLNode = dynamic_cast<GR_DLNode*>(pDL) )
				pRRDL = NEW_OBJ2(GR_RRDLNodeOpenGL)(pDLNode);

			else if( GR_DLPoint* pDLPoint = dynamic_cast<GR_DLPoint*>(pDL) )
				pRRDL = NEW_OBJ2(GR_RRDLPointOpenGL)(pDLPoint);

			else if( GR_DLCrv* pDLCrv = dynamic_cast<GR_DLCrv*>(pDL) )
				pRRDL = NEW_OBJ2(GR_RRDLCrvOpenGL)(pDLCrv);

			else if( GR_DLSrf* pDLSrf = dynamic_cast<GR_DLSrf*>(pDL) )
				pRRDL = NEW_OBJ2(GR_RRDLSrfOpenGL)(pDLSrf);
		}
		break;
	case eD3D:
		break;
	default:
		break;
	}

	return pRRDL;
}

// Get the renderer of the attribute
GR_RRDLAttrib* GR_RRManager::GetRRDLAttrib(GR_DLAttrib* pDLAttrib) const
{
	GR_RRDLAttrib*	pRRDLAttrib = NULL;

	switch(m_eRender)
	{
	case eOpenGL:
		{
			if( GR_DLAttribColor* pDLAttribColor = dynamic_cast<GR_DLAttribColor*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribColorOpenGL)(pDLAttribColor);
			
			else if( GR_DLAttribPointSize* pDLAttribPointSize = dynamic_cast<GR_DLAttribPointSize*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribPointSizeOpenGL)(pDLAttribPointSize);

			else if ( GR_DLAttribPointSmooth* pDLAttribPointSmooth = dynamic_cast<GR_DLAttribPointSmooth*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribPointSmoothOpenGL)(pDLAttribPointSmooth);

			else if ( GR_DLAttribCurveWidth* pDLAttribCurveWidth = dynamic_cast<GR_DLAttribCurveWidth*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribCurveWidthOpenGL)(pDLAttribCurveWidth);

			else if ( GR_DLAttribCurveStipple* pDLAttribCurveStipple = dynamic_cast<GR_DLAttribCurveStipple*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribCurveStippleOpenGL)(pDLAttribCurveStipple);

			else if ( GR_DLAttribBlend* pDLAttribBlend = dynamic_cast<GR_DLAttribBlend*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribBlendOpenGL)(pDLAttribBlend);

			else if ( GR_DLAttribTransform* pDLAttribTransform = dynamic_cast<GR_DLAttribTransform*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribTransformOpenGL)(pDLAttribTransform);

			else if ( GR_DLAttribSelect* pDLAttribSelect = dynamic_cast<GR_DLAttribSelect*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribSelectOpenGL)(pDLAttribSelect);

			else if ( GR_DLAttribTexture* pDLAttribTexture = dynamic_cast<GR_DLAttribTexture*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribTextureOpenGL)(pDLAttribTexture);

			else if ( GR_DLAttribLight* pDLAttribLight = dynamic_cast<GR_DLAttribLight*>(pDLAttrib) )
				pRRDLAttrib = NEW_OBJ2(GR_RRDLAttribLightOpenGL)(pDLAttribLight);
		}
		break;
	case eD3D:
		break;
	default:
		break;
	}

	return pRRDLAttrib;
}

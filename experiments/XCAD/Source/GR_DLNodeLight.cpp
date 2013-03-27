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
#include "gr_dlnodelight.h"
#include <math.h>
#include "gr_dlattribblend.h"
#include "gr_dlsrf.h"
#include "mh_srfsphere.h"
#include "mh_srfcylinder.h"
#include "sl_mm.h"

#define LIGHT_BULB_RADIUS 0.2f
#define LIGHT_DIR_LEN 2.0f

GR_DLNodeLight::GR_DLNodeLight(const SL_Ptr<GR_DLNode>& pParentNode,
							   const MH_Point3& pt,
							   GR_Selector* pSelector)
:GR_DLNode(pParentNode, pSelector),
m_pt(pt)
{
	MH_SrfSphere* pSrfSphere = NEW_OBJ(MH_SrfSphere, this)(m_pt, LIGHT_BULB_RADIUS);
	NEW_OBJ(GR_DLSrf, this)(this, pSrfSphere);

	GR_DLAttribBlend* pDLAttribBlend = NEW_OBJ(GR_DLAttribBlend, this)(true);
	AddAttrib(pDLAttribBlend);
}

GR_DLNodeLight::GR_DLNodeLight(const SL_Ptr<GR_DLNode>& pParentNode,
							   const MH_Point3& pt,
							   const MH_Vector3& vDir,
							   GR_Selector* pSelector)
:GR_DLNode(pParentNode, pSelector),
m_pt(pt),
m_vDir(vDir)
{
	m_vDir.Normalize();

	MH_SrfSphere* pSrfSphere = NEW_OBJ(MH_SrfSphere, this)(m_pt, LIGHT_BULB_RADIUS);
	NEW_OBJ(GR_DLSrf, this)(this, pSrfSphere);

	MH_SrfCylinder* pSrfCylinder = NEW_OBJ(MH_SrfCylinder, this)(m_pt+m_vDir*LIGHT_BULB_RADIUS/2.0f, m_vDir*LIGHT_BULB_RADIUS*2, LIGHT_BULB_RADIUS*sqrt(3.0f)/2.0f, 0);
	NEW_OBJ(GR_DLSrf, this)(this, pSrfCylinder);

	GR_DLAttribBlend* pDLAttribBlend = NEW_OBJ(GR_DLAttribBlend, this)(true);
	AddAttrib(pDLAttribBlend);
}

GR_DLNodeLight::~GR_DLNodeLight(void)
{
}

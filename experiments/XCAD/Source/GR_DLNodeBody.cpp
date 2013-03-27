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
#include "gr_dlnodebody.h"
#include "gr_dlsrf.h"
#include "gr_dlattribblend.h"
#include "gr_dlattribcolor.h"
#include "gr_selectorbody.h"
#include "brep_body.h"
#include "brep_face.h"
#include "brep_util.h"
#include "dr_stbody.h"
#include "mh_srfpolygon.h"
#include "mh_util.h"
#include "sl_mm.h"

GR_DLNodeBody::GR_DLNodeBody(const SL_Ptr<DR_StBody>& pStBody, const SL_Ptr<GR_DLNode>& pParentNode)
:GR_DLNode(pParentNode, new GR_SelectorBody()),
m_pStBody(pStBody)
{
	Update();
}

GR_DLNodeBody::~GR_DLNodeBody(void)
{
}

bool GR_DLNodeBody::Update()
{
	GR_DLNodePtrVect* pvDLNode = NULL;
	GR_DLPtrVect* pvDL = NULL;
	this->GetChildren(pvDLNode, pvDL);
	if(pvDL->size() > 0)
		RemoveDL(pvDL->front());

	ASSERT(m_pStBody.GetTarget());
	BREP_FacePtrVect vFace;
	BREP_Util::GetFaces(m_pStBody->GetBody().GetTarget(), vFace);
	BREP_FacePtrVect::const_iterator it = vFace.begin();
	BREP_FacePtrVect::const_iterator itEnd = vFace.end();
	for(; it!=itEnd; ++it)
	{
		GR_DLSrf* pDLSrf = NEW_OBJ(GR_DLSrf, this)(this, (*it)->GetSrf());

		// Add attribute - color
		pDLSrf->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 0.0f, 0.3f)));

		// Add attribute - blend
		//pDLSrf->AddAttrib(NEW_OBJ(GR_DLAttribBlend, this)(true));
	}

	return true;
}

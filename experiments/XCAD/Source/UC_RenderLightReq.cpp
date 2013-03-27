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
#include "uc_renderlightreq.h"
#include "fw_document.h"
#include "gr_dlnodelight.h"
#include "gr_dlattriblight.h"
#include "sl_mm.h"

UC_RenderLightReq::UC_RenderLightReq(FW_Document* pDoc, 
									 const GR_DLAttribLight::Ambient& ambient,
									 const GR_DLAttribLight::Diffuse& diffuse,
									 const GR_DLAttribLight::Specular& specular,
									 const GR_DLAttribLight::Position& position,
									 GR_DLAttribLight* pDLAttribLight)
:FW_RequestTxn(pDoc),
m_pDLAttribLight(pDLAttribLight),
m_ambient(ambient),
m_diffuse(diffuse),
m_specular(specular),
m_position(position)
{
}

UC_RenderLightReq::~UC_RenderLightReq(void)
{
}

// virtual
HRESULT UC_RenderLightReq::Script()
{
	return S_OK;
}

// virtual 
HRESULT UC_RenderLightReq::InitFromScript()
{
	return S_OK;
}

// virtual 
HRESULT UC_RenderLightReq::OnExecute()
{
	GR_DLNode* pDLNode = m_pDoc->GetDLNode();
	GR_DLNodeLight* pDLNodeLight = NULL;
	
	if(!m_pDLAttribLight)
	{
		if(m_position.m_fPos[3] == 0)
			pDLNodeLight = NEW_OBJ(GR_DLNodeLight, pDLNode)(pDLNode, MH_Point3(m_position.m_fPos[0], m_position.m_fPos[1], m_position.m_fPos[2]));
		else
			pDLNodeLight = NEW_OBJ(GR_DLNodeLight, pDLNode)(pDLNode, MH_Point3(m_position.m_fPos[0], m_position.m_fPos[1], m_position.m_fPos[2]), -MH_Vector3(m_position.m_fPos[0], m_position.m_fPos[1], m_position.m_fPos[2]));

		m_pDLAttribLight = NEW_OBJ(GR_DLAttribLight, pDLNode)();
		pDLNode->AddAttrib(m_pDLAttribLight);
	}

	m_pDLAttribLight->SetAmbient(m_ambient);
	m_pDLAttribLight->SetDiffuse(m_diffuse);
	m_pDLAttribLight->SetSpecular(m_specular);
	m_pDLAttribLight->SetPosition(m_position);
	return S_OK;
}

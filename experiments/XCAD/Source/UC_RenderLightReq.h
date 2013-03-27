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


#pragma once
#include "fw_requesttxn.h"
#include "gr_dlattriblight.h"

class GR_DLAttribLight;
class UC_RenderLightReq : public FW_RequestTxn
{
public:
	UC_RenderLightReq(FW_Document* pDoc, 
		const GR_DLAttribLight::Ambient& ambient,
		const GR_DLAttribLight::Diffuse& diffuse,
		const GR_DLAttribLight::Specular& specular,
		const GR_DLAttribLight::Position& position,
		GR_DLAttribLight* pDLAttribLight = NULL);


	virtual ~UC_RenderLightReq(void);

protected:
	virtual HRESULT Script();
	virtual HRESULT InitFromScript();
	virtual HRESULT OnExecute();

private:
	GR_DLAttribLight*			m_pDLAttribLight;
	GR_DLAttribLight::Ambient	m_ambient;
	GR_DLAttribLight::Diffuse	m_diffuse;
	GR_DLAttribLight::Specular	m_specular;
	GR_DLAttribLight::Position	m_position;
};

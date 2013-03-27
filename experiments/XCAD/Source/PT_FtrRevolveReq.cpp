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
#include "pt_ftrrevolvereq.h"
#include "dr_dctfeaturerevolve.h"
#include "dr_dctstop.h"
#include "dr_dctwire.h"
#include "dr_fragment.h"
#include "dr_stbody.h"
#include "dr_stcrv.h"
#include "dr_stwire.h"
#include "fw_document.h"
#include "gr_dlnodebody.h"
#include "sl_mm.h"
#include "GR_DLAttribTexture.h"
#include "GR_Color.h"

GR_DLNodeBody* gDLNodeBody = NULL;

PT_FtrRevolveReq::PT_FtrRevolveReq(FW_Document* pDoc, 
								   const DR_StCrvPtrVect&	vStCrvProfile,
								   const SL_Ptr<DR_StCrv>&	pStCrvAxis)
:FW_RequestTxn(pDoc),
m_vStCrvProfile(vStCrvProfile),
m_pStCrvAxis(pStCrvAxis)
{
}

PT_FtrRevolveReq::~PT_FtrRevolveReq(void)
{
}

// Record
// virtual 
HRESULT PT_FtrRevolveReq::Script()
{
	return S_OK;
}

// Prepare the data for Replay
// virtual 
HRESULT PT_FtrRevolveReq::InitFromScript()
{
	return S_OK;
}

// virtual 
HRESULT PT_FtrRevolveReq::OnExecute()
{
	HRESULT hr = S_OK;
	DR_Fragment* pFragment = m_pDoc->GetFragment();

	DR_StWire* pStWire = NEW_OBJ(DR_StWire, pFragment)(pFragment);
	ASSERT(pStWire);

	DR_StPointPtrVect vPt;
	DR_StCrvPtrVect::const_iterator it		= m_vStCrvProfile.begin();
	DR_StCrvPtrVect::const_iterator itEnd	= m_vStCrvProfile.end();
	for(; it!=itEnd; ++it)
	{
		vPt.push_back((*it)->GetStartPt());
		if(it == itEnd-1)
			vPt.push_back((*it)->GetEndPt());
	}

	DR_DCtWire* pDCtWire = NEW_OBJ(DR_DCtWire, pStWire)(pFragment, m_vStCrvProfile, vPt, pStWire);
	ASSERT(pDCtWire);

    DR_StBody* pStBody = NEW_OBJ(DR_StBody, pFragment)(pFragment);
	ASSERT(pStBody);

	DR_DCtFeatureRevolve* pFtr = NEW_OBJ(DR_DCtFeatureRevolve, pFragment)(pFragment, pStWire, m_pStCrvAxis, pStBody);
	ASSERT(pFtr);

	pFragment->GetDCtStop()->AddInput(pStBody);

	pFragment->Compute();

	gDLNodeBody = NEW_OBJ(GR_DLNodeBody, m_pDoc->GetDLNode())(pStBody, m_pDoc->GetDLNode());
	GR_DLNodePtrVect* pvDLNode=NULL;
	GR_DLPtrVect* pvDL = NULL;
	gDLNodeBody->GetChildren(pvDLNode, pvDL);
	//pvDL->at(0)->AddAttrib(NEW_OBJ(GR_DLAttribTexture, gDLNodeBody)("D:\\Work\\Graphics\\XCAD2\\res\\Crate.bmp"), true);
	gDLNodeBody->GetParent()->Invalidate();
	return hr;
}
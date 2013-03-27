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
#include "fw_documentdata.h"
#include "fw_document.h"
#include "dr_fragment.h"
#include "dr_dctstop.h"
#include "dr_stpoint.h"
#include "dr_stcrvline.h"
#include "dr_stplane.h"
#include "dr_stvector3.h"
#include "dr_stxform.h"
#include "dr_dctalignerplane.h"
#include "dr_dctsketch2d.h"
#include "gr_dlnode.h"
#include "gr_dlnodeworkaxis.h"
#include "gr_dlnodeworkplane.h"
#include "gr_dlnodeworkpoint.h"
#include "gr_dlnodesketch2d.h"
#include "sl_storage.h"
#include "sl_streamobj.h"
#include "sl_mm.h"
#include "mm_txnmanager.h"

FW_DocumentData::FW_DocumentData(FW_Document* pDoc)
:m_pDoc(pDoc),
m_pDLNode(NULL),
m_pFragment(NULL),
m_pStorage(NULL)
{
}

FW_DocumentData::~FW_DocumentData()
{
	if(m_pStorage)
		DEL_OBJ(m_pStorage);
	if(m_pFragment)
		DEL_OBJ(m_pFragment);
	if(m_pDLNode)
		DEL_OBJ(m_pDLNode);
}

// Initialize. Create:
// 1. Root DL Node
// 2. Fragment
void FW_DocumentData::Init()
{
	ASSERT(!m_pDLNode);
	ASSERT(!m_pFragment);

	// Create fragment
	m_pFragment = NEW_OBJ1(DR_Fragment, GetStream(FW_DocumentData::eDR))();

	// Get stop constraint
	SL_Ptr<DR_DCtStop> pDCtStop = m_pFragment->GetDCtStop();
	ASSERT(pDCtStop.GetTarget());

	// Origin
	SL_Ptr<DR_StPoint> pStPointOrigin = NEW_OBJ(DR_StPoint, m_pFragment)(m_pFragment, MH_Point3(0,0,0));
	ASSERT(pStPointOrigin.GetTarget());
	pDCtStop->AddInput(pStPointOrigin.GetTarget());

	// X Axis
	SL_Ptr<DR_StCrvLine> pStLineX = NEW_OBJ(DR_StCrvLine, m_pFragment)(m_pFragment, MH_CrvLine(MH_Point3(0,0,0), MH_Vector3(1,0,0)));
	ASSERT(pStLineX.GetTarget());
	pDCtStop->AddInput(pStLineX.GetTarget());

	// Y Axis
	SL_Ptr<DR_StCrvLine> pStLineY = NEW_OBJ(DR_StCrvLine, m_pFragment)(m_pFragment, MH_CrvLine(MH_Point3(0,0,0), MH_Vector3(0,1,0)));
	ASSERT(pStLineY.GetTarget());
	pDCtStop->AddInput(pStLineY.GetTarget());

	// Z Axis
	SL_Ptr<DR_StCrvLine> pStLineZ = NEW_OBJ(DR_StCrvLine, m_pFragment)(m_pFragment, MH_CrvLine(MH_Point3(0,0,0), MH_Vector3(0,0,1)));
	ASSERT(pStLineZ.GetTarget());
	pDCtStop->AddInput(pStLineZ.GetTarget());

    // XY plane
	SL_Ptr<DR_StPlane> pStPlaneXY = NEW_OBJ(DR_StPlane, m_pFragment)(m_pFragment, MH_Plane(MH_Point3(0,0,0), MH_Vector3(0,0,1)));
	ASSERT(pStPlaneXY.GetTarget());
	pDCtStop->AddInput(pStPlaneXY.GetTarget());

	// YZ plane
	SL_Ptr<DR_StPlane> pStPlaneYZ = NEW_OBJ(DR_StPlane, m_pFragment)(m_pFragment, MH_Plane(MH_Point3(0,0,0), MH_Vector3(1,0,0)));
	ASSERT(pStPlaneYZ.GetTarget());
	pDCtStop->AddInput(pStPlaneYZ.GetTarget());

	// ZX plane
	SL_Ptr<DR_StPlane> pStPlaneZX = NEW_OBJ(DR_StPlane, m_pFragment)(m_pFragment, MH_Plane(MH_Point3(0,0,0), MH_Vector3(0,1,0)));
	ASSERT(pStPlaneZX.GetTarget());
	pDCtStop->AddInput(pStPlaneZX.GetTarget());

	SL_Ptr<DR_StXform> pStXform = NEW_OBJ(DR_StXform, m_pFragment)(m_pFragment);
	ASSERT(pStPlaneZX.GetTarget());

	SL_Ptr<DR_DCtAlignerPlane> pDCtAlignerPlane = NEW_OBJ(DR_DCtAlignerPlane, m_pFragment)(m_pFragment, pStPlaneXY, pStXform);
	ASSERT(pDCtAlignerPlane.GetTarget());
	pDCtAlignerPlane->AddOutput(pStXform.GetTarget());

	SL_Ptr<DR_DCtSketch2D> pDCtSketch2D = NEW_OBJ(DR_DCtSketch2D, m_pFragment)(m_pFragment, pStXform);
	ASSERT(pDCtSketch2D.GetTarget());
	pDCtStop->AddInput(pDCtSketch2D->GetNormal().GetTarget());

	// Create root DL Node
	m_pDLNode = NEW_OBJ1(GR_DLNode, GetStream(FW_DocumentData::eDL))(reinterpret_cast<GR_DLNode*>(0));

	// DL Node - Origin
	SL_Ptr<GR_DLNodeWorkpoint> pPointOrigin = NEW_OBJ(GR_DLNodeWorkpoint, m_pDLNode)(m_pDLNode, pStPointOrigin);

	// DL Node - X Axis
	SL_Ptr<GR_DLNodeWorkaxis> pAxisX = NEW_OBJ(GR_DLNodeWorkaxis, m_pDLNode)(m_pDLNode, pStLineX);
	pAxisX->SetColor(1,0,0);

	// DL Node - Y Axis
	SL_Ptr<GR_DLNodeWorkaxis> pAxisY = NEW_OBJ(GR_DLNodeWorkaxis, m_pDLNode)(m_pDLNode, pStLineY);
	pAxisY->SetColor(0,1,0);

	// DL Node - Z Axis
	SL_Ptr<GR_DLNodeWorkaxis> pAxisZ = NEW_OBJ(GR_DLNodeWorkaxis, m_pDLNode)(m_pDLNode, pStLineZ);
	pAxisZ->SetColor(0,0,1);

    // DL Node - XY plane
	SL_Ptr<GR_DLNodeWorkplane> pPlaneXY = NEW_OBJ(GR_DLNodeWorkplane, m_pDLNode)(m_pDLNode, pStPlaneXY, MH_Vector3(1,0,0));

	// DL Node - YZ plane
	SL_Ptr<GR_DLNodeWorkplane> pPlaneYZ = NEW_OBJ(GR_DLNodeWorkplane, m_pDLNode)(m_pDLNode, pStPlaneYZ, MH_Vector3(0,1,0));

	// DL Node - ZX plane
	SL_Ptr<GR_DLNodeWorkplane> pPlaneZX = NEW_OBJ(GR_DLNodeWorkplane, m_pDLNode)(m_pDLNode, pStPlaneZX, MH_Vector3(0,0,1));

	// DL Node - Sketch Node
	SL_Ptr<GR_DLNodeSketch2D> pSketchXY = NEW_OBJ(GR_DLNodeSketch2D, m_pDLNode)(m_pDLNode, pDCtSketch2D);
	pSketchXY->SetActive(true);
}

// Get the root storage
SL_Storage* FW_DocumentData::GetStorage()
{
	if(!m_pStorage)
		m_pStorage = NEW_OBJ2(SL_Storage)(m_pDoc->GetPathName());
	return m_pStorage;
}

// Get stream
SL_StreamObj* FW_DocumentData::GetStream(EStream eStream)
{
	SL_Storage* pStorage = GetStorage();
	if(!pStorage)
		return NULL;

	return pStorage->CreateStreamObj(eStream);
}

// Get root node of the doc
GR_DLNode* FW_DocumentData::GetDLNode() const
{
	ASSERT(m_pDLNode);
	return m_pDLNode;
}

// Get fragment used to store st and ct
DR_Fragment* FW_DocumentData::GetFragment() const
{
	ASSERT(m_pFragment);
	return m_pFragment;
}

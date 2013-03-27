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
#include "uc_workplanecmd.h"
#include <math.h>
#include "fw_view.h"
#include "fw_document.h"
#include "gr_dl.h"
#include "gr_dlpoint.h"
#include "gr_dlcrv.h"
#include "mh_crvray.h"
#include "mh_crvline.h"
#include "mh_crvlineseg.h"
#include "resource.h"

UC_WorkplaneCmd::UC_WorkplaneCmd(void)
:FW_Cmd(IDS_UC_WORKPLANE_DISPNAME,
		IDS_UC_WORKPLANE_TOOLTIP,
		IDB_UC_WORKPLANE,
		_T("UC_WorkplaneCmd"), 
		IDR_UC_WORKPLANE)
{
	m_pDL[0] = NULL;
	m_pDL[1] = NULL;
	m_pDL[2] = NULL;
}

UC_WorkplaneCmd::~UC_WorkplaneCmd(void)
{
}

UC_WorkplaneCmd* UC_WorkplaneCmd::GetCmd()
{
	static UC_WorkplaneCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_WorkplaneCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_WorkplaneCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_WorkplaneCmd::OnExecute()
{
	//SL_Storage* pStorage = SL_Manager::Get()->CreateStorage("C:\\a.dat");
	//pStorage->CreateStorage(1)->CreateStreamObj(1);
	//SL_StreamObj* p = pStorage->CreateStreamObj(5);
	//ULARGE_INTEGER nSize;
	//memset(&nSize, 0, sizeof(ULARGE_INTEGER));
	//p->SetSize(nSize);
	//p->operator <<(__int8(9));

	////p->operator <<(__int8(1));
	////p->operator <<(__int8(2));
	////p->operator <<(__int8(3));
	//delete pStorage;

	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;
	return TRUE;
}

// LButtonDown message
// virtual 
void UC_WorkplaneCmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
}

// LButtonUp message
// virtual 
void UC_WorkplaneCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(m_pDL[2])
	{
		if(!m_pDL[0])
			m_pDL[0] = m_pDL[2];
		else if(!m_pDL[1])
			m_pDL[1] = m_pDL[2];

///		m_pDL[2]->SetSelectStatus(GR_DL::eSelected);
		m_pDL[2]->Invalidate();
		m_pDL[2] = NULL;
	}
}

// MouseMove message
// virtual 
void UC_WorkplaneCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
//	FW_View* pView = (FW_View*) pWnd;
//	GR_RR* pRR = pView->GetRR();
//	if(!pRR)
//		return;
//
//	if(m_pDL[2])
//	{
////		m_pDL[2]->SetSelectStatus(GR_DL::eNormal);
//		m_pDL[2]->Invalidate();
//	}
//
//	MH_CrvRay ray;
//	pRR->GetRay(point, ray);
//
//	GR_DLNode* pDLNode = pRR->GetDLNode();
//	std::map<GR_DL*, MH_Point3>		mDL;
//	std::map<GR_DLNode*, MH_Point3> mDLNode;
//
//	pRR->HitTest(pDLNode, 
//		&mDL,
//		NULL,
//		&mDLNode,
//		NULL,
//		ray, 0.01f);
//
//	if(mDL.size()==1)
//	{
//		std::map<GR_DL*, MH_Point3>::iterator itDL = mDL.begin();
//		if(IsValid(itDL->first))
//		{
////			itDL->first->SetSelectStatus(GR_DL::ePreSelected);
//			itDL->first->Invalidate();
//			m_pDL[2] = itDL->first;
//		}
//	}
//
//	pRR->Invalidate();
}


// Is the GR_DL valid as an input to generate the sketch 2d
bool UC_WorkplaneCmd::IsValid(GR_DL*	pDL) const
{
	bool bValid = false;

	GR_DLPoint* pDLPoint	= dynamic_cast<GR_DLPoint*>(pDL);
	GR_DLCrv*	pDLCrv		= dynamic_cast<GR_DLCrv*>(pDL);

	//if (pDLPoint)
	//{
	//	if(m_pDL[0])
	//	{
	//		pDLCrv	 = dynamic_cast<GR_DLCrv*>(m_pDL[0]);
	//		if(pDLCrv)
	//		{
	//			MH_CrvLineSeg* pLineSeg = dynamic_cast<MH_CrvLineSeg*>(pDLCrv->GetCrv());
	//			if(pLineSeg)
	//			{
	//				if(MH_CrvLine(*pLineSeg).IsIn(pDLPoint->GetPoint()))
	//					return false;
	//			}
	//		}

	//	}
	//	bValid = true;
	//}
	//else if(pDLCrv)
	//{
	//	MH_CrvLineSeg* pLineSeg = dynamic_cast<MH_CrvLineSeg*>(pDLCrv->GetCrv());
	//	if(pLineSeg)
	//	{
	//		if(m_pDL[0])
	//		{
	//			GR_DLPoint* pDLPointTemp = dynamic_cast<GR_DLPoint*>(m_pDL[0]);
	//			GR_DLCrv* pDLCrvTemp	 = dynamic_cast<GR_DLCrv*>(m_pDL[0]);
	//			if(pDLPointTemp)
	//			{
	//				if(MH_CrvLine(*pLineSeg).IsIn(pDLPointTemp->GetPoint()))
	//					return false;
	//				bValid = true;
	//			}
	//			//else if(pDLCrvTemp)
	//			//{
	//			//	MH_CrvLineSeg* pLineSeg = dynamic_cast<MH_CrvLineSeg*>(pDLCrvTemp->GetCrv());
	//			//	if(pLineSeg)
	//			//	{
	//			//		if(pLineSeg->)
	//			//	}
	//			//	&& !dynamic_cast<MH_CrvLineSeg*>(pDLCrv->GetCrv()))
	//			//	bValid = true;
	//		}
	//	}
	//	if(m_pDL[0])
	//	{
	//		GR_DLPoint* pDLPointTemp = dynamic_cast<GR_DLPoint*>(m_pDL[0]);
	//		GR_DLCrv* pDLCrvTemp	 = dynamic_cast<GR_DLCrv*>(m_pDL[0]);
	//		if(pDLPointTemp)
	//			bValid = true;
	//		//else if(pDLCrvTemp)
	//		//{
	//		//	MH_CrvLineSeg* pLineSeg = dynamic_cast<MH_CrvLineSeg*>(pDLCrvTemp->GetCrv());
	//		//	if(pLineSeg)
	//		//	{
	//		//		if(pLineSeg->)
	//		//	}
	//		//	&& !dynamic_cast<MH_CrvLineSeg*>(pDLCrv->GetCrv()))
	//		//	bValid = true;
	//	}
	//	else
	//		bValid = true;
	//}

	return bValid;
}

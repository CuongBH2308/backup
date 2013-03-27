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
#include "uc_sketch2dcmd.h"
#include <math.h>
#include <typeinfo.h>
#include "fw_view.h"
#include "fw_document.h"
#include "resource.h"
#include "gr_dl.h"
#include "gr_dlpoint.h"
#include "gr_dlcrv.h"
#include "gr_dlsrf.h"
#include "gr_dlattribselect.h"
#include "gr_dlnodegrids.h"
#include "mh_crvray.h"
#include "mh_crvline.h"
#include "mh_crvlineseg.h"
#include "mh_srfrect.h"
#include "mh_plane.h"
#include "mm_txnmanager.h"
#include "sl_mm.h"

UC_Sketch2DCmd::UC_Sketch2DCmd(void)
:FW_Cmd(IDS_UC_SKETCH2D_DISPNAME,
		IDS_UC_SKETCH2D_TOOLTIP,
		IDB_UC_SKETCH2D,
		_T("UC_Sketch2DCmd"),
		IDR_UC_SKETCH2D)
{
}

UC_Sketch2DCmd::~UC_Sketch2DCmd(void)
{
}

UC_Sketch2DCmd* UC_Sketch2DCmd::GetCmd()
{
	static UC_Sketch2DCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_Sketch2DCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_Sketch2DCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_Sketch2DCmd::OnExecute()
{
	FW_Cmd::OnExecute();
	return TRUE;
}

// LButtonDown message
// virtual 
void UC_Sketch2DCmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
}

// LButtonUp message
// virtual 
void UC_Sketch2DCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	//FW_View* pView = (FW_View*) pWnd;
	//GR_RR* pRR = pView->GetRR();
	//if(!pRR)
	//	return;

	//for(std::map<GR_DL*, MH_Point3>::iterator itDL = m_mDL.begin(); itDL != m_mDL.end(); itDL++)
	//{
	//	if( !IsValid(itDL->first) )
	//		continue;

	//	GR_DLSrf* pDLSrf = dynamic_cast<GR_DLSrf*>(itDL->first);
	//	if(!pDLSrf)
	//		continue;

	//	MH_Srf* pSrf = pDLSrf->GetSrf();
	//	if(!pSrf)
	//		continue;

	//	MH_SrfRect* pSrfRect = dynamic_cast<MH_SrfRect*>(pSrf);
	//	if(!pSrf)
	//		continue;

	class CT
	{
	public:
		CT(){};
		~CT(){};
		std::vector< SL_Ptr<MH_Point3>, MM_Allocator<SL_Ptr<MH_Point3> > > m_v;
	};

	CT* pCT = NEW_OBJ2(CT)();
	MM_TxnManager::Get()->StartTxn();
	MH_Point3 *p = NEW_OBJ2(MH_Point3)(0,0,0);
	pCT->m_v.push_back(p);
	MM_TxnManager::Get()->EndTxn();

	MM_TxnManager::Get()->StartTxn();
	MH_Point3 *p2 = NEW_OBJ2(MH_Point3)(1,0,0);
	pCT->m_v.push_back(p2);
	MM_TxnManager::Get()->EndTxn();


	MM_TxnManager::Get()->UndoTxn();
	MM_TxnManager::Get()->UndoTxn();

		//class CT
		//{
		//public:
		//	CT(){m_i=0;};
		//	std::vector< int, MM_Allocator<int> > m_v;
		//	int m_i;
		//};

		//MM_Manager* pMemMgr = MM_Manager::Get();
		//CT* pCT = NEW_OBJ2(CT)();

		//pMemMgr->Dump("c:\\a.xml");

		//MM_TxnManager::Get()->StartTxn();
		//pCT->m_v.push_back(1);
		//pCT->m_i = 1;
		//MM_TxnManager::Get()->EndTxn();

		//MM_TxnManager::Get()->StartTxn();
		//pCT->m_v.push_back(2);
		//pCT->m_i = 2;
		//MM_TxnManager::Get()->EndTxn();


		//MM_TxnManager::Get()->UndoTxn();
		//MM_TxnManager::Get()->UndoTxn();

		//int iii = 0;
//		new GR_DLNodeGrids(pRR->GetDLNode(), new MH_Plane(pSrfRect->GetPt(), pSrfRect->GetNormal()));
	//}

	//pRR->Invalidate();
}

// MouseMove message
// virtual 
void UC_Sketch2DCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
	//FW_View* pView = (FW_View*) pWnd;
	//GR_RR* pRR = pView->GetRR();
	//if(!pRR)
	//	return;

	//for(std::map<GR_DL*, MH_Point3>::iterator itDL = m_mDL.begin(); itDL != m_mDL.end(); itDL++)
	//{
	//	GR_DLAttribSelect* pDLAttribSelect = NULL;
	//	GR_DLAttrib* pDLAttrib = itDL->first->GetAttrib(typeid(GR_DLAttribSelect));
	//	if(pDLAttrib) 
	//	{
	//		pDLAttribSelect = dynamic_cast<GR_DLAttribSelect*>(pDLAttrib);
	//		ASSERT(pDLAttribSelect);
	//		if(pDLAttribSelect->GetStatus() == GR_DLAttribSelect::ePreSel)
	//		{
	//			pDLAttribSelect->SetStatus(GR_DLAttribSelect::eUnSel);
	//			itDL->first->Invalidate();
	//		}

	//		if(pDLAttribSelect->GetStatus() != GR_DLAttribSelect::eSel)
	//		{
	//			std::map<GR_DL*, MH_Point3>::iterator itDLTemp = itDL;
	//			itDL++;
	//			m_mDL.erase(itDLTemp);
	//			if(m_mDL.size() == 0)
	//				break;
	//			itDL--;
	//		}
	//	}
	//}

	//MH_CrvRay ray;
	//pRR->GetRay(point, ray);

	//GR_DLNode* pDLNode = pRR->GetDLNode();
	//MH_Point3 ptFrom;
	//MH_Vector3 vDirect;
	//const std::vector<type_info>* pvInternalNameDL = NULL;
	//const std::vector<type_info>* pvInternalNameDLNode = NULL;
	//
	//pRR->HitTest(pDLNode, 
	//	&m_mDL,
	//	pvInternalNameDL,
	//	&m_mDLNode,
	//	pvInternalNameDLNode,
	//	ray, 0.1f);

	//for(std::map<GR_DL*, MH_Point3>::iterator itDL = m_mDL.begin(); itDL != m_mDL.end(); itDL++)
	//{
	//	if( !IsValid(itDL->first) )
	//		continue;

	//	GR_DLAttribSelect* pDLAttribSelect = NULL;
	//	GR_DLAttrib* pDLAttrib = itDL->first->GetAttrib(typeid(GR_DLAttribSelect));
	//	if(pDLAttrib) 
	//	{
	//		pDLAttribSelect = dynamic_cast<GR_DLAttribSelect*>(pDLAttrib);
	//		ASSERT(pDLAttribSelect);
	//		if(pDLAttribSelect->GetStatus() == GR_DLAttribSelect::eSel)
	//			continue;
	//	}
	//	else
	//	{
	//		pDLAttribSelect = new GR_DLAttribSelect();
	//		itDL->first->AddAttrib(pDLAttribSelect, true);
	//	}

	//	pDLAttribSelect->SetStatus(GR_DLAttribSelect::ePreSel);
	//	itDL->first->Invalidate();
	//}

	//pRR->Invalidate();
}


// Is the GR_DL valid as an input to generate the sketch 2d
bool UC_Sketch2DCmd::IsValid(GR_DL*	pDL) const
{
	//GR_DLSrf* pDLSrf = dynamic_cast<GR_DLSrf*>(pDL);
	//if(!pDLSrf)
	//	return false;

	//MH_Srf* pSrf = pDLSrf->GetSrf();
	//if(!pSrf)
	//	return false;

	//MH_SrfRect* pSrfRect = dynamic_cast<MH_SrfRect*>(pSrf);
	//if(!pSrf)
	//	return false;

	return true;
}
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
#include "uc_testcrvnurbscmd.h"
#include "dr_stcrvnurbs.h"
#include "fw_view.h"
#include "gr_dlnode.h"
#include "gr_dlnodesketch2d.h"
#include "gr_selectionfilterset.h"
#include "gr_selectionfiltersketchcrv.h"
#include "gr_selectionsketchcrv.h"
#include "mh_crvray.h"
#include "mh_crdsys.h"
#include "mh_plane.h"
#include "resource.h"
#include "S2_CrvNurbsReq.h"
#include "FW_MDIFrameWnd.h"
#include "FW_Document.h"
#include "MH_CrvBezier.h"
#include "MH_SrfNurbs.h"
#include "GR_DLSrf.h"
#include "S2_CrvBezierReq.h"
#include "GR_Color.h"
#include "sl_mm.h"
#include "MH_CrvArc.h"
#include "GR_DLCrv.h"
#include "MH_SrfSphere.h"
#include "MH_SrfCylinder.h"
#include "GR_DLNodeLight.h"

UC_TestCrvNurbsCmd::UC_TestCrvNurbsCmd(void)
:FW_Cmd(IDS_UC_TEST_CRVNURBS_DISPNAME,
		IDS_UC_TEST_CRVNURBS_TOOLTIP,
		IDB_UC_TEST_CRVNURBS,_T("UC_TestCrvNurbsCmd"))
{

}

UC_TestCrvNurbsCmd::~UC_TestCrvNurbsCmd(void)
{
}

UC_TestCrvNurbsCmd* UC_TestCrvNurbsCmd::GetCmd()
{
	static UC_TestCrvNurbsCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_TestCrvNurbsCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_TestCrvNurbsCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_TestCrvNurbsCmd::OnExecute()
{
	// Initialize
	FW_Cmd::OnExecute();

	// Get active view
	FW_View* pView = GetView();
	if(!pView)
		return FALSE;

	// Get root node
	GR_DLNode* pDLNode = pView->GetDLNode();
	if(!pDLNode)
		return FALSE;

	m_pDLNodeSketch2D = GR_DLNodeSketch2D::GetActive(pDLNode);
	if(!m_pDLNodeSketch2D)
		return FALSE;

	GR_DLNodeLight* p = NEW_OBJ(GR_DLNodeLight, m_pDLNodeSketch2D)(m_pDLNodeSketch2D, MH_Point3(3,3,0), MH_Vector3(-1,-1,-1));
	p->SetColor(GR_Color(0.0f,1.0f,0.0f,1.0f));
	//MH_SrfSphere* p = NEW_OBJ(MH_SrfSphere, m_pDLNodeSketch2D)(MH_Point3(0,0,0), 0.1);
	////MH_SrfCylinder* p = NEW_OBJ(MH_SrfCylinder, m_pDLNodeSketch2D)(MH_Point3(0,0,0), MH_Vector3(0,0,5), 3, 0);
	//MH_SrfNurbs* pN = NEW_OBJ(MH_SrfNurbs, p)();
	//*pN = p->GetNurbs();
	//GR_DLSrf* pp = NEW_OBJ(GR_DLSrf, m_pDLNodeSketch2D)(m_pDLNodeSketch2D, pN);

	//MH_Point3 ptCenter(0,0,0);
	//MH_CrvArc* pArc = NEW_OBJ(MH_CrvArc, m_pDLNodeSketch2D)(ptCenter, MH_Vector3(0.0f, 0.0f, 1.0f), ptCenter+MH_Vector3(1.0f, 0.0f, 0.0f), PI);

	////MH_CrvArc* pArc = NEW_OBJ(MH_CrvArc, m_pDLNodeSketch2D)(MH_Point3(), MH_Vector3(0,0,1), MH_Point3(3,0,0), PI*2);
	//GR_DLCrv* p = NEW_OBJ(GR_DLCrv, m_pDLNodeSketch2D)(m_pDLNodeSketch2D, pArc);

/*

	MH_CVVect vCV;
	vCV.push_back(MH_CV(MH_Point3(-3.971428, 1.457143, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-3.971428, 1.457143, -0.794082), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-4.745054, 1.278063, -0.794082), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-5.518680, 1.098983, -0.794082), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-5.518680, 1.098983, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-5.518680, 1.098983, 0.794082), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-4.745054, 1.278063, 0.794082), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-3.971428, 1.457143, 0.794082), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-3.971428, 1.457143, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-2.742857, 0.828571, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-2.742857, 0.828571, -1.849250), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-4.544468, 0.411532, -1.849250), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-6.346079, -0.005508, -1.849250), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-6.346079, -0.005508, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-6.346079, -0.005508, 1.849250), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-4.544468, 0.411532, 1.849250), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-2.742857, 0.828571, 1.849250), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-2.742857, 0.828571, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-3.857143, -0.600000, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-3.857143, -0.600000, -0.441500), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-4.287269, -0.699566, -0.441500), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-4.717396, -0.799133, -0.441500), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-4.717396, -0.799133, 0.000000), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-4.717396, -0.799133, 0.441500), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-4.287269, -0.699566, 0.441500), 1.000000)); 
	vCV.push_back(MH_CV(MH_Point3(-3.857143, -0.600000, 0.441500), 0.707107)); 
	vCV.push_back(MH_CV(MH_Point3(-3.857143, -0.600000, 0.000000), 1.000000)); 

	FloatVect vKnotS;
	FloatVect vKnotT;

	vKnotS.push_back(0.000000); 
	vKnotS.push_back(0.000000); 
	vKnotS.push_back(0.000000); 
	vKnotS.push_back(0.250000); 
	vKnotS.push_back(0.250000); 
	vKnotS.push_back(0.500000); 
	vKnotS.push_back(0.500000); 
	vKnotS.push_back(0.750000); 
	vKnotS.push_back(0.750000); 
	vKnotS.push_back(1.000000); 
	vKnotS.push_back(1.000000); 
	vKnotS.push_back(1.000000); 

	vKnotT.push_back(0.000000); 
	vKnotT.push_back(0.000000); 
	vKnotT.push_back(0.000000); 
	vKnotT.push_back(1.000000); 
	vKnotT.push_back(1.000000); 
	vKnotT.push_back(1.000000); 

	MH_SrfNurbs* pSrfNurbs = NEW_OBJ(MH_SrfNurbs,m_pDLNodeSketch2D)(vCV,9,3,3,vKnotS,vKnotT);
	GR_DLSrf* pDLSrf = NEW_OBJ(GR_DLSrf, m_pDLNodeSketch2D)(m_pDLNodeSketch2D, pSrfNurbs);
	pDLSrf->SetColor(GR_Color(0.0f,0.0f,0,1.0f));*/
	pView->Invalidate();
	return TRUE;
}

// LButtonUp message
// virtual 
void UC_TestCrvNurbsCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	// Get the cross point of the ray and the sketch plane
	MH_Point3 pt;
	MH_CrdSys crdSys(m_pDLNodeSketch2D->GetNetTransform());
	pView->GetPt(point, MH_Plane(crdSys.GetOrigin(), crdSys.GetZAxis()), pt);

	GR_SelectionSet selSet;
	GR_SelectionFilterSet filterSet;
	filterSet.Add(new GR_SelectionFilterSketchCrv());
	MH_CrvRay ray;
	pView->GetRay(point, ray);
	m_pDLNodeSketch2D->Select(selSet, filterSet, ray, 0.1f);
	// Delete all items in the filterSet set
	filterSet.DeleteAll();


	if(selSet.IsNotEmpty())
	{
		GR_SelectionSketchCrv* pSel = dynamic_cast<GR_SelectionSketchCrv*>(selSet.GetAll().front());
		if(pSel)
		{
			//m_pDLNodeSketch2D->RemoveDL(pSel->GetDLPtrVect().front());
			DR_StCrvNurbs* pStCrvNurbs = dynamic_cast<DR_StCrvNurbs*>(pSel->GetStCrv());
			if(pStCrvNurbs)
			{
				MH_CrvNurbs nurbs = pStCrvNurbs->GetNurbs();
				////nurbs.Dump();
				//int no = 1;
				//float uu = 1.0/3;
				//nurbs.InsertKnot(uu,no);
				////nurbs.Dump();

				//for(int ii = 0; ii<no; ii++)
				//{
				//	nurbs.RemoveKnot(uu);
				//	//nurbs.Dump();
				//}


				MH_CrvNurbs nurbs2;
				MH_CrvBezierVect beziers;
				nurbs.ConvertToBeziers(beziers, nurbs2);
				for(int iii= 0; iii<beziers.size(); iii++)
				{
					S2_CrvBezierReq req(FW_MDIFrameWnd::GetActiveDoc(), m_pDLNodeSketch2D, beziers[iii]);
					FW_MDIFrameWnd::GetActiveDoc()->ExecuteRequest(&req);
				}

				////int no = 1;
				////float uu = 0.5;
				////nurbs.InsertKnot(uu,no);

				//S2_CrvNurbsReq req(FW_MDIFrameWnd::GetActiveDoc(), m_pDLNodeSketch2D, nurbs);
				//FW_MDIFrameWnd::GetActiveDoc()->ExecuteRequest(&req);


				//nurbs.Dump();

				////nurbs.ElevateDegree();
				////nurbs.Dump();

				//for(int ii=0; ii<no; ii++)
				//{
				//	nurbs.InsertKnot(uu);
				//	nurbs.Dump();
				//}

				//MH_CrvNurbs nurbs2 = pStCrvNurbs->GetNurbs();
				//nurbs2.InsertKnot(uu,no);
				//nurbs2.Dump();

				//ASSERT(nurbs == nurbs2);


				//nurbs.SetCV(1, MH_CV(1,1,1,1));
				//nurbs.Cleanup();
				//pStCrvNurbs->SetNurbs(nurbs);
				m_pDLNodeSketch2D->Update();
			}
		}
		selSet.DeleteAll();
	}

	pView->Invalidate();
	OnTerminate();
}


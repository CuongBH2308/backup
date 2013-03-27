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
#include "uc_renderlightcmd.h"
#include <math.h>
#include "fw_mdiframewnd.h"
#include "fw_view.h"
#include "fw_document.h"
#include "fw_mdiframewnd.h"
#include "mh_point3.h"
#include "mh_vector3.h"
#include "resource.h"
#include "uc_renderlightreq.h"
#include "uc_renderlightdlg.h"

UC_RenderLightCmd::UC_RenderLightCmd(void)
:FW_Cmd(IDS_UC_RENDERLIGHT_DISPNAME,
		IDS_UC_RENDERLIGHT_TOOLTIP,
		IDB_UC_RENDERLIGHT,
		_T("UC_RenderLightCmd"),
		IDR_UC_RENDERLIGHT)
{
}

UC_RenderLightCmd::~UC_RenderLightCmd(void)
{
}

UC_RenderLightCmd* UC_RenderLightCmd::GetCmd()
{
	static UC_RenderLightCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_RenderLightCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_RenderLightCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_RenderLightCmd::OnExecute()
{
	// Execute basic function to terminate previous command
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	// UC_RenderLightDlg will be created in the constructor
	m_pRenderLightDlg = new UC_RenderLightDlg(this, FW_MDIFrameWnd::GetMDIFrameWnd());
	if(m_pRenderLightDlg)
		m_pRenderLightDlg->ShowWindow(SW_SHOW);

	return TRUE;
}

// Some other command is activated, so this command will be terminated
// virtual 
BOOL UC_RenderLightCmd::OnTerminate()
{
	// OnCancel will destroy the dialog and delete m_pPropertyDlg
	if(m_pRenderLightDlg && m_pRenderLightDlg->GetSafeHwnd())
	{
		// UC_PropertyDlg::PostNcDestroy will delete m_pPropertyDlg
		m_pRenderLightDlg->DestroyWindow();
		m_pRenderLightDlg = NULL;
	}

	FW_Cmd::OnTerminate();
	return TRUE;
}

// LButtonDown message
// virtual 
void UC_RenderLightCmd::OnLButtonDown(CWnd* pWnd, UINT nFlags, CPoint point)
{
}

// LButtonUp message
// virtual 
void UC_RenderLightCmd::OnLButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	// Convert the window to FW_View
	FW_View* pView = dynamic_cast<FW_View*>(pWnd);
	if(!pView)
		return;

	//static float f = 0;

	//MH_Point3 pt(cos(f)*3, 0, sin(f)*3);
	//f += 3.14/4;

	//UC_RenderLightReq req(FW_MDIFrameWnd::GetActiveDoc(), 
	//	GR_DLAttribLight::Ambient(0.5f, 0.5f, 0.5f, 1.0f),
	//	GR_DLAttribLight::Diffuse(1.0f, 1.0f, 1.0f, 1.0f),
	//	GR_DLAttribLight::Specular(),
	//	GR_DLAttribLight::Position(pt.m_f[0], pt.m_f[1], pt.m_f[2], 1));
	//FW_MDIFrameWnd::GetActiveDoc()->ExecuteRequest(&req);
	
	pView->Invalidate();
}

// MouseMove message
// virtual 
void UC_RenderLightCmd::OnMouseMove(CWnd* pWnd, UINT nFlags, CPoint point)
{
}


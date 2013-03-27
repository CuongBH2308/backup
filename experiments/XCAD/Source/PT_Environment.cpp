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
#include "pt_environment.h"
#include "fw_winapp.h"
#include "fw_mdiframewnd.h"
#include "fw_environmentmanager.h"
#include "fw_uimanager.h"
#include "fw_uicmdbars.h"
#include "fw_cmds.h"
#include "fw_cmdmanager.h"
#include "fw_uicmdbarctrls.h"
#include "uc_viewrotatecmd.h"
#include "uc_viewzoomcmd.h"
#include "uc_viewmovecmd.h"
#include "uc_undocmd.h"
#include "uc_workplanecmd.h"
#include "uc_sketch2dcmd.h"
#include "uc_propertycmd.h"
#include "uc_renderlightcmd.h"
#include "uc_testfragmentcmd.h"
#include "uc_testcrvnurbscmd.h"
#include "s2_dragcmd.h"
#include "s2_crvlinesegcmd.h"
#include "s2_crvnurbscmd.h"
#include "s2_crvbeziercmd.h"
#include "pt_ftrextrusioncmd.h"
#include "pt_ftrrevolvecmd.h"

PT_Environment::PT_Environment()
:FW_Environment(FW_WinApp::GetWinApp()->GetEnvironmentManager()->GetEnvironments(),
				_T("PT_Environment"))
{
	FW_PanelBar* pPanelBar = FW_MDIFrameWnd::GetMDIFrameWnd()->GetPanelBar();
	ASSERT(pPanelBar);

	//////////////////////////////////////////////////////////////////////////
	// Add UC_Toolbar
	//////////////////////////////////////////////////////////////////////////
	FW_UICmdBar* pUICmdBar = FW_WinApp::GetWinApp()->GetUIManager()->Add(
		_T("Universal Tools"),
		_T("UC_Toolbar"));
	if(!pUICmdBar)
		return;
	pPanelBar->AddCmdBar2Menu(pUICmdBar);

	// Add command bar that should be displayed in this env
	Add(pUICmdBar);

	// Create commands and add them to the command bar
	// 1.Once a command is new up, it will be added into FW_Cmds that will 
	// manage the life cycle of this command
	// 2.We should add it into the UI manager 
	pUICmdBar->Add(UC_UndoCmd::GetCmd());
	pUICmdBar->Add(UC_ViewRotateCmd::GetCmd());
	pUICmdBar->Add(UC_ViewZoomCmd::GetCmd());
	pUICmdBar->Add(UC_ViewMoveCmd::GetCmd());
	pUICmdBar->Add(UC_WorkplaneCmd::GetCmd());
	pUICmdBar->Add(UC_Sketch2DCmd::GetCmd());
	pUICmdBar->Add(UC_PropertyCmd::GetCmd());
	pUICmdBar->Add(UC_TestFragmentCmd::GetCmd());
	pUICmdBar->Add(UC_TestCrvNurbsCmd::GetCmd());

	FW_MDIFrameWnd::GetMDIFrameWnd()->AddToolBar(pUICmdBar);

	//////////////////////////////////////////////////////////////////////////
	// Add S2_Toolbar
	//////////////////////////////////////////////////////////////////////////
	pUICmdBar = FW_WinApp::GetWinApp()->GetUIManager()->Add(
		_T("2D Sketch"),
		_T("S2_Toolbar"));
	if(!pUICmdBar)
		return;
	pPanelBar->AddCmdBar2Menu(pUICmdBar);

	// Add command bar that should be displayed in this env
	Add(pUICmdBar);

	// Add drag command
	pUICmdBar->Add(S2_DragCmd::GetCmd());

	// Create commands and add them to the command bar
	// 1.Once a command is new up, it will be added into FW_Cmds that will 
	// manage the life cycle of this command
	// 2.We should add it into the UI manager 
	pUICmdBar->Add(S2_CrvLineSegCmd::GetCmd());
	pUICmdBar->Add(S2_CrvNurbsCmd::GetCmd());
	pUICmdBar->Add(S2_CrvBezierCmd::GetCmd());

	//////////////////////////////////////////////////////////////////////////
	// Add PT_Toolbar
	//////////////////////////////////////////////////////////////////////////
	pUICmdBar = FW_WinApp::GetWinApp()->GetUIManager()->Add(
		_T("Part Feature"),
		_T("PT_Toolbar"));
	if(!pUICmdBar)
		return;
	pPanelBar->AddCmdBar2Menu(pUICmdBar);

	// Add command bar that should be displayed in this env
	Add(pUICmdBar);

	// Add extrusion command
	pUICmdBar->Add(PT_FtrExtrusionCmd::GetCmd());

	// Add extrusion command
	pUICmdBar->Add(PT_FtrRevolveCmd::GetCmd());

	// Add tool bar
	//FW_MDIFrameWnd::GetMDIFrameWnd()->AddToolBar(pUICmdBar);


	//////////////////////////////////////////////////////////////////////////
	// Add Render_Toolbar
	//////////////////////////////////////////////////////////////////////////
	pUICmdBar = FW_WinApp::GetWinApp()->GetUIManager()->Add(
		_T("Render Scene"),
		_T("Render_Toolbar"));
	if(!pUICmdBar)
		return;
	pPanelBar->AddCmdBar2Menu(pUICmdBar);

	// Add command bar that should be displayed in this env
	Add(pUICmdBar);

	// Add extrusion command
	pUICmdBar->Add(UC_RenderLightCmd::GetCmd());
}

PT_Environment::~PT_Environment(void)
{
}

PT_Environment* PT_Environment::GetEnvironment()
{
	static PT_Environment* pPT_Environment = NULL;
	if(!pPT_Environment)
		pPT_Environment = new PT_Environment();

	return pPT_Environment;
}

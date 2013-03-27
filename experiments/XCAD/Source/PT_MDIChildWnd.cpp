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
#include "pt_mdichildwnd.h"
#include "pt_environment.h"
#include "fw_mdiframewnd.h"

IMPLEMENT_DYNCREATE(PT_MDIChildWnd, FW_MDIChildWnd)

// PT_MDIChildWnd construction/destruction
PT_MDIChildWnd::PT_MDIChildWnd()
{
	// TODO: add member initialization code here
}

PT_MDIChildWnd::~PT_MDIChildWnd()
{
}

BEGIN_MESSAGE_MAP(PT_MDIChildWnd, FW_MDIChildWnd)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()


// PT_MDIChildWnd message handlers
int PT_MDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (FW_MDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void PT_MDIChildWnd::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd) 
{
	FW_MDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);

	// Get panel bar
	FW_PanelBar* pPanelBar = FW_MDIFrameWnd::GetMDIFrameWnd()->GetPanelBar();
	ASSERT(pPanelBar);

	if(bActivate)
		pPanelBar->Activate(PT_Environment::GetEnvironment()->GetDefaultCmdBar());
	else
		pPanelBar->Activate(NULL);
}

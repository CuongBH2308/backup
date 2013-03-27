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
#include "uc_undocmd.h"
#include "uc_undoreq.h"
#include "fw_document.h"
#include "fw_view.h"
#include "resource.h"

UC_UndoCmd::UC_UndoCmd(void)
:FW_Cmd(IDS_UC_UNDO_DISPNAME,
		IDS_UC_UNDO_TOOLTIP,
		IDB_UC_UNDO,
		_T("UC_UndoCmd"), 
		IDR_UC_UNDO)
{
}

UC_UndoCmd::~UC_UndoCmd(void)
{
}

UC_UndoCmd* UC_UndoCmd::GetCmd()
{
	static UC_UndoCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_UndoCmd();
	return pCmd;
}

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_UndoCmd::OnExecute()
{
	// Initialize
	BOOL bOK = FW_Cmd::OnExecute();
	if(!bOK)
		return FALSE;

	// Get active document
	FW_Document* pDoc = GetDocument();
	if(!pDoc)
		return FALSE;

	// Get active view
	FW_View* pView = GetView();
	if(!pView)
		return FALSE;

	// Execute request
	UC_UndoReq req(pDoc);
	bOK = SUCCEEDED(pDoc->ExecuteRequest(&req));

	// Invalidate the view
	pView->Invalidate();

	// Terminate the command
	OnTerminate();
	return bOK;
}
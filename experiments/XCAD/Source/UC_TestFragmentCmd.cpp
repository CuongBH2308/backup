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
#include "uc_testfragmentcmd.h"
#include "dr_fragment.h"
#include "fw_document.h"
#include "resource.h"

UC_TestFragmentCmd::UC_TestFragmentCmd(void)
:FW_Cmd(IDS_UC_TEST_FRAGMENT_DISPNAME,
		IDS_UC_TEST_FRAGMENT_TOOLTIP,
		IDB_UC_TEST_FRAGMENT,
		_T("UC_TestFragmentCmd"), 
		IDR_UC_TEST_FRAGMENT)
{
}

UC_TestFragmentCmd::~UC_TestFragmentCmd(void)
{
}

UC_TestFragmentCmd* UC_TestFragmentCmd::GetCmd()
{
	static UC_TestFragmentCmd* pCmd = NULL;
	if(!pCmd)
		pCmd = new UC_TestFragmentCmd();
	return pCmd;
}

BEGIN_MESSAGE_MAP(UC_TestFragmentCmd,FW_Cmd)
END_MESSAGE_MAP()

// If the button in the command bar is clicked, then this function will be called
// virtual 
BOOL UC_TestFragmentCmd::OnExecute()
{
	// Execute basic function to terminate previous command
	FW_Cmd::OnExecute();
	GetDocument()->GetFragment()->Dump("a.txt");

	OnTerminate();
	return TRUE;
}
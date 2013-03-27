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


#pragma once
#include "xcad.h"

interface IFWCmdManager;
class FW_Cmd;
class FW_Cmds;
class FW_WinApp;
class XCAD_EXPORT FW_CmdManager
{
public:
	FW_CmdManager(FW_WinApp* pApp);
	virtual ~FW_CmdManager(void);

	// Get m_spIFWCmdManager
	CComPtr<IFWCmdManager> GetInterface();

	// Set m_spIFWCmdManager to NULL
	void ResetInterface();

	// Get commands
	FW_Cmds* GetCmds(void);

	// Execute command
	BOOL Execute(FW_Cmd* pCmd);

	// Terminate command
	BOOL Terminate(FW_Cmd* pCmd);

private:
	CComPtr<IFWCmdManager> m_spIFWCmdManager;
	FW_WinApp* m_pApp;
	FW_Cmds* m_pCmds;
};

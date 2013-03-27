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
#include <vector>
#include "xcad.h"

interface IFWCmds;
class FW_Cmd;
class FW_CmdManager;
class XCAD_EXPORT FW_Cmds
{
	friend FW_CmdManager;

public:
	// Get m_spIFWCmds;
	CComPtr<IFWCmds> GetInterface();

	// Set m_spIFWCmds to NULL
	void ResetInterface();

	// Add a command
	void Add(FW_Cmd* pCmd);

	// Add a command
	FW_Cmd* Add(UINT nDisplayName,
		UINT nTooltip,
		UINT nImages,
		const CString& strInternalName,
		const int& iCmdId = -1);

	// Add a command
	FW_Cmd* Add(const CString& strDisplayName,
		const CString& strTooltip,
		CImageList& imageList,
		const CString& strInternalName,
		const int& iCmdId = -1);

	// Get the command upon the command id
	FW_Cmd* GetCmd(int iCmdId) const;

	// Get the active command
	FW_Cmd* GetActiveCmd() const;

	// Generate a new command ID.
	// If it is an add-in command, the user should not specify a command for it, then 
	// we should use this function to generate a new command ID for this command
	int GenerateCmdId() const;

	// Handle messages
	virtual BOOL OnCmdMsg( UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo );
protected:
	FW_Cmds(FW_CmdManager* pCmdManager);
	virtual ~FW_Cmds(void);

private:
	FW_CmdManager* m_pCmdManager;
	std::vector<FW_Cmd*> m_vCmd;

	CComPtr<IFWCmds> m_spIFWCmds;
};

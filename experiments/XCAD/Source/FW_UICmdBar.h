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

/************************************************************************
FW_UICmdBar include the following types
1. toolbar
2. popup menu
3. dropdown toolbar
************************************************************************/
#include "xcad.h"

interface IFWUICmdBar;
class FW_UICmdBars;
class FW_UICmdBarCtrl;
class FW_UICmdBarCtrls;
class FW_Cmd;

class XCAD_EXPORT FW_UICmdBar
{
	friend FW_UICmdBars;

public:
	// Get m_spIFWUICmdBar;
	CComPtr<IFWUICmdBar> GetInterface();

	// Set m_spIFWUICmdBar to NULL
	void ResetInterface();

	FW_UICmdBarCtrls* GetUICmdBarCtrls();

	// Get display name
	CString GetDisplayName() const;

	// Get unique internal name 
	CString GetInternalName() const;

	// Associate a FW_UICmdBarCtrl with a command
	FW_UICmdBarCtrl* Add(FW_Cmd* pCmd);

protected:
	FW_UICmdBar(FW_UICmdBars* pUICmdBars, const CString& strDisplayName, const CString& strInternalName);
	virtual ~FW_UICmdBar(void);

private:
	CComPtr<IFWUICmdBar> m_spIFWUICmdBar;
	CString m_strDisplayName;
	CString m_strInternalName;
	FW_UICmdBars* m_pUICmdBars;
	FW_UICmdBarCtrls* m_pUICmdBarCtrls;
};

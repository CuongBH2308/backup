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

class FW_UICmdBar;
class FW_UICmdBars;
class FW_WinApp;
class XCAD_EXPORT FW_UIManager
{
	friend FW_WinApp;

public:
	// Get m_spIFWUIManager;
	CComPtr<IFWUIManager> GetInterface();

	// Set m_spIFWUIManager to NULL
	void ResetInterface();

	FW_UICmdBars* GetUICmdBars();

	// Add a command bar according to the type
	FW_UICmdBar* Add(const CString& strDisplayName,
		const CString& strInternalName);

protected:
	FW_UIManager(FW_WinApp* pApp);
	virtual ~FW_UIManager(void);

private:
	CComPtr<IFWUIManager> m_spIFWUIManager;
	FW_WinApp*		m_pApp;
	FW_UICmdBars*	m_pUICmdBars;
};

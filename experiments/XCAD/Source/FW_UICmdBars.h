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
#include "fw_uicmdbar.h"
#include "xcad.h"

interface IFWUICmdBars;
class FW_UIManager;
class XCAD_EXPORT FW_UICmdBars
{
	friend FW_UIManager;

public:
	// 	Get m_spIFWUICmdBars;
	CComPtr<IFWUICmdBars> GetInterface();

	// Set m_spIFWUICmdBars to NULL
	void ResetInterface();

	// Add a command bar according to the type
	FW_UICmdBar* Add(const CString& strDisplayName,
		const CString& strInternalName);

	// Get command bar according to the internal name
	FW_UICmdBar* GetItem(const CString& strInternalName) const;

	// Get command bar according to the index
	FW_UICmdBar* GetItem(int iIndex) const;

protected:
	FW_UICmdBars(FW_UIManager* pUIManager);
	virtual ~FW_UICmdBars(void);

private:
	CComPtr<IFWUICmdBars> m_spIFWUICmdBars;
	FW_UIManager* m_pUIManager;
	std::vector<FW_UICmdBar*> m_vUICmdBar;
};

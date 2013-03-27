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

class FW_Cmd;
class FW_UICmdBar;
class FW_UICmdBarCtrl;
class XCAD_EXPORT FW_UICmdBarCtrls
{
	friend FW_UICmdBar;

public:
	// 	Get m_spIFWUICmdBarCtrls;
	CComPtr<IFWUICmdBarCtrls> GetInterface();

	// Set m_spIFWUICmdBarCtrls to NULL
	void ResetInterface();

	// Associate a FW_UICmdBarCtrl with a command
	FW_UICmdBarCtrl* Add(FW_Cmd* pCmd);

	// Get count
	size_t GetCount() const;

	// Get command
	FW_Cmd* GetCmd(int iIndex);

protected:
	FW_UICmdBarCtrls(FW_UICmdBar* pUICmdBar);
	virtual ~FW_UICmdBarCtrls(void);

private:
	CComPtr<IFWUICmdBarCtrls> m_spIFWUICmdBarCtrls;
	FW_UICmdBar* m_pUICmdBar;
	std::vector<FW_UICmdBarCtrl*> m_vUICmdBarCtrl;
};

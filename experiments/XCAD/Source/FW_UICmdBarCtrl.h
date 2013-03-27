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

class FW_Cmd;
class FW_UICmdBarCtrls;
class XCAD_EXPORT FW_UICmdBarCtrl
{
	friend FW_UICmdBarCtrls;

public:
	// Get m_spIFWUICmdBarCtrl
	CComPtr<IFWUICmdBarCtrl> GetInterface();

	// Set m_spIFWUICmdBarCtrl to NULL
	void ResetInterface();

protected:
	FW_UICmdBarCtrl(FW_UICmdBarCtrls* pUICmdBarCtrls);
	virtual ~FW_UICmdBarCtrl(void);

	void SetCmd(FW_Cmd* pCmd);
	FW_Cmd* GetCmd() const;

private:
	CComPtr<IFWUICmdBarCtrl> m_spIFWUICmdBarCtrl;
	FW_UICmdBarCtrls* m_pUICmdBarCtrls;
	FW_Cmd* m_pCmd;
};

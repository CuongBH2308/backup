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

class FW_Environments;
class FW_UICmdBar;
class FW_Environment
{
public:
	// Once an environment is new up, it will be added into FW_Environments that will 
	// manage the life cycle of this env
	FW_Environment(FW_Environments* pEnvironment,const CString& strInternalName);
	virtual ~FW_Environment(void);

	// Set the default command bar in this env
	void SetDefaultCmdBar(FW_UICmdBar* pUICmdBar);

	// Get the default command bar in this env
	FW_UICmdBar* GetDefaultCmdBar() const;

	// Add command bar that should be displayed in this env
	void Add(FW_UICmdBar* pUICmdBar);

protected:
	// DefaultCmdBar
	FW_UICmdBar* m_pUICmdBar;

private:
	FW_Environments* m_pEnvironments;
	CString m_strInternalName;
	std::vector<FW_UICmdBar*> m_vUICmdBar;
};

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

class FW_AddIn;
class FW_AddInManager;
class FW_AddIns
{
	friend class FW_AddInManager;

public:
	// Load an addin and add it into m_vAddIn
	FW_AddIn* Add(const CLSID& clsidAddInServer);

protected:
	FW_AddIns(FW_AddInManager* pAddInManager);
	virtual ~FW_AddIns(void);

private:
	FW_AddInManager* m_pAddInManager;
	std::vector<FW_AddIn*> m_vAddIn;
};

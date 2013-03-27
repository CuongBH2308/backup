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

// a little class to parse out our extra cmdline items
class FW_CommandLineInfo : public CCommandLineInfo
{
public:	
	FW_CommandLineInfo() : m_bWinHelp(FALSE), 
		m_lcid(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), SORT_DEFAULT))
	{}

	virtual void ParseParam(LPCTSTR lpszParam, BOOL bFlag, BOOL bLast);

	BOOL m_bWinHelp;
	LCID m_lcid;
};

void SetErrorInfo(UINT uiStringID);
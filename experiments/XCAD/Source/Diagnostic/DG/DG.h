// DG.h : main header file for the DG DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDGApp
// See DG.cpp for the implementation of this class
//

class CDGApp : public CWinApp
{
public:
	CDGApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

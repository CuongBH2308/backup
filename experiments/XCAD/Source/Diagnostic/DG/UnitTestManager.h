#pragma once
#include "DGExports.h"
class CDiagnosticWnd;
class DGEXPORTS_API CUnitTestManager
{
private:
	CUnitTestManager(void);

	~CUnitTestManager(void);
public:
	static CUnitTestManager* GetUnitTestManager();

private:
	CDiagnosticWnd* m_pDGWnd;
};

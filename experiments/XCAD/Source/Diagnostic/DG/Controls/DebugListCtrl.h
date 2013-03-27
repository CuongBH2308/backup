#pragma once


// CDebugListCtrl

class CDebugListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CDebugListCtrl)

public:
	CDebugListCtrl();
	virtual ~CDebugListCtrl();

	void Initialize();

	int InsertItem(CString strTime, DWORD dTickCount, CString strFileName, int nLineNumber, CString strError);



protected:
	DECLARE_MESSAGE_MAP()
};



// AddInSample.h : AddInSample DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������
#include "AddInSample_i.h"


// CAddInSampleApp
// �йش���ʵ�ֵ���Ϣ������� AddInSample.cpp
//

class CAddInSampleApp : public CWinApp
{
public:
	CAddInSampleApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

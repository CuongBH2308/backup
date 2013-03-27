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


#include "stdafx.h"
#include "fw_oleipframewnd.h"

FW_OleIPFrameWnd::FW_OleIPFrameWnd(void)
{
}

FW_OleIPFrameWnd::~FW_OleIPFrameWnd(void)
{
}

IMPLEMENT_DYNCREATE(FW_OleIPFrameWnd, COleIPFrameWnd)

BEGIN_MESSAGE_MAP(FW_OleIPFrameWnd, COleIPFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int FW_OleIPFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndResizeBar.Create(this))
	{
		ASSERT(0);
		return -1;
	}

	m_dropTarget.Register(this);
	return 0;
}

// ��ܽ����� OnCreateControlBars �Ա���
//  ����Ӧ�ó���Ĵ����ϴ�����������pWndFrame �������Ķ�����ܴ��ڣ�
//  ����ʼ�ղ�Ϊ NULL��pWndDoc ���ĵ�����ܴ��ڣ�
//  ������������ SDI Ӧ�ó���ʱΪ NULL��
// ������Ӧ�ó�����Խ� MFC �����������������������е��κ�һ���ϡ�
BOOL FW_OleIPFrameWnd::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// ���ʹ�� pWndDoc���򽫴��Ƴ�
	UNREFERENCED_PARAMETER(pWndDoc);

	//// ���ô˴��ڵ������ߣ��Ա㽫��Ϣ���͵���ȷ��Ӧ�ó���
	//m_wndToolBar.SetOwner(this);

	//// �ڿͻ��Ŀ�ܴ����ϴ���������
	//if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_XCAD1TYPE_SRVR_IP))
	//{
	//	ASSERT(0);
	//	return FALSE;
	//}

	//// TODO: �������Ҫ��������ͣ������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	//pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL FW_OleIPFrameWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	return COleIPFrameWnd::PreCreateWindow(cs);
}

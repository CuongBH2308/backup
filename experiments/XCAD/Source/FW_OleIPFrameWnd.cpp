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

// 框架将调用 OnCreateControlBars 以便在
//  容器应用程序的窗口上创建控制条。pWndFrame 是容器的顶级框架窗口，
//  并且始终不为 NULL。pWndDoc 是文档级框架窗口，
//  并且在容器是 SDI 应用程序时为 NULL。
// 服务器应用程序可以将 MFC 控制条放置在这两个窗口中的任何一个上。
BOOL FW_OleIPFrameWnd::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	// 如果使用 pWndDoc，则将此移除
	UNREFERENCED_PARAMETER(pWndDoc);

	//// 设置此窗口的所有者，以便将消息发送到正确的应用程序
	//m_wndToolBar.SetOwner(this);

	//// 在客户的框架窗口上创建工具栏
	//if (!m_wndToolBar.CreateEx(pWndFrame, TBSTYLE_FLAT,WS_CHILD | WS_VISIBLE | CBRS_TOP
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_XCAD1TYPE_SRVR_IP))
	//{
	//	ASSERT(0);
	//	return FALSE;
	//}

	//// TODO: 如果不需要工具栏可停靠，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//pWndFrame->EnableDocking(CBRS_ALIGN_ANY);
	//pWndFrame->DockControlBar(&m_wndToolBar);

	return TRUE;
}

BOOL FW_OleIPFrameWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	return COleIPFrameWnd::PreCreateWindow(cs);
}

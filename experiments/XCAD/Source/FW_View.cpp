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
#include "fw_view.h"
#include "fw_cmd.h"
#include "fw_cmds.h"
#include "fw_cmdmanager.h"
#include "fw_document.h"
#include "fw_winapp.h"
#include "gr_dlnode.h"
#include "gr_rr.h"
#include "gr_rrmanager.h"
#include "sl_mm.h"

IMPLEMENT_DYNCREATE(FW_View, CView)

FW_View::FW_View()
{
	m_pRR = GR_RRManager::GetRRManager()->GetRR();
}

FW_View::~FW_View()
{
	if(m_pRR)
		DEL_OBJ(m_pRR);
}

BEGIN_MESSAGE_MAP(FW_View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

FW_Document* FW_View::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(FW_Document)));
	return dynamic_cast<FW_Document*>(m_pDocument);
}

// Get root DLNode
GR_DLNode* FW_View::GetDLNode() const
{
	ASSERT(m_pRR);
	return m_pRR->GetDLNode();
}

// Get RR
GR_RR* FW_View::GetRR() const
{
	return m_pRR;
}

// Get ray according to a point in view
// ptInRay is when z=0
bool FW_View::GetRay(const CPoint& pt, MH_CrvRay& ray) const
{
	ASSERT(m_pRR);
	CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
	return m_pRR->GetRay(dc.GetSafeHdc(), pt, ray);
}

// Get point in 3d space according to a point in view
bool FW_View::GetPt(const CPoint& pt, const MH_Plane& plane, MH_Point3& pt3d) const
{
	ASSERT(m_pRR);
	CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
	return m_pRR->GetPt(dc.GetSafeHdc(), pt, plane, pt3d);
}

// Get the model view transformation matrix
MH_Matrix44 FW_View::GetModelView() const
{
	ASSERT(m_pRR);
	CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
	return m_pRR->GetModelView(dc.GetSafeHdc());
}

// Get the projection transformation matrix
MH_Matrix44 FW_View::GetProject() const
{
	ASSERT(m_pRR);
	CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
	return m_pRR->GetProject(dc.GetSafeHdc());
}

// Set the model view transformation matrix
void FW_View::SetModelView(const MH_Matrix44& mtx)
{
	ASSERT(m_pRR);
	CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
	return m_pRR->SetModelView(dc.GetSafeHdc(), mtx);
}

// Set the projection transformation matrix
void FW_View::SetProject(const MH_Matrix44& mtx)
{
	ASSERT(m_pRR);
	CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
	return m_pRR->SetProject(dc.GetSafeHdc(), mtx);
}

bool FW_View::Init()
{
	if(m_pRR)
	{
		CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
		return m_pRR->Init(dc.GetSafeHdc());
	}
	else
		return false;
}

// Uninitialize the setting
// virtual 
bool FW_View::Uninit()
{
	if(m_pRR)
		return m_pRR->Uninit();
	else
		return false;
}

// Render scene
bool FW_View::RenderScene()
{
	if(m_pRR)
	{
		CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
		return m_pRR->RenderScene(dc.GetSafeHdc());
	}
	else
		return false;
}

int FW_View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if(!Init())
		return -1;

	FW_Document* pDoc = GetDocument();
	if(!pDoc || !m_pRR)
		return -1;

	// Initialize data
	pDoc->InitData();

	// Set the root node
	m_pRR->SetDLNode(pDoc->GetDLNode());
	return 0;
}


// FW_View drawing
void FW_View::OnDraw(CDC* pDC)
{
	// Render the scene
	RenderScene();
}

void FW_View::OnDestroy()
{
	Uninit();
	CView::OnDestroy();	
}

BOOL FW_View::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void FW_View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if(m_pRR)
	{
		CClientDC dc(CWnd::FromHandle(GetSafeHwnd()));
		m_pRR->SetViewPort(dc.GetSafeHdc(), cx, cy);
	}
}

// virtual 
BOOL FW_View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CView::OnPreparePrinting(pInfo);
}

// virtual 
void FW_View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CView::OnBeginPrinting(pDC, pInfo);
}

// virtual 
void FW_View::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CView::OnEndPrinting(pDC, pInfo);
}

// virtual 
void FW_View::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CClientDC dc(this);

	HBITMAP hBmp = NULL;
	BITMAPINFO bmi;
	LPVOID pBitmapBits = NULL;
	if(!m_pRR->GetBitmap(dc.GetSafeHdc(), hBmp, bmi, pBitmapBits))
		return;

	CSize szPage;
	szPage.cx = pDC->GetDeviceCaps(HORZRES);
	szPage.cy = pDC->GetDeviceCaps(VERTRES);

	// 2. Calculate the target size according to the image size, and orientation of the paper.
	float fBmiRatio = float(bmi.bmiHeader.biHeight) / bmi.bmiHeader.biWidth;
	CSize szTarget;  
	if (szPage.cx > szPage.cy)	 // Landscape page
	{
		if(fBmiRatio<1)		// Landscape image
		{
			szTarget.cx = szPage.cx;
			szTarget.cy = long(fBmiRatio * szPage.cx);
		}
		else				// Portrait image
		{
			szTarget.cx = long(szPage.cy/fBmiRatio);
			szTarget.cy = szPage.cy;
		}
	}
	else					// Portrait page
	{
		if(fBmiRatio<1)		// Landscape image
		{
			szTarget.cx = szPage.cx;
			szTarget.cy = long(fBmiRatio * szPage.cx);
		}
		else				// Portrait image
		{
			szTarget.cx = long(szPage.cy/fBmiRatio);
			szTarget.cy = szPage.cy;
		}
	}

	CSize szOffset((szPage.cx - szTarget.cx) / 2, (szPage.cy - szTarget.cy) / 2);

	int nRet = ::StretchDIBits(pDC->GetSafeHdc(),
		szOffset.cx, szOffset.cy,
		szTarget.cx, szTarget.cy,
		0, 0,
		bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight,
		pBitmapBits,
		&bmi, DIB_RGB_COLORS, SRCCOPY);
	::DeleteObject(hBmp);
}

void FW_View::OnMouseMove(UINT nFlags, CPoint point) 
{
	CView::OnMouseMove(nFlags, point);

	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnMouseMove(this,nFlags,point);
}

void FW_View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnLButtonDown(nFlags, point);

	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnLButtonDown(this,nFlags,point);
}

void FW_View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnLButtonUp(nFlags, point);

	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnLButtonUp(this,nFlags,point);
}

void FW_View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnRButtonDown(nFlags, point);

	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnRButtonDown(this,nFlags,point);
}

void FW_View::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnRButtonUp(nFlags, point);

	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnRButtonUp(this,nFlags,point);
}

void FW_View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnKeyDown(this, nChar, nRepCnt, nFlags);
}

void FW_View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnKeyUp(nChar, nRepCnt, nFlags);

	FW_Cmd* pCmd = FW_WinApp::GetWinApp()->GetCmdManager()->GetCmds()->GetActiveCmd();
	if(pCmd)
		pCmd->OnKeyUp(this, nChar, nRepCnt, nFlags);
}
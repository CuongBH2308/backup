// MyLineCom.cpp : Implementation of CMyLineCom
#include "stdafx.h"
#include "Model.h"
#include "MyLineCom.h"

//BOOL PtOnLine(long x, long y, long x1, long y1, long x2, long y2);
BOOL PtOnLine(CPoint point, CPoint start, CPoint end);

/////////////////////////////////////////////////////////////////////////////
// CMyLineCom

IMPLEMENT_DYNAMIC(CMyLineCom, CObject)
//IMPLEMENT_DYNAMIC(IMyLineCom, CObject)

/********************************************************************
注意：由于连线不可能在左边comview中，
所以，在本函数中不考虑m_pStartPoint, m_scale_flag，
而在调用之前，要首先设置连线的端点
*********************************************************************/
STDMETHODIMP CMyLineCom::Draw(unsigned long m_pDC, unsigned long m_pStartPoint, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CClientDC * pDC = (CClientDC*) m_pDC;
	GraphInfo * pGraphInfo;

	int i=0;

	//设置
	if ( m_pGraphInfo != NULL )
	{
		pGraphInfo = (GraphInfo*)m_pGraphInfo;
		m_GraphInfo.SetGraphInfo(*pGraphInfo);
	}
	else
		pGraphInfo = &m_GraphInfo;
		
	//设置激活标志
	isActive = m_active_flag;

	double scale = 0;
	m_scale_flag = scale_flag;
	if ( m_scale_flag )
		scale = m_Scale;
	else
		scale = 1;

	//CFont * sysFont = pDC->SelectObject(&(pGraphInfo->font));
	CPen * normalPen = new CPen( pGraphInfo->normal_penStyle, pGraphInfo->normal_linewidth, pGraphInfo->normal_linecolor );	//构造画笔
	CPen * activePen = new CPen( pGraphInfo->active_penStyle, pGraphInfo->active_linewidth, pGraphInfo->active_linecolor );	//构造画笔
	CPen * sysPen;
	CBrush * normalBrush = new CBrush( pGraphInfo->normal_regioncolor );	//普通显示的画刷
	CBrush * activeBrush = new CBrush( pGraphInfo->active_regioncolor );	//激活后的画刷
	CBrush * blackBrush = new CBrush( BLACKBRUSHCOLOR );
	
	CRgn outRgn;
	outRgn.CreateRectRgn(0, 0, 5, 5);
	CRect smallRect;
	
	//判断是否激活了，如果激活，添加outRect
	if ( isActive )	//激活
	{
		sysPen = pDC->SelectObject(activePen);

		//在连线的各个端点分别画一个方框
		pDC->MoveTo(downPoints[0]);
		smallRect.SetRect(downPoints[0].x-3, downPoints[0].y-3, downPoints[0].x+3, downPoints[0].y+3);
		pDC->FillRect(smallRect, blackBrush);
		for (i=1; i<downPointsCount; i++)
		{
			pDC->LineTo(downPoints[i]);
			smallRect.SetRect(downPoints[i].x-3, downPoints[i].y-3, downPoints[i].x+3, downPoints[i].y+3);
			pDC->FillRect(smallRect, blackBrush);
		}
	}
	else	//未激活
	{
		sysPen = pDC->SelectObject(normalPen);
		pDC->MoveTo(downPoints[0]);
		for (i=1; i<downPointsCount; i++)
		{
			pDC->LineTo(downPoints[i]);
		}
	}

		//释放
	//pDC->SelectObject(sysFont);
	pDC->SelectObject(sysPen);
	
	delete(normalPen);
	delete(activePen);
	delete(normalBrush);
	delete(activeBrush);
	delete(blackBrush);

	return S_OK;
}

STDMETHODIMP CMyLineCom::DrawOffset(unsigned long m_pDC, unsigned long m_pOffset, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	Draw(m_pDC, m_pOffset, m_Scale, m_pGraphInfo, scale_flag, m_active_flag);
	return S_OK;
}

STDMETHODIMP CMyLineCom::SetName(unsigned long pName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_name.Format("%s", (char *)pName);
	return S_OK;
}

STDMETHODIMP CMyLineCom::SetID(unsigned long ID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_ID = ID;
	return S_OK;
}


STDMETHODIMP CMyLineCom::GetCLSID(unsigned long pCLSID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	//pCLSID = (unsigned long)(&CLSID_MyLineCom);
	memcpy((void *)pCLSID, &CLSID_MyLineCom, sizeof(CLSID_MyLineCom));
	return S_OK;
}


//new
STDMETHODIMP CMyLineCom::PtInRgn(unsigned long point, unsigned long return_flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	BOOL flag = FALSE;

	for ( int i=0; i<downPointsCount-1; i++ )
	{
		flag = PtOnLine(*(CPoint*)point, downPoints[0], downPoints[1]);
		if ( flag )
		{
			*(BOOL *)return_flag = TRUE;
			return S_OK;
		}
	}

	*(BOOL *)return_flag = FALSE;

	return S_OK;
}


STDMETHODIMP CMyLineCom::GetIID(unsigned long pIID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	//pIID = (unsigned long)(&IID_IMyLineCom);
	memcpy((void *)pIID, &IID_IMyLineCom, sizeof(IID_IMyLineCom));
	return S_OK;
}


STDMETHODIMP CMyLineCom::SetActive(BOOL activeFlag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	isActive = activeFlag;
	return S_OK;
}

STDMETHODIMP CMyLineCom::GetActive(unsigned long pIsActive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	*(BOOL*)pIsActive = isActive;
	return S_OK;
}


STDMETHODIMP CMyLineCom::GetTopLeft(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		
	// TODO: Add your implementation code here
	((CPoint *)pPoint)->x = downPoints[0].x;
	((CPoint *)pPoint)->y = downPoints[0].y;
	
	return S_OK;
}


//new
STDMETHODIMP CMyLineCom::GetRgn(unsigned long pRgn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO: Add your implementation code here
	return S_OK;
}

//new
STDMETHODIMP CMyLineCom::InOtherRgn(unsigned long pRgn, float scale, unsigned long pFlag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*(BOOL *)pFlag = TRUE;

	CRgn * rgn = (CRgn *)pRgn;
	int i = 0;
	CPoint point;
	
	for (i=0; i<downPointsCount; i++)
	{
		point.x = (int)(downPoints[i].x*scale);
		point.y = (int)(downPoints[i].y*scale);
		if ( !rgn->PtInRegion(point) )
			*(BOOL *)pFlag = FALSE;
	}

	return S_OK;
}

//new
STDMETHODIMP CMyLineCom::InOtherRect(unsigned long pRect, float scale, unsigned long pFlag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*(BOOL *)pFlag = TRUE;

	CRect * rect = (CRect *)pRect;
	int i = 0;

	CPoint point;
	
	for (i=0; i<downPointsCount; i++)
	{
		point.x = (int)(downPoints[i].x*scale);
		point.y = (int)(downPoints[i].y*scale);
		if ( !rect->PtInRect(point) )
			*(BOOL *)pFlag = FALSE;
	}

	return S_OK;
}

//new
STDMETHODIMP CMyLineCom::OffsetRgn(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CPoint * point = (CPoint *)pPoint;
	int i = 0;
	for ( i=0; i<downPointsCount; i++ )
		downPoints[i].Offset(*point);
		
	return S_OK;
}

//new
STDMETHODIMP CMyLineCom::GetTopCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint *)pPoint)->x = downPoints[0].x;
	((CPoint *)pPoint)->y = downPoints[0].y;

	return S_OK;
}

STDMETHODIMP CMyLineCom::GetBottomCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint *)pPoint)->x = downPoints[downPointsCount-1].x;
	((CPoint *)pPoint)->y = downPoints[downPointsCount-1].y;

	return S_OK;
}

STDMETHODIMP CMyLineCom::GetLeftCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint*)pPoint)->x = downPoints[0].x;
	((CPoint*)pPoint)->y = downPoints[0].y;

	return S_OK;
}


STDMETHODIMP CMyLineCom::GetRightCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint*)pPoint)->x = downPoints[downPointsCount-1].x;
	((CPoint*)pPoint)->y = downPoints[downPointsCount-1].y;

	return S_OK;
}

/*
STDMETHODIMP CMyLineCom::SetEndPoint(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	downPoints[0].x = ((CPoint *)pPoint)->x;
	downPoints[0].y = ((CPoint *)pPoint)->y;
	ReCalMidPoints();
	return S_OK;
}

STDMETHODIMP CMyLineCom::SetStartPoint(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	downPoints[downPointsCount-1].x = ((CPoint *)pPoint)->x;
	downPoints[downPointsCount-1].y = ((CPoint *)pPoint)->y;
	ReCalMidPoints();
	
	return S_OK;
}
*/

STDMETHODIMP CMyLineCom::SetStartPoint(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	downPoints[0].x = ((CPoint *)pPoint)->x;
	downPoints[0].y = ((CPoint *)pPoint)->y;
	ReCalMidPoints();
	return S_OK;
}

STDMETHODIMP CMyLineCom::SetEndPoint(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	downPoints[downPointsCount-1].x = ((CPoint *)pPoint)->x;
	downPoints[downPointsCount-1].y = ((CPoint *)pPoint)->y;
	ReCalMidPoints();
	
	return S_OK;
}

void CMyLineCom::ReCalMidPoints()
{
	/*
	if ( downPointsCount != 3 )
	{
		//TRACE("端点数不是3");
		return ;
	}

	downPoints[1].x = downPoints[0].x;
	downPoints[1].y = (downPoints[0].y+downPoints[2].y)/2;

	return ;
	*/
}

STDMETHODIMP CMyLineCom::GetName(unsigned long pName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	memcpy((CString *)pName, &m_name, sizeof(CString));	
	return S_OK;
}

STDMETHODIMP CMyLineCom::GetID(unsigned long pID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*(unsigned long *) pID = m_ID;
	return S_OK;
}


STDMETHODIMP CMyLineCom::GetGraphInfo(unsigned long pGraphInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	//*(GraphInfo **)pGraphInfo = &m_GraphInfo;
	((GraphInfo *)pGraphInfo)->font.DeleteObject();
	memcpy((GraphInfo *)pGraphInfo, &m_GraphInfo, sizeof(GraphInfo));
	return S_OK;
}

STDMETHODIMP CMyLineCom::SetGraphInfo(unsigned long pGraphInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_GraphInfo.SetGraphInfo((GraphInfo *)pGraphInfo);
	return S_OK;
}
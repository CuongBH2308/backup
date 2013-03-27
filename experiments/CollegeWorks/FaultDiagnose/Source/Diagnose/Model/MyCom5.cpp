// MyCom5.cpp : Implementation of CMyCom5
#include "stdafx.h"
#include "Model.h"
#include "MyCom5.h"

/////////////////////////////////////////////////////////////////////////////
// CMyCom5

//BOOL PtOnLine(long x, long y, long x1, long y1, long x2, long y2);
BOOL PtOnLine(CPoint point, CPoint start, CPoint end);


IMPLEMENT_DYNAMIC(CMyCom5, CObject)
//IMPLEMENT_DYNAMIC(IMyCom5, CObject)

//new
STDMETHODIMP CMyCom5::Draw(unsigned long m_pDC, unsigned long m_pStartPoint, double m_Scale,
						   unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here

	CClientDC * pDC = (CClientDC*) m_pDC;
	GraphInfo * pGraphInfo;

	//设置
	if ( m_pGraphInfo != NULL )
	{
		pGraphInfo = (GraphInfo*)m_pGraphInfo;
		m_GraphInfo.SetGraphInfo(*pGraphInfo);
	}
	else
		pGraphInfo = &m_GraphInfo;
	
	CPoint * point ;
	CPoint offset;

	double scale = 0;
	m_scale_flag = scale_flag;
	if ( m_scale_flag )
		scale = m_Scale;
	else
		scale = 1;

	if ( m_pStartPoint != NULL )
	{
		point = (CPoint *) m_pStartPoint;
		//计算偏移量
		if ( m_scale_flag )
		{
			offset.x = point->x-upPoints[0].x;
			offset.y = point->y-upPoints[0].y;
		}
		else
		{
			offset.x = point->x-upPoints[0].x-20;
			offset.y = point->y-upPoints[0].y;
		}
	}
	else
	{
		if ( m_scale_flag )
		{
			offset.x = 0 - upPoints[0].x;
			offset.y = 0 - upPoints[0].y;
		}
		else
		{
			offset.x = 0 - upPoints[0].x-20;
			offset.y = 0 - upPoints[0].y;
		}
	}

	OffsetRgn((unsigned long)&offset);

	//设置激活标志
	isActive = m_active_flag;

	CFont * sysFont = pDC->SelectObject(&(pGraphInfo->font));
	CPen * pen = new CPen( pGraphInfo->normal_penStyle, pGraphInfo->normal_linewidth, pGraphInfo->normal_linecolor );	//构造画笔
	CPen * sysPen = pDC->SelectObject(pen);
	CBrush * normalBrush = new CBrush( pGraphInfo->normal_regioncolor );	//普通显示的画刷
	CBrush * activeBrush = new CBrush( pGraphInfo->active_regioncolor );	//激活后的画刷
	CBrush * blackBrush = new CBrush( BLACKBRUSHCOLOR );
	
	CRgn outRgn;
	outRgn.CreateRectRgn(0, 0, 5, 5);
	CRect smallRect;
	
	//判断是否激活了，如果激活，添加outRect
	if ( isActive )	//激活
	{
		if ( m_scale_flag )	//如果是在modelview区域
		{
			//选中后，在外边画一个方框
			outRgn.CombineRgn(&upRgn, &downRgn, RGN_OR);
			outRgn.GetRgnBox(&outRect);
			outRect.InflateRect(5, 5);
			pDC->MoveTo(outRect.left, outRect.top);
			pDC->LineTo(outRect.right, outRect.top);
			pDC->LineTo(outRect.right, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.top);

			//画出upRgn, downRgn, 和连线
			//pDC->FillRgn(&upRgn, normalBrush);
			CRect upRect;
			upRgn.GetRgnBox(upRect);
			pDC->Rectangle(upRect);
			pDC->MoveTo(upPoints[2]);
			pDC->LineTo(upPoints[5]);

			pDC->MoveTo(topPoint);
			pDC->LineTo(bottomPoint);
			pDC->MoveTo(leftPoint);
			pDC->LineTo(rightPoint);
			pDC->FillRgn(&downRgn, normalBrush);

			inRect.SetRect(upPoints[0].x, upPoints[0].y, upPoints[2].x, upPoints[2].y);
			pDC->SetTextColor(pGraphInfo->textcolor);
			pDC->DrawText(m_name, inRect, TEXTOUTFOMAT);	//|DT_END_ELLIPSIS);

			//在矩形的角上，画四个小矩形，5*5象素
			smallRect.SetRect(outRect.left, outRect.top, outRect.left+5, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.top, outRect.right, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.bottom-5, outRect.right, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.left, outRect.bottom-5, outRect.left+5, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
		}
		else	//如果是在comview区域
		{
			//选中后，在外边画一个方框
			downRgn.GetRgnBox(&outRect);
			outRect.InflateRect(5, 5);
			
			pDC->MoveTo(outRect.left, outRect.top);
			pDC->LineTo(outRect.right, outRect.top);
			pDC->LineTo(outRect.right, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.top);
			
			//画出downRgn
			pDC->FillRgn(&downRgn, normalBrush);
			
			//在矩形的角上，画四个小矩形，5*5象素
			smallRect.SetRect(outRect.left, outRect.top, outRect.left+5, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.top, outRect.right, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.bottom-5, outRect.right, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.left, outRect.bottom-5, outRect.left+5, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
		}
	}
	else	//未激活
	{
		if ( m_scale_flag )	//如果是在modelview区域
		{
			//画出upRgn, downRgn, 和连线
			//pDC->FillRgn(&upRgn, normalBrush);
			CRect upRect;
			upRgn.GetRgnBox(upRect);
			pDC->Rectangle(upRect);
			pDC->MoveTo(upPoints[2]);
			pDC->LineTo(upPoints[5]);

			pDC->MoveTo(topPoint);
			pDC->LineTo(bottomPoint);
			pDC->MoveTo(leftPoint);
			pDC->LineTo(rightPoint);
			pDC->FillRgn(&downRgn, normalBrush);

			inRect.SetRect(upPoints[0].x, upPoints[0].y, upPoints[2].x, upPoints[2].y);
			pDC->SetTextColor(pGraphInfo->textcolor);
			pDC->DrawText(m_name, inRect, TEXTOUTFOMAT);	//|DT_END_ELLIPSIS);
		}
		else	//如果是在comview区域
		{
			//画出downRgn
			pDC->FillRgn(&downRgn, normalBrush);
			CRect rr;
			downRgn.GetRgnBox(rr);
		}
	}

		//释放
	pDC->SelectObject(sysFont);
	pDC->SelectObject(sysPen);
	
	delete(pen);
	delete(normalBrush);
	delete(activeBrush);
	delete(blackBrush);

	return S_OK;
}

STDMETHODIMP CMyCom5::DrawOffset(unsigned long m_pDC, unsigned long m_pOffset, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CClientDC * pDC = (CClientDC*) m_pDC;
	GraphInfo * pGraphInfo;

	//设置
	if ( m_pGraphInfo != NULL )
	{
		pGraphInfo = (GraphInfo*)m_pGraphInfo;
		m_GraphInfo.SetGraphInfo(*pGraphInfo);
	}
	else
		pGraphInfo = &m_GraphInfo;
	
		
	//计算偏移量
	if ( m_pOffset != NULL )
	{
		CPoint * offset = (CPoint *)m_pOffset;
		OffsetRgn((unsigned long)offset);
	}

	//设置激活标志
	isActive = m_active_flag;

	double scale = 0;
	m_scale_flag = scale_flag;
	if ( m_scale_flag )
		scale = m_Scale;
	else
		scale = 1;

	CFont * sysFont = pDC->SelectObject(&(pGraphInfo->font));
	CPen * pen = new CPen( pGraphInfo->normal_penStyle, pGraphInfo->normal_linewidth, pGraphInfo->normal_linecolor );	//构造画笔
	CPen * sysPen = pDC->SelectObject(pen);
	CBrush * normalBrush = new CBrush( pGraphInfo->normal_regioncolor );	//普通显示的画刷
	CBrush * activeBrush = new CBrush( pGraphInfo->active_regioncolor );	//激活后的画刷
	CBrush * blackBrush = new CBrush( BLACKBRUSHCOLOR );
	
	CRgn outRgn;
	outRgn.CreateRectRgn(0, 0, 5, 5);
	CRect smallRect;
	
	//判断是否激活了，如果激活，添加outRect
	if ( isActive )	//激活
	{
		if ( m_scale_flag )	//如果是在modelview区域
		{
			//选中后，在外边画一个方框
			outRgn.CombineRgn(&upRgn, &downRgn, RGN_OR);
			outRgn.GetRgnBox(&outRect);
			outRect.InflateRect(5, 5);
			
			pDC->MoveTo(outRect.left, outRect.top);
			pDC->LineTo(outRect.right, outRect.top);
			pDC->LineTo(outRect.right, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.top);

			//画出upRgn, downRgn, 和连线
			//pDC->FillRgn(&upRgn, normalBrush);
			CRect upRect;
			upRgn.GetRgnBox(upRect);
			pDC->Rectangle(upRect);
			pDC->MoveTo(upPoints[2]);
			pDC->LineTo(upPoints[5]);

			pDC->MoveTo(topPoint);
			pDC->LineTo(bottomPoint);
			pDC->MoveTo(leftPoint);
			pDC->LineTo(rightPoint);
			pDC->FillRgn(&downRgn, normalBrush);

			inRect.SetRect(upPoints[0].x, upPoints[0].y, upPoints[2].x, upPoints[2].y);
			pDC->SetTextColor(pGraphInfo->textcolor);
			pDC->DrawText(m_name, inRect, TEXTOUTFOMAT);	//|DT_END_ELLIPSIS);
						
			//在矩形的角上，画四个小矩形，5*5象素
			smallRect.SetRect(outRect.left, outRect.top, outRect.left+5, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.top, outRect.right, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.bottom-5, outRect.right, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.left, outRect.bottom-5, outRect.left+5, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
		}
		else	//如果是在comview区域
		{
			//选中后，在外边画一个方框
			downRgn.GetRgnBox(&outRect);
			outRect.InflateRect(5, 5);

			pDC->MoveTo(outRect.left, outRect.top);
			pDC->LineTo(outRect.right, outRect.top);
			pDC->LineTo(outRect.right, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.bottom);
			pDC->LineTo(outRect.left, outRect.top);
			
			//画出downRgn
			pDC->FillRgn(&downRgn, normalBrush);
			
			//在矩形的角上，画四个小矩形，5*5象素
			smallRect.SetRect(outRect.left, outRect.top, outRect.left+5, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.top, outRect.right, outRect.top+5);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.right-5, outRect.bottom-5, outRect.right, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
			smallRect.SetRect(outRect.left, outRect.bottom-5, outRect.left+5, outRect.bottom);
			pDC->FillRect(smallRect, blackBrush);
		}
	}
	else	//未激活
	{
		if ( m_scale_flag )	//如果是在modelview区域
		{
			//画出upRgn, downRgn, 和连线
			//pDC->FillRgn(&upRgn, normalBrush);
			CRect upRect;
			upRgn.GetRgnBox(upRect);
			pDC->Rectangle(upRect);
			pDC->MoveTo(upPoints[2]);
			pDC->LineTo(upPoints[5]);

			pDC->MoveTo(topPoint);
			pDC->LineTo(bottomPoint);
			pDC->MoveTo(leftPoint);
			pDC->LineTo(rightPoint);
			pDC->FillRgn(&downRgn, normalBrush);

			inRect.SetRect(upPoints[0].x, upPoints[0].y, upPoints[2].x, upPoints[2].y);
			pDC->SetTextColor(pGraphInfo->textcolor);
			pDC->DrawText(m_name, inRect, TEXTOUTFOMAT);	//|DT_END_ELLIPSIS);
		}
		else	//如果是在comview区域
		{
			//画出downRgn
			pDC->FillRgn(&downRgn, normalBrush);
		}
	}

		//释放
	pDC->SelectObject(sysFont);
	pDC->SelectObject(sysPen);
	
	delete(pen);
	delete(normalBrush);
	delete(activeBrush);
	delete(blackBrush);
	
	return S_OK;
}

STDMETHODIMP CMyCom5::SetName(unsigned long pName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_name.Format("%s", (char *)pName);
	return S_OK;
}

STDMETHODIMP CMyCom5::SetID(unsigned long ID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_ID = ID;
	return S_OK;
}

//new
STDMETHODIMP CMyCom5::PtInRgn(unsigned long point, unsigned long return_flag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	BOOL flag = FALSE;
	if ( m_scale_flag )
	{
		flag = upRgn.PtInRegion(*(CPoint*)point);
		if ( flag )
		{
			*(BOOL *)return_flag = TRUE;
			return S_OK;
		}

		flag = PtOnLine(*(CPoint*)point, topPoint, bottomPoint);
		if ( flag )
		{
			*(BOOL *)return_flag = TRUE;
			return S_OK;
		}

		flag = PtOnLine(*(CPoint*)point, leftPoint, rightPoint);
		if ( flag )
		{
			*(BOOL *)return_flag = TRUE;
			return S_OK;
		}
	}

	flag = downRgn.PtInRegion(*(CPoint*)point);
	if ( flag )
		*(BOOL *)return_flag = TRUE;
	else
		*(BOOL *)return_flag = FALSE;

	return S_OK;
}

STDMETHODIMP CMyCom5::GetIID(unsigned long pIID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	//pIID = (unsigned long)(&IID_IMyCom5);
	memcpy((void *)pIID, &IID_IMyCom5, sizeof(IID_IMyCom5));
	return S_OK;
}

STDMETHODIMP CMyCom5::GetCLSID(unsigned long pCLSID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	//pCLSID = (unsigned long)(&CLSID_MyCom5);
	memcpy((void *)pCLSID, &CLSID_MyCom5, sizeof(CLSID_MyCom5));
	return S_OK;
}

//new
STDMETHODIMP CMyCom5::GetTopLeft(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if ( m_scale_flag )
	{
		((CPoint *)pPoint)->x = upPoints[0].x;
		((CPoint *)pPoint)->y = upPoints[0].y;
	}
	else
	{
		((CPoint *)pPoint)->x = downPoints[0].x;
		((CPoint *)pPoint)->y = downPoints[0].y;
	}

	return S_OK;
}

STDMETHODIMP CMyCom5::SetActive(BOOL IsActive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	isActive = IsActive;
	return S_OK;
}

STDMETHODIMP CMyCom5::GetActive(unsigned long pIsActive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*(BOOL*)pIsActive = isActive;
	return S_OK;
}


//new
STDMETHODIMP CMyCom5::GetRgn(unsigned long pRgn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// TODO: Add your implementation code here
	CRgn * rgn = (CRgn *)pRgn;
	if ( m_scale_flag )
		rgn->CombineRgn(&upRgn, &downRgn, RGN_OR);
	else
		rgn->CopyRgn(&downRgn);
	return S_OK;
}

//new
STDMETHODIMP CMyCom5::InOtherRgn(unsigned long pRgn, float scale, unsigned long pFlag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*(BOOL *)pFlag = TRUE;

	CRgn * rgn = (CRgn *)pRgn;
	int i = 0;
	CPoint point;
	
	if ( m_scale_flag )
	{
		for (i=0; i<upPointsCount; i++)
		{
			point.x = (int)(upPoints[i].x*scale);
			point.y = (int)(upPoints[i].y*scale);
			if ( !rgn->PtInRegion(point) )
				*(BOOL *)pFlag = FALSE;
		}

		point.x = (int)(topPoint.x*scale);
		point.y = (int)(topPoint.y*scale);
		if ( !rgn->PtInRegion(point) )
				*(BOOL *)pFlag = FALSE;

		point.x = (int)(bottomPoint.x*scale);
		point.y = (int)(bottomPoint.y*scale);
		if ( !rgn->PtInRegion(point) )
				*(BOOL *)pFlag = FALSE;

		point.x = (int)(leftPoint.x*scale);
		point.y = (int)(leftPoint.y*scale);
		if ( !rgn->PtInRegion(point) )
				*(BOOL *)pFlag = FALSE;

		point.x = (int)(rightPoint.x*scale);
		point.y = (int)(rightPoint.y*scale);
		if ( !rgn->PtInRegion(point) )
				*(BOOL *)pFlag = FALSE;
	}
	
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
STDMETHODIMP CMyCom5::InOtherRect(unsigned long pRect, float scale, unsigned long pFlag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*(BOOL *)pFlag = TRUE;

	CRect * rect = (CRect *)pRect;
	int i = 0;
	CPoint point;
	
	if ( m_scale_flag )
	{
		for (i=0; i<upPointsCount; i++)
		{
			point.x = (int)(upPoints[i].x*scale);
			point.y = (int)(upPoints[i].y*scale);
			if ( !rect->PtInRect(point) )
				*(BOOL *)pFlag = FALSE;
		}

		point.x = (int)(topPoint.x*scale);
		point.y = (int)(topPoint.y*scale);
		if ( !rect->PtInRect(point) )
				*(BOOL *)pFlag = FALSE;

		point.x = (int)(bottomPoint.x*scale);
		point.y = (int)(bottomPoint.y*scale);
		if ( !rect->PtInRect(point) )
				*(BOOL *)pFlag = FALSE;

		point.x = (int)(leftPoint.x*scale);
		point.y = (int)(leftPoint.y*scale);
		if ( !rect->PtInRect(point) )
				*(BOOL *)pFlag = FALSE;

		point.x = (int)(rightPoint.x*scale);
		point.y = (int)(rightPoint.y*scale);
		if ( !rect->PtInRect(point) )
				*(BOOL *)pFlag = FALSE;
	}
	
	for (i=0; i<downPointsCount; i++)
	{
		point.x = (int)(downPoints[i].x*scale);
		point.y = (int)(downPoints[i].y*scale);
		if ( !rect->PtInRect(point) )
			*(BOOL *)pFlag = FALSE;
	}
	
	return S_OK;
}

STDMETHODIMP CMyCom5::OffsetRgn(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	CPoint * point = (CPoint *)pPoint;
	int i = 0;
	for ( i=0; i<upPointsCount; i++ )
		upPoints[i].Offset(*point);
	for ( i=0; i<downPointsCount; i++ )
		downPoints[i].Offset(*point);

	upRgn.OffsetRgn(*point);
	downRgn.OffsetRgn(*point);

	topPoint.Offset(*point);
	bottomPoint.Offset(*point);
	leftPoint.Offset(*point);
	rightPoint.Offset(*point);

	return S_OK;
}

STDMETHODIMP CMyCom5::GetTopCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint *)pPoint)->x = (upPoints[0].x + upPoints[1].x) / 2;
	((CPoint *)pPoint)->y = upPoints[0].y;

	return S_OK;
}

STDMETHODIMP CMyCom5::GetBottomCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint *)pPoint)->x = downPoints[3].x;
	((CPoint *)pPoint)->y = downPoints[3].y;

	return S_OK;
}

STDMETHODIMP CMyCom5::GetLeftCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint*)pPoint)->x = downPoints[4].x;
	((CPoint*)pPoint)->y = (downPoints[4].y+downPoints[5].y)/2;

	return S_OK;
}


STDMETHODIMP CMyCom5::GetRightCenter(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	((CPoint*)pPoint)->x = downPoints[1].x;
	((CPoint*)pPoint)->y = (downPoints[1].y+downPoints[2].y)/2;

	return S_OK;
}


STDMETHODIMP CMyCom5::SetStartPoint(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	if ( m_scale_flag )
	{
		upPoints[0].x = ((CPoint *)pPoint)->x;
		upPoints[0].y = ((CPoint *)pPoint)->y;
	}
	else
	{
		downPoints[0].x = ((CPoint *)pPoint)->x;
		downPoints[0].y = ((CPoint *)pPoint)->y;
	}
	
	return S_OK;
}

STDMETHODIMP CMyCom5::SetEndPoint(unsigned long pPoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	downPoints[downPointsCount-1].x = ((CPoint *)pPoint)->x;
	downPoints[downPointsCount-1].y = ((CPoint *)pPoint)->y;

	return S_OK;
}


STDMETHODIMP CMyCom5::GetName(unsigned long pName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	memcpy((CString *)pName, &m_name, sizeof(CString));	
	return S_OK;
}

STDMETHODIMP CMyCom5::GetID(unsigned long pID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	*(unsigned long *) pID = m_ID;
	return S_OK;
}


STDMETHODIMP CMyCom5::GetGraphInfo(unsigned long pGraphInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	//*(GraphInfo **)pGraphInfo = &m_GraphInfo;
	((GraphInfo *)pGraphInfo)->font.DeleteObject();
	memcpy((GraphInfo *)pGraphInfo, &m_GraphInfo, sizeof(GraphInfo));
	return S_OK;
}

STDMETHODIMP CMyCom5::SetGraphInfo(unsigned long pGraphInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	// TODO: Add your implementation code here
	m_GraphInfo.SetGraphInfo((GraphInfo *)pGraphInfo);
	return S_OK;
}

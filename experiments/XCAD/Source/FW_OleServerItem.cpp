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
#include "fw_oleserveritem.h"
#include "fw_document.h"
#include "gr_rrmanager.h"
#include "gr_rr.h"

IMPLEMENT_DYNAMIC(FW_OleServerItem, COleServerItem)
FW_OleServerItem::FW_OleServerItem(FW_Document* pContainerDoc)
:COleServerItem(pContainerDoc, TRUE)
{
}

FW_OleServerItem::~FW_OleServerItem(void)
{
}

FW_Document* FW_OleServerItem::GetDocument() const
{ 
	return reinterpret_cast<FW_Document*>(COleServerItem::GetDocument()); 
}

void FW_OleServerItem::Serialize(CArchive& ar)
{
	if (!IsLinkedItem())
	{
		FW_Document* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc)
			pDoc->Serialize(ar);
	}
}

BOOL FW_OleServerItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	ASSERT(0);
	return TRUE;
}

BOOL FW_OleServerItem::OnDraw(CDC* pDC, CSize& rSize)
{
	rSize.cx = 200;
	rSize.cy = 200;

	if (!pDC)
		return FALSE;

	FW_Document* pDoc = GetDocument();
	if(!pDoc)
		return FALSE;

	BOOL bOK = FALSE;
	GR_RR* pRR = GR_RRManager::GetRRManager()->GetRR();
	if(pRR)
	{
		// Sets the window origin of the device context
		pDC->SetWindowOrg(0, 0);

		// Sets the x- and y-extents of the window associated with the device context
		pDC->SetWindowExt(rSize);

		// Sets the x- and y-extents of the view-port of the device context
		pDC->SetViewportExt(rSize);  // only affects the m_hAttribDC

		// Call this function to convert logical units into HIMETRIC units
		pDC->LPtoHIMETRIC(&rSize);   // convert pixels to xcad

		HBITMAP hBmp = NULL;
		BITMAPINFO bmi;
		LPVOID pBitmapBits = NULL;
		MH_Matrix44 mtxProject;
		mtxProject[0] = 0.1f;
		mtxProject[5] = 0.2f;
		mtxProject[10] = 0.0f;
		if(pRR->GetBitmap(pDoc->GetDLNode(), rSize, MH_Matrix44(), mtxProject, hBmp, bmi, pBitmapBits))
		{
			int nRet = ::StretchDIBits(pDC->GetSafeHdc(),
				0,0,bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight,
				0,0,bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight,
				pBitmapBits,
				&bmi, DIB_RGB_COLORS, SRCCOPY);

			::DeleteObject(hBmp);
			if(nRet != GDI_ERROR)
				bOK = TRUE;
		}

		// Delete RR
		GR_RRManager::GetRRManager()->DeleteRR(pRR);
	}

	return bOK;
}
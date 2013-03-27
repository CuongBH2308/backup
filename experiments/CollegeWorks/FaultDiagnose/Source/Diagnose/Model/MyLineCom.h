// MyLineCom.h : Declaration of the CMyLineCom

#ifndef __MYLINECOM_H_
#define __MYLINECOM_H_

#include "resource.h"       // main symbols
#include "basecom.h"
/////////////////////////////////////////////////////////////////////////////
// CMyLineCom
class ATL_NO_VTABLE CMyLineCom : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyLineCom, &CLSID_MyLineCom>,
	public IDispatchImpl<IMyLineCom, &IID_IMyLineCom, &LIBID_MODELLib>,
	public CBaseCom
{
	DECLARE_DYNAMIC(CMyLineCom)
	//DECLARE_DYNAMIC(IMyLineCom)
	
public:
	CMyLineCom()//:m_GraphInfo()
	{
		m_ID = 0;
		m_name = _T("LINE_COM");
		isActive = FALSE;
		m_scale_flag = TRUE;
		m_GraphInfo.normal_linecolor = m_GraphInfo.active_linecolor = RGB(9, 5, 150);//RGB(71, 151, 73);

		downPointsCount = 2;
		downPoints = new CPoint[2];
		downPoints[0].x = 0, downPoints[0].y = 0;
		downPoints[1].x = 10, downPoints[1].y = 10;
	}

	~CMyLineCom()
	{
		delete []downPoints;
	}

	void ReCalMidPoints();

DECLARE_REGISTRY_RESOURCEID(IDR_MYLINECOM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyLineCom)
	COM_INTERFACE_ENTRY(IMyLineCom)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


// IMyLineCom
public:
	STDMETHOD(Draw)(unsigned long m_pDC, unsigned long m_pStartPoint, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag);
	STDMETHOD(DrawOffset)(unsigned long m_pDC, unsigned long m_pOffset, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag);
	STDMETHOD(SetName)(unsigned long pName);
	STDMETHOD(SetID)(unsigned long ID);
	STDMETHOD(PtInRgn)(unsigned long point, unsigned long return_flag);	//判断点是否在rgn内
	STDMETHOD(GetIID)(unsigned long pIID);
	STDMETHOD(GetCLSID)(unsigned long pCLSID);
	STDMETHOD(GetTopLeft)(unsigned long pPoint);						//取得bottomRgn左上角的坐标
	STDMETHOD(SetActive)(BOOL IsActive);	
	STDMETHOD(GetActive)(unsigned long pIsActive);
	STDMETHOD(GetRgn)(unsigned long pRgn);								//取得bottomRgn
	STDMETHOD(InOtherRgn)(unsigned long pRgn, float scale, unsigned long pFlag);
	STDMETHOD(InOtherRect)(unsigned long pRect, float scale, unsigned long pFlag);
	STDMETHOD(OffsetRgn)(unsigned long pPoint);
	STDMETHOD(GetTopCenter)(unsigned long pPoint);
	STDMETHOD(GetBottomCenter)(unsigned long pPoint);
	STDMETHOD(GetLeftCenter)(unsigned long pPoint);
	STDMETHOD(GetRightCenter)(unsigned long pPoint);
	STDMETHOD(SetStartPoint)(unsigned long pPoint);
	STDMETHOD(SetEndPoint)(unsigned long pPoint);
	STDMETHOD(GetName)(unsigned long pName);
	STDMETHOD(GetID)(unsigned long pID);	
	STDMETHOD(GetGraphInfo)(unsigned long pGraphInfo);
	STDMETHOD(SetGraphInfo)(unsigned long pGraphInfo);
};

#endif //__MYLINECOM_H_

// MyCom12.h : Declaration of the CMyCom12

#ifndef __MYCOM12_H_
#define __MYCOM12_H_

#include "resource.h"       // main symbols
#include "basecom.h"

/////////////////////////////////////////////////////////////////////////////
// CMyCom12
class ATL_NO_VTABLE CMyCom12 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyCom12, &CLSID_MyCom12>,
	public IDispatchImpl<IMyCom12, &IID_IMyCom12, &LIBID_MODELLib>,
	public CBaseCom
{
	DECLARE_DYNAMIC(CMyCom12)
public:
	CMyCom12()//:m_GraphInfo()
	{
		isActive = FALSE;
		m_name = _T("COM_12");
		m_ID = 0;
		m_scale_flag = TRUE;
		m_GraphInfo.normal_regioncolor = m_GraphInfo.active_regioncolor = RGB(0, 0, 221);

		//上面的半个区域
		upPointsCount = 6;
		upPoints = new CPoint[upPointsCount];
		upPoints[0].x = 0, upPoints[0].y = 0;
		upPoints[1].x = 90, upPoints[1].y = 0;
		upPoints[2].x = 90, upPoints[2].y = 15;
		upPoints[3].x = 90, upPoints[3].y = 25;
		upPoints[4].x = 0, upPoints[4].y = 25;
		upPoints[5].x = 0, upPoints[5].y = 15;
		upRgn.CreatePolygonRgn(upPoints, upPointsCount, ALTERNATE);

		//下面的半个区域
		downPointsCount = 4;
		downPoints = new CPoint[downPointsCount];
		downPoints[0].x = 45, downPoints[0].y = 30;
		downPoints[1].x = 70, downPoints[1].y = 55;
		downPoints[2].x = 45, downPoints[2].y = 80;
		downPoints[3].x = 20, downPoints[3].y = 55;
		downRgn.CreatePolygonRgn(downPoints, downPointsCount, ALTERNATE);

		//设置短线的两个端点
		topPoint.x = 45, topPoint.y = 25;
		bottomPoint.x = 45, bottomPoint.y = 30;
		leftPoint.x = 42, leftPoint.y = 27;
		rightPoint.x = 48, rightPoint.y = 27;
	}
	~CMyCom12()
	{
		downRgn.DeleteObject();
		upRgn.DeleteObject();
		delete []upPoints;
		delete []downPoints;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYCOM12)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyCom12)
	COM_INTERFACE_ENTRY(IMyCom12)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


// IMyCom12
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

#endif //__MYCOM12_H_

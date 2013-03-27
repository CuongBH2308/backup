#ifndef _BASECOM_H
#define _BASECOM_H

#include "stdafx.h"

#define BLACKBRUSHCOLOR RGB(150, 150, 150)
#define TEXTOUTFOMAT DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS

class CBaseCom : public IUnknown,
				 public CObject
{
	DECLARE_DYNAMIC(CBaseCom)
	//DECLARE_DYNAMIC(IBaseCom)

public:
	unsigned long m_ID;
	CString m_name;
	CPoint * upPoints;		//ʹ��ʱ��Ҫ�����еĵ㶼����Ϊ�����m_points[0]�����λ�ã������е㰴��˳ʱ�뷽��
	CPoint * downPoints;	//ʹ��ʱ��Ҫ�����еĵ㶼����Ϊ�����m_points[0]�����λ�ã������е㰴��˳ʱ�뷽��
	CRgn upRgn;
	CRgn downRgn;
	unsigned char upPointsCount;
	unsigned char downPointsCount;
	CPoint topPoint;		//com�ڲ��Ķ���,�ֱ�Ϊ��������Rgn���е�
	CPoint bottomPoint;
	CPoint leftPoint;
	CPoint rightPoint;
	BOOL isActive;
	GraphInfo m_GraphInfo;
	CRect outRect;
	CRect inRect;
	BOOL m_scale_flag;

public:
	STDMETHOD(Draw)(unsigned long m_pDC, unsigned long m_pStartPoint, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag) = 0;
	STDMETHOD(DrawOffset)(unsigned long m_pDC, unsigned long m_pOffset, double m_Scale, unsigned long m_pGraphInfo, BOOL scale_flag, BOOL m_active_flag) = 0;
	STDMETHOD(SetName)(unsigned long pName) = 0;
	STDMETHOD(SetID)(unsigned long ID) = 0;
	STDMETHOD(PtInRgn)(unsigned long point, unsigned long return_flag) = 0;	//�жϵ��Ƿ���rgn��
	STDMETHOD(GetIID)(unsigned long pIID) = 0;
	STDMETHOD(GetCLSID)(unsigned long pCLSID) = 0;
	STDMETHOD(GetTopLeft)(unsigned long pPoint) = 0;						//ȡ��bottomRgn���Ͻǵ�����
	STDMETHOD(SetActive)(BOOL IsActive) = 0;	
	STDMETHOD(GetActive)(unsigned long pIsActive) = 0;
	STDMETHOD(GetRgn)(unsigned long pRgn) = 0;
	STDMETHOD(InOtherRgn)(unsigned long pRgn, float scale, unsigned long pFlag) = 0;
	STDMETHOD(InOtherRect)(unsigned long pRect, float scale, unsigned long pFlag) = 0;
	STDMETHOD(OffsetRgn)(unsigned long pPoint) = 0;
	STDMETHOD(GetTopCenter)(unsigned long pPoint) = 0;
	STDMETHOD(GetBottomCenter)(unsigned long pPoint) = 0;
	STDMETHOD(GetLeftCenter)(unsigned long pPoint) = 0;
	STDMETHOD(GetRightCenter)(unsigned long pPoint) = 0;
	STDMETHOD(SetStartPoint)(unsigned long pPoint) = 0;
	STDMETHOD(SetEndPoint)(unsigned long pPoint) = 0;
	STDMETHOD(GetName)(unsigned long pName) = 0;
	STDMETHOD(GetID)(unsigned long pID) = 0;
	STDMETHOD(GetGraphInfo)(unsigned long pGraphInfo) = 0;	//pGraphInfo���Ѿ���ʼ����ָ��
	STDMETHOD(SetGraphInfo)(unsigned long pGraphInfo) = 0;
};

#endif;

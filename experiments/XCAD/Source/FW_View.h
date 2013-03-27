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


#pragma once
#include "mh_matrix44.h"

class FW_Document;
class GR_DLNode;
class GR_RR;
class MH_CrvRay;
class MH_Plane;
class MH_Point3;
class FW_View : public CView
{
	DECLARE_DYNCREATE(FW_View)
public:
	FW_View();
	virtual ~FW_View();

	// Get document
	FW_Document* GetDocument() const;

	// Get root DLNode
	GR_DLNode*	GetDLNode() const;

	// Get RR
	GR_RR* GetRR() const;

	// Get ray according to a point in view
	// ptInRay is when z=0
	bool GetRay(const CPoint& pt, MH_CrvRay& ray) const;

	// Get point in 3d space according to a point in view
	bool GetPt(const CPoint& pt, const MH_Plane& plane, MH_Point3& pt3d) const;

	// Get the model view transformation matrix
	MH_Matrix44 GetModelView() const;

	// Get the projection transformation matrix
	MH_Matrix44 GetProject() const;

	// Set the model view transformation matrix
	void SetModelView(const MH_Matrix44& mtx);

	// Set the projection transformation matrix
	void SetProject(const MH_Matrix44& mtx);

protected:

	// Initialize the setting
	virtual bool Init();

	// Uninitialize the setting
	virtual bool Uninit();

	// Render the scene, including the coordinate plane,
	// and the objects in the scene
	virtual bool RenderScene();

	// Overridden to draw this view
	virtual void OnDraw(CDC* pDC);

	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()

private:
	GR_RR* m_pRR;
};

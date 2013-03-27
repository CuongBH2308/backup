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

class GR_DLNode;
class MH_CrvRay;
class MH_Plane;
class MH_Point3;
class GR_RR
{
public:
	GR_RR(void);
	virtual ~GR_RR(void);

	// Set root DLNode
	void SetDLNode(GR_DLNode* pDLNode);

	// Get root DLNode
	GR_DLNode* GetDLNode() const;

	// Initialize the setting
	virtual bool Init(HDC hDC) = 0;

	// Uninitialize the setting
	virtual bool Uninit() = 0;

	// Render the scene
	virtual bool RenderScene(HDC hDC) = 0;

	// Get ray according to a point in view
	// ptInRay is when z=0
	virtual	bool GetRay(HDC hDC, const CPoint& pt, MH_CrvRay& ray) const = 0;

	// Get point in 3d space according to a point in view
	virtual	bool GetPt(HDC hDC, const CPoint& pt, const MH_Plane& plane, MH_Point3& pt3d) const = 0;

	// Get point in 3d space according to a point in view
	virtual	bool GetPt(HDC hDC, const CPoint& pt, MH_Point3& pt3d) const = 0;

	// Get point in 3d space according to a point in view
	virtual	bool GetPt(HDC hDC, float fWinX, float fWinY, float fWinZ, MH_Point3& pt) const = 0;

	// Get point in view according to a point in 3d space  
	virtual	bool GetPt(HDC hDC, const MH_Point3& pt, float& fWinX, float& fWinY, float& fWinZ) const = 0;

	// Set the model view transformation matrix
	virtual void SetModelView(HDC hDC, const MH_Matrix44& mtx) = 0;

	// Get the model view transformation matrix
	virtual MH_Matrix44 GetModelView(HDC hDC) const = 0;

	// Set the projection transformation matrix
	virtual void SetProject(HDC hDC, const MH_Matrix44& mtx) = 0;

	// Get the projection transformation matrix
	virtual MH_Matrix44 GetProject(HDC hDC) const = 0;

	// Resize the window
	virtual bool SetViewPort(HDC hDC, int cx, int cy) = 0;

	// Get view port
	virtual bool GetViewPort(HDC hDC, int& cx, int& cy) = 0;

	// Save the scene as bitmap
	virtual bool GetBitmap(HDC hDC, HBITMAP& hDib, BITMAPINFO& bmi, LPVOID&	pBitmapBits) = 0;

	// Save the scene as bitmap
	virtual bool GetBitmap(GR_DLNode* pDLNode, const CSize& rViewPort, const MH_Matrix44& mtxModelView, const MH_Matrix44& mtxProject,
		HBITMAP& hDib, BITMAPINFO& bmi, LPVOID& pBitmapBits) = 0;

	// Print the scene to hDCPrinter
	virtual bool Print(HDC hDC, HDC hDCPrinter,  
		int iXDest,						// x-coord of destination upper-left corner
		int iYDest,						// y-coord of destination upper-left corner
		int iDestWidth,					// width of destination rectangle
		int iDestHeight) = 0;			// height of destination rectangle
protected:
	GR_DLNode*	m_pDLNode;
};

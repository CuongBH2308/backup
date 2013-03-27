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
#include "gr_rr.h"

class GR_DLNode;
class GR_RROpenGL : public GR_RR
{
public:
	GR_RROpenGL(void);
	virtual ~GR_RROpenGL(void);

	// Initialize the setting
	virtual bool Init(HDC hDC);

	// Uninitialize the setting
	virtual bool Uninit();

	// Render the scene
	virtual bool RenderScene(HDC hDC);

	// Get ray according to a point in view
	virtual	bool GetRay(HDC hDC, const CPoint& pt, MH_CrvRay& ray) const;

	// Get point in 3d space according to a point in view
	virtual	bool GetPt(HDC hDC, const CPoint& pt, const MH_Plane& plane, MH_Point3& pt3d) const;

	// Get point in 3d space according to a point in view
	virtual	bool GetPt(HDC hDC, const CPoint& pt, MH_Point3& pt3d) const;

	// Get point in 3d space according to a point in view
	virtual	bool GetPt(HDC hDC, float fWinX, float fWinY, float fWinZ, MH_Point3& pt) const;

	// Get point in view according to a point in 3d space  
	virtual	bool GetPt(HDC hDC, const MH_Point3& pt, float& fWinX, float& fWinY, float& fWinZ) const;

	// Set the model view transformation matrix
	virtual void SetModelView(HDC hDC, const MH_Matrix44& mtx);

	// Get the model view transformation matrix
	virtual MH_Matrix44 GetModelView(HDC hDC) const;

	// Set the projection transformation matrix
	virtual void SetProject(HDC hDC, const MH_Matrix44& mtx);

	// Get the projection transformation matrix
	virtual MH_Matrix44 GetProject(HDC hDC) const;

	// Resize the window
	virtual bool SetViewPort(HDC hDC, int cx, int cy);

	// Get view port
	virtual bool GetViewPort(HDC hDC, int& cx, int& cy);

	// Save the scene as bitmap
	virtual bool GetBitmap(HDC hDC, HBITMAP& hDib, BITMAPINFO& bmi, LPVOID&	pBitmapBits);

	// Save the scene as bitmap
	virtual bool GetBitmap(GR_DLNode* pDLNode, const CSize& rViewPort, const MH_Matrix44& mtxModelView, const MH_Matrix44& mtxProject,
		HBITMAP& hDib, BITMAPINFO& bmi, LPVOID& pBitmapBits);

    // Print the scene to hDCPrinter
	virtual bool Print(HDC hDC, HDC hDCPrinter,  
		int iXDest,						// x-coord of destination upper-left corner
		int iYDest,						// y-coord of destination upper-left corner
		int iDestWidth,					// width of destination rectangle
		int iDestHeight);				// height of destination rectangle

private:
	HGLRC					m_hRC;
	PIXELFORMATDESCRIPTOR	m_pfd;
};

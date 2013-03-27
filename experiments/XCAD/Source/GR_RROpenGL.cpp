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
#include "gr_rropengl.h"
#include <gl\gl.h>
#include <gl\glu.h>
#include "gr_color.h"
#include "gr_dlnode.h"
#include "mh_crvray.h"
#include "mh_point3.h"

#define HALF_HEIGHT		5.0f
#define CLR_BACKGROUND	GR_Color(.6f, 0.6f, 0.6f, 1.0f)

GR_RROpenGL::GR_RROpenGL()
:m_hRC(NULL)
{
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,										// Version Number
			PFD_DRAW_TO_WINDOW |					// Format Must Support Window
			PFD_SUPPORT_OPENGL |					// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,						// Must Support Double Buffering
			PFD_TYPE_RGBA,							// Request An RGBA Format
			24,										// Select Our Color Depth
			0, 0, 0, 0, 0, 0,						// Color Bits Ignored
			0,										// No Alpha Buffer
			0,										// Shift Bit Ignored
			0,										// No Accumulation Buffer
			0, 0, 0, 0,								// Accumulation Bits Ignored
			16,										// 16Bit Z-Buffer (Depth Buffer)  
			0,										// No Stencil Buffer
			0,										// No Auxiliary Buffer
			PFD_MAIN_PLANE,							// Main Drawing Layer
			0,										// Reserved
			0, 0, 0									// Layer Masks Ignored
	};
	memcpy(&m_pfd, &pfd, sizeof(PIXELFORMATDESCRIPTOR));
}

GR_RROpenGL::~GR_RROpenGL(void)
{
	Uninit();
}

// Initialize the setting
// virtual
bool GR_RROpenGL::Init(HDC hDC)
{
	ASSERT(hDC);
	ASSERT(!m_hRC);

	int iPixelFormat = ::ChoosePixelFormat(hDC, &m_pfd);
	if(!iPixelFormat)
		return false;

	if(!::SetPixelFormat(hDC, iPixelFormat, &m_pfd))
		return false;

	// Update the PIXELFORMATDESCRIPTOR once the device context has been modified.
	::DescribePixelFormat(hDC, iPixelFormat, sizeof(m_pfd), &m_pfd);

	if(m_pfd.dwFlags & PFD_NEED_PALETTE)
	{
		ASSERT(0);
		//SetupPalette();
	}

	m_hRC = ::wglCreateContext(hDC); 
	if(m_hRC == NULL)
		return false;

	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	::glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	::glClearColor(CLR_BACKGROUND.GetRed(),
		CLR_BACKGROUND.GetGreen(),
		CLR_BACKGROUND.GetBlue(),
		CLR_BACKGROUND.GetAlpha());						// Background
	::glClearDepth(1.0f);								// Depth Buffer Setup
	::glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	::glDepthFunc(GL_LEQUAL);							// The Type Of Depth Testing To Do
	::glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Really Nice Perspective Calculations

	return true;
}

// Uninitialize the setting
// virtual 
bool GR_RROpenGL::Uninit()
{
	// If we have A Rendering Context
	if (m_hRC)
	{
		// Try to release the DC and RC contexts
		BOOL bOK = ::wglMakeCurrent(NULL, NULL);
		//ASSERT(bOK);
		//if(!bOK)
		//	return false;

		// Try to delete the DC
		bOK = ::wglDeleteContext(m_hRC);
		ASSERT(bOK);
		if(!bOK)
			return false;

		// Set RC To NULL
		m_hRC = NULL;
	}

	return true;
}

// Render the scene
// virtual
bool GR_RROpenGL::RenderScene(HDC hDC)
{
	if(!m_pDLNode)
		return false;

	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	::glMatrixMode(GL_MODELVIEW_MATRIX);
	//////////////////////////////////////////////////////////////////////////
	// Start to render
	//////////////////////////////////////////////////////////////////////////
	// Clear color and depth buffer
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render all nodes from the root node
	m_pDLNode->Render();

	// Forces execution of OpenGL functions in finite time
	::glFlush();

	// Exchanges the front and back buffers if the current pixel format for the window referenced 
	// by the specified device context includes a back buffer
	::SwapBuffers(hDC);

	return true;
}

// Get ray according to a point in view
// virtual
bool GR_RROpenGL::GetRay(HDC hDC, const CPoint& pt, MH_CrvRay& ray) const
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	GLdouble	modelMatrix[16];
	GLdouble	projectMatrix[16];
	GLint		viewport[4];

	::glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	::glGetDoublev(GL_PROJECTION_MATRIX, projectMatrix);
	::glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble x[2],y[2],z[2];
	::gluUnProject(pt.x, viewport[3]-pt.y, 0.0, modelMatrix, projectMatrix, viewport, 
		&x[0], &y[0], &z[0]);
	::gluUnProject(pt.x, viewport[3]-pt.y, 1.0, modelMatrix, projectMatrix, viewport, 
		&x[1], &y[1], &z[1]);

	ray.Set(MH_Point3(float(x[0]), float(y[0]), float(z[0])), MH_Vector3(float(x[1]-x[0]), float(y[1]-y[0]), float(z[1]-z[0])));

	return true;
}

// Get point in 3d space according to a point in view
// virtual	
bool GR_RROpenGL::GetPt(HDC hDC, const CPoint& pt, const MH_Plane& plane, MH_Point3& pt3d) const
{
	MH_CrvRay ray;
	bool bOK = GetRay(hDC, pt, ray);
	ASSERT(bOK);
	if(bOK)
		bOK = ray.CrossPoint(plane, &pt3d);

    return bOK;
}

// Get point in 3d space according to a point in view
// virtual	
bool GR_RROpenGL::GetPt(HDC hDC, const CPoint& pt, MH_Point3& pt3d) const
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	GLdouble	modelMatrix[16];
	GLdouble	projectMatrix[16];
	GLint		viewport[4];

	::glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	::glGetDoublev(GL_PROJECTION_MATRIX, projectMatrix);
	::glGetIntegerv(GL_VIEWPORT, viewport);

	float winX	=(float)pt.x;
	float winY	=(float)viewport[3]-(float)pt.y;
	float winZ	= 0.0f;
	::glReadPixels( pt.x,
		viewport[3] - pt.y,
		1,1,				//Read one pixel
		GL_DEPTH_COMPONENT,	//Depth Info
		GL_FLOAT,			//Float
		&winZ);				//Depth

	GLdouble x,y,z;
	::gluUnProject((GLdouble)winX,(GLdouble)winY,(GLdouble)winZ,modelMatrix,projectMatrix,viewport,
		&x, &y, &z);
	pt3d.Set(float(x), float(y), float(z));

	return true;
}

// Get point in 3d space according to a point in view
// virtual	
bool GR_RROpenGL::GetPt(HDC hDC, float fWinX, float fWinY, float fWinZ, MH_Point3& pt) const
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	GLdouble	modelMatrix[16];
	GLdouble	projectMatrix[16];
	GLint		viewport[4];

	::glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	::glGetDoublev(GL_PROJECTION_MATRIX, projectMatrix);
	::glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble x,y,z;
	int ok = ::gluUnProject(fWinX, fWinY, fWinZ, modelMatrix, projectMatrix, viewport, 
		&x, &y, &z);

	pt.Set(float(x), float(y), float(z));
	return (ok == GL_TRUE) ? true : false;
}

// Get point in view according to a point in 3d space  
// virtual	
bool GR_RROpenGL::GetPt(HDC hDC, const MH_Point3& pt, float& fWinX, float& fWinY, float& fWinZ) const
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	GLdouble	modelMatrix[16];
	GLdouble	projectMatrix[16];
	GLint		viewport[4];

	::glGetDoublev(GL_MODELVIEW_MATRIX,modelMatrix);
	::glGetDoublev(GL_PROJECTION_MATRIX, projectMatrix);
	::glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble x,y,z;
	int ok = ::gluProject(pt.m_f[0], pt.m_f[1], pt.m_f[2], 
		modelMatrix, projectMatrix, viewport, 
		&x, &y, &z);

	fWinX = float(x);
	fWinY = float(y);
	fWinZ = float(z);

	return (ok == GL_TRUE) ? true : false;
}

// Get the model view transformation matrix
// virtual 
MH_Matrix44 GR_RROpenGL::GetModelView(HDC hDC) const
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		ASSERT(0);

	MH_Matrix44 mtx;
	::glGetFloatv(GL_MODELVIEW_MATRIX, &mtx[0]);
	return mtx.Transpose();
}

// Get the projection transformation matrix
// virtual 
MH_Matrix44 GR_RROpenGL::GetProject(HDC hDC) const
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		ASSERT(0);

	MH_Matrix44 mtx;
	::glGetFloatv(GL_PROJECTION_MATRIX, &mtx[0]);
	return mtx.Transpose();
}

// Set the model view transformation matrix
// virtual
void GR_RROpenGL::SetModelView(HDC hDC, const MH_Matrix44& mtx)
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		return;

	// Keep GL_MATRIX_MODE
	::glPushAttrib(GL_TRANSFORM_BIT);

	// Select Model-view Matrix as the current matrix
	::glMatrixMode(GL_MODELVIEW);	

	// Set model view Matrix
	::glLoadMatrixf(&mtx.Transpose()[0]);

	// Restore GL_MATRIX_MODE
	::glPopAttrib();
}

// Set the projection transformation matrix
// virtual 
void GR_RROpenGL::SetProject(HDC hDC, const MH_Matrix44& mtx)
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		return;

	// Keep GL_MATRIX_MODE
	::glPushAttrib(GL_TRANSFORM_BIT);

	// Select Model-view Matrix as the current matrix
	::glMatrixMode(GL_PROJECTION);	

	// Set model view Matrix
	::glLoadMatrixf(&mtx.Transpose()[0]);

	// Restore GL_MATRIX_MODE
	::glPopAttrib();
}

// Resize the window
// virtual 
bool GR_RROpenGL::SetViewPort(HDC hDC, int cx, int cy)
{
	if(cy == 0)
		cy=1;

	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	// Set the viewport.
	::glViewport(0, 0, cx, cy);

	//////////////////////////////////////////////////////////////////////////
	// Projection Matrix
	// void glOrtho(left,right,bottom,top,zNear,zFar);
	//////////////////////////////////////////////////////////////////////////
	// Get the Ortho's Information
	float fLeft		= -float(cx)/float(cy)*HALF_HEIGHT;
	float fRight	=  float(cx)/float(cy)*HALF_HEIGHT;
	float fBottom	= -HALF_HEIGHT;
	float fTop		=  HALF_HEIGHT;
	float fNear		= -100;
	float fFar		=  100;

	MH_Matrix44 mtxProjection;
	mtxProjection[0]	= 2.0f/(fRight-fLeft);
	mtxProjection[3]	= -(fRight+fLeft)/(fRight-fLeft);
	mtxProjection[5]	= 2.0f/(fTop-fBottom);
	mtxProjection[7]	= -(fTop+fBottom)/(fTop-fBottom);
	mtxProjection[10]	= -2.0f/(fFar-fNear);
	mtxProjection[11]	= -(fFar+fNear)/(fFar-fNear);

	SetProject(hDC, mtxProjection);
	return true;
}

// Get view port
// virtual 
bool GR_RROpenGL::GetViewPort(HDC hDC, int& cx, int& cy)
{
	if(!::wglMakeCurrent(hDC, m_hRC))
		return false;

	GLint sz[4];
	::glGetIntegerv(GL_VIEWPORT, sz);
	cx = sz[2];
	cy = sz[3];
	return true;
}

// Save the scene as bitmap
// virtual 
bool GR_RROpenGL::GetBitmap(GR_DLNode* pDLNode, const CSize& rViewPort, const MH_Matrix44& mtxModelView, const MH_Matrix44& mtxProject,
					   HBITMAP& hDib, BITMAPINFO& bmi, LPVOID& pBitmapBits)
{
	hDib = NULL;
	GR_RROpenGL* pRR = new GR_RROpenGL();
	if(pRR)
	{
		static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
				1,										// Version Number
				PFD_DRAW_TO_BITMAP | 
				PFD_SUPPORT_OPENGL | 
				PFD_STEREO_DONTCARE,
				PFD_TYPE_RGBA,							// Request An RGBA Format
				24,										// Select Our Color Depth
				0, 0, 0, 0, 0, 0,						// Color Bits Ignored
				0,										// No Alpha Buffer
				0,										// Shift Bit Ignored
				0,										// No Accumulation Buffer
				0, 0, 0, 0,								// Accumulation Bits Ignored
				16,										// 16Bit Z-Buffer (Depth Buffer)  
				0,										// No Stencil Buffer
				0,										// No Auxiliary Buffer
				PFD_MAIN_PLANE,							// Main Drawing Layer
				0,										// Reserved
				0, 0, 0									// Layer Masks Ignored
		};
		memcpy(&pRR->m_pfd, &pfd, sizeof(PIXELFORMATDESCRIPTOR));

		pRR->m_pfd.dwFlags = PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_STEREO_DONTCARE;
		pRR->m_pfd.cColorBits = 24;
		pRR->m_pfd.cRedBits = 8;
		pRR->m_pfd.cRedShift = 16;
		pRR->m_pfd.cGreenBits = 8;
		pRR->m_pfd.cGreenShift = 8;
		pRR->m_pfd.cBlueBits = 8;
		pRR->m_pfd.cBlueShift = 0;
		pRR->m_pfd.cAlphaBits = 0;
		pRR->m_pfd.cAlphaShift = 0;
		pRR->m_pfd.cAccumBits = 64;
		pRR->m_pfd.cAccumRedBits = 16;
		pRR->m_pfd.cAccumGreenBits = 16;
		pRR->m_pfd.cAccumBlueBits = 16;
		pRR->m_pfd.cAccumAlphaBits = 0;
		pRR->m_pfd.cDepthBits = 32;
		pRR->m_pfd.cStencilBits = 8;
		pRR->m_pfd.cAuxBuffers = 0;
		pRR->m_pfd.iLayerType = PFD_MAIN_PLANE;
		pRR->m_pfd.bReserved = 0;
		pRR->m_pfd.dwLayerMask = 0;
		pRR->m_pfd.dwVisibleMask = 0;
		pRR->m_pfd.dwDamageMask = 0;

		// Set DLNode
		pRR->SetDLNode(pDLNode);

		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth		= rViewPort.cx;
		bmi.bmiHeader.biHeight		= rViewPort.cy;
		bmi.bmiHeader.biPlanes		= 1;
		bmi.bmiHeader.biBitCount	= 24;
		bmi.bmiHeader.biCompression	= BI_RGB;
		bmi.bmiHeader.biSizeImage	= bmi.bmiHeader.biWidth * bmi.bmiHeader.biHeight * 3;

		pBitmapBits = 0;
		HDC hDCMem = ::CreateCompatibleDC(NULL);
		if(hDCMem)
		{	
			hDib = ::CreateDIBSection(hDCMem, &bmi, DIB_RGB_COLORS, &pBitmapBits, NULL, (DWORD)0);
			if(hDib)
			{
				::SelectObject(hDCMem, hDib);
				if(pRR->Init(hDCMem))
				{
					pRR->SetViewPort(hDCMem, rViewPort.cx, rViewPort.cy);
					pRR->SetProject(hDCMem, mtxProject);
					pRR->SetModelView(hDCMem, mtxModelView);
					pDLNode->Invalidate();

					::glMatrixMode(GL_MODELVIEW_MATRIX);
					//////////////////////////////////////////////////////////////////////////
					// Start to render
					//////////////////////////////////////////////////////////////////////////
					// Clear color and depth buffer
					::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					// Render all nodes from the root node
					pDLNode->Render();

					// Forces execution of OpenGL functions in finite time
					::glFinish();

					::DeleteObject(hDCMem);
				}
				else
				{
					::DeleteObject(hDib);
					hDib = NULL;
				}
			}

			::DeleteObject(hDCMem);
		}

		delete pRR;
	}

	return (hDib != NULL);
}

// Save the scene as bitmap
// virtual
bool GR_RROpenGL::GetBitmap(HDC hDC, HBITMAP& hDib, BITMAPINFO& bmi, LPVOID& pBitmapBits)
{
	int width = 0, height = 0;
	GetViewPort(hDC, width, height);

	hDib = NULL;
	GR_RROpenGL* pRR = new GR_RROpenGL();
	if(pRR)
	{
		pRR->m_pfd.dwFlags = PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_STEREO_DONTCARE;
		pRR->m_pfd.cColorBits = 24;
		pRR->m_pfd.cRedBits = 8;
		pRR->m_pfd.cRedShift = 16;
		pRR->m_pfd.cGreenBits = 8;
		pRR->m_pfd.cGreenShift = 8;
		pRR->m_pfd.cBlueBits = 8;
		pRR->m_pfd.cBlueShift = 0;
		pRR->m_pfd.cAlphaBits = 0;
		pRR->m_pfd.cAlphaShift = 0;
		pRR->m_pfd.cAccumBits = 64;
		pRR->m_pfd.cAccumRedBits = 16;
		pRR->m_pfd.cAccumGreenBits = 16;
		pRR->m_pfd.cAccumBlueBits = 16;
		pRR->m_pfd.cAccumAlphaBits = 0;
		pRR->m_pfd.cDepthBits = 32;
		pRR->m_pfd.cStencilBits = 8;
		pRR->m_pfd.cAuxBuffers = 0;
		pRR->m_pfd.iLayerType = PFD_MAIN_PLANE;
		pRR->m_pfd.bReserved = 0;
		pRR->m_pfd.dwLayerMask = 0;
		pRR->m_pfd.dwVisibleMask = 0;
		pRR->m_pfd.dwDamageMask = 0;
		pRR->SetDLNode(m_pDLNode);

		memset(&bmi, 0, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth		= width;
		bmi.bmiHeader.biHeight		= height;
		bmi.bmiHeader.biPlanes		= 1;
		bmi.bmiHeader.biBitCount	= 24;
		bmi.bmiHeader.biCompression	= BI_RGB;
		bmi.bmiHeader.biSizeImage	= width * height * 3;

		pBitmapBits = 0;
		hDib = ::CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, &pBitmapBits, NULL, (DWORD)0);
		if(hDib)
		{
			HDC hDCMem = ::CreateCompatibleDC(NULL);
			if(hDCMem)
			{
				::SelectObject(hDCMem, hDib);
				if(pRR->Init(hDCMem))
				{
					pRR->SetViewPort(hDCMem, width, height);
					pRR->SetProject(hDCMem, GetProject(hDC));
					pRR->SetModelView(hDCMem, GetModelView(hDC));
					m_pDLNode->Invalidate();

					::glMatrixMode(GL_MODELVIEW_MATRIX);
					//////////////////////////////////////////////////////////////////////////
					// Start to render
					//////////////////////////////////////////////////////////////////////////
					// Clear color and depth buffer
					::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					// Render all nodes from the root node
					m_pDLNode->Render();

					// Forces execution of OpenGL functions in finite time
					::glFinish();

					::DeleteObject(hDCMem);
				}
				else
				{
					::DeleteObject(hDib);
					::DeleteObject(hDCMem);
					hDib = NULL;
				}
			}
			else
			{
				::DeleteObject(hDib);
				hDib = NULL;
			}
		}

		delete pRR;
	}

	return (hDib != NULL);
}

// Print the scene to hDCPrinter
// virtual 
bool GR_RROpenGL::Print(HDC hDC, HDC hDCPrinter,  
						int iXDest,						// x-coord of destination upper-left corner
						int iYDest,						// y-coord of destination upper-left corner
						int iDestWidth,					// width of destination rectangle
						int iDestHeight)				// height of destination rectangle
{
	HBITMAP hBmp = NULL;
	BITMAPINFO bmi;
	LPVOID pBitmapBits = NULL;
	if(!GetBitmap(hDC, hBmp, bmi, pBitmapBits))
		return false;

	int nRet = ::StretchDIBits(hDCPrinter,
		iXDest, iYDest, iDestWidth, iDestHeight,
		0, 0,
		bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight,
		(GLubyte*) pBitmapBits,
		&bmi, DIB_RGB_COLORS, SRCCOPY);

	::DeleteObject(hBmp);
	if(nRet == GDI_ERROR)
		return false;
	return true;
}
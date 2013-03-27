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
#include "gr_rrdlopengl.h"

// If want GLUnurbsObj to render NURBS surface
// #define _GLUNURBSOBJ

#ifdef _GLUNURBSOBJ
class GLUnurbs;
#endif

class GR_DLSrf;
class GR_RRDLSrfOpenGL : public GR_RRDLOpenGL
{
public:
	GR_RRDLSrfOpenGL(GR_DLSrf* pDLSrf);
	virtual ~GR_RRDLSrfOpenGL(void);

protected:
	// Build the display list
	virtual bool OnBuild();

	// Render the display list
	virtual bool OnRender() const;

private:
	GR_DLSrf* m_pDLSrf;

#ifdef _GLUNURBSOBJ
	GLUnurbs* m_pnobj;
#ifdef _DEBUG
	CString Dump(GLfloat* p, GLint i) const;
#endif
#endif
};

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
#include "gr_rrdl.h"
#include <gl\gl.h>

class GR_RRDLOpenGL : public GR_RRDL
{
public:
	GR_RRDLOpenGL(GR_DL* pDL);
	virtual ~GR_RRDLOpenGL(void);

	// Build this display list
	virtual bool Build();

protected:
	// Build the display list
	virtual bool OnBuild() = 0;

	// Render the display list
	virtual bool OnRender() const;

//private:
	GLuint	m_nList;
};

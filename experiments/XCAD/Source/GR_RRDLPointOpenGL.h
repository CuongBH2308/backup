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

class GR_DLPoint;
class GR_RRDLPointOpenGL : public GR_RRDLOpenGL
{
public:
	GR_RRDLPointOpenGL(GR_DLPoint* pDLPoint);
	virtual ~GR_RRDLPointOpenGL(void);

protected:
	// Build the display list
	virtual bool OnBuild();

private:
	GR_DLPoint* m_pDLPoint;
};

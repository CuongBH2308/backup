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
#include "gr_rrdlattrib.h"

class GR_DLAttribPointSize;
class GR_RRDLAttribPointSizeOpenGL : public GR_RRDLAttrib
{
public:
	GR_RRDLAttribPointSizeOpenGL(GR_DLAttribPointSize* pDLAttribPointSize);
	virtual ~GR_RRDLAttribPointSizeOpenGL(void);

	// Apply this attribute
	virtual bool Apply(bool bApply);

private:
	GR_DLAttribPointSize* m_pDLAttribPointSize;
};

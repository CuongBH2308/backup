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
#include "GR_RRDLAttrib.h"

class GR_DLAttribColor;
class GR_RRDLAttribColorOpenGL : public GR_RRDLAttrib
{
public:
	GR_RRDLAttribColorOpenGL(GR_DLAttribColor* pDLAttribColor);
	virtual ~GR_RRDLAttribColorOpenGL(void);

	// Apply this attribute
	virtual bool Apply(bool bApply);

private:
	GR_DLAttribColor* m_pDLAttribColor;
};

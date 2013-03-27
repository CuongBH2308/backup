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

class GR_DLAttribTransform;
class GR_RRDLAttribTransformOpenGL : public GR_RRDLAttrib
{
public:
	GR_RRDLAttribTransformOpenGL(GR_DLAttribTransform* pDLAttribTransform);
	virtual ~GR_RRDLAttribTransformOpenGL(void);

	// Apply this attribute
	virtual bool Apply(bool bApply);

private:
	GR_DLAttribTransform* m_pDLAttribTransform;
};

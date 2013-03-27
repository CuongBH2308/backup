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
#include "gr_dlattrib.h"
#include "mh_matrix44.h"

class GR_DLAttribTransform : public GR_DLAttrib
{
public:
	GR_DLAttribTransform(const MH_Matrix44& mtx);
	virtual ~GR_DLAttribTransform(void);

	void SetTransform(const MH_Matrix44& mtxTransform);
	const MH_Matrix44& GetTransform() const;
private:
	MH_Matrix44 m_mtxTransform;
};

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
#include "gr_dlattribtransform.h"

GR_DLAttribTransform::GR_DLAttribTransform(const MH_Matrix44& mtx)
:m_mtxTransform(mtx)
{
}

GR_DLAttribTransform::~GR_DLAttribTransform(void)
{
}

void GR_DLAttribTransform::SetTransform(const MH_Matrix44& mtxTransform)
{
	m_mtxTransform = mtxTransform;
}

const MH_Matrix44& GR_DLAttribTransform::GetTransform() const
{
	return m_mtxTransform;
}
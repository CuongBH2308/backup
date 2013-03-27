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
#include "gr_dlattrib.h"
#include "gr_rrdlattrib.h"
#include "gr_rrmanager.h"
#include "sl_mm.h"

GR_DLAttrib::GR_DLAttrib(void)
:m_pRRDLAttrib(NULL)
{
}

GR_DLAttrib::~GR_DLAttrib(void)
{
	if(m_pRRDLAttrib)
		DEL_OBJ(m_pRRDLAttrib);
}

// Apply this attribute
bool GR_DLAttrib::Apply(bool bApply)
{
	if(!m_pRRDLAttrib)
	{
		// It will be deleted at de-constructor of GR_RRDLAttrib
		m_pRRDLAttrib = GR_RRManager::GetRRManager()->GetRRDLAttrib(this);
	}

	return m_pRRDLAttrib->Apply(bApply);
}
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
#include "fw_addin.h"

FW_AddIn::FW_AddIn(FW_AddIns* pAddIns, IXCADAddIn*pIXCADAddIn)
:m_pAddIns(pAddIns),
m_spIXCADAddIn(pIXCADAddIn)
{
}

FW_AddIn::~FW_AddIn(void)
{
	m_spIXCADAddIn = NULL;
}

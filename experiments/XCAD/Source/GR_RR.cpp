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
#include "gr_rr.h"

GR_RR::GR_RR(void)
:m_pDLNode(NULL)
{
}

GR_RR::~GR_RR(void)
{
}

// Set root DLNode
void GR_RR::SetDLNode(GR_DLNode* pDLNode)
{
	m_pDLNode = pDLNode;
}

// Get root DLNode
GR_DLNode* GR_RR::GetDLNode() const
{
	return m_pDLNode;
}

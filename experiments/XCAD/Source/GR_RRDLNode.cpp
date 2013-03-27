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
#include "gr_rrdlnode.h"
#include "gr_dlnode.h"

GR_RRDLNode::GR_RRDLNode(GR_DLNode* pDLNode)
:GR_RRDL(pDLNode),
m_pDLNode(pDLNode)
{
}

GR_RRDLNode::~GR_RRDLNode(void)
{
}

// Build this display list node
// virtual 
bool GR_RRDLNode::Build()
{
	if(!m_pDLNode)
		return false;
	return true;
}

// Render the display list node
// virtual 
bool GR_RRDLNode::OnRender() const
{
	if(!m_pDLNode)
		return false;

	GR_DLNodePtrVect* pvDLNode;
	GR_DLPtrVect* pvDL;
	m_pDLNode->GetChildren(pvDLNode, pvDL);

	// Apply the attributes
	m_pDLNode->ApplyAttrib();

	// Render the child nodes
	for(GR_DLNodePtrVect::const_iterator it = pvDLNode->begin(); it != pvDLNode->end(); it++)
	{
		if((*it).GetTarget())
		{
			bool bOK = (*it)->Render();
			ASSERT(bOK);
		}
	}

	// Render the child display lists
	for(GR_DLPtrVect::const_iterator it = pvDL->begin(); it != pvDL->end(); it++)
	{
		if((*it).GetTarget())
		{
			bool bOK = (*it)->Render();
			ASSERT(bOK);
		}
	}

	// Un-apply the attributes
	m_pDLNode->ApplyAttrib(false);

	return true;
}

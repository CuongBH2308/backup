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
#include "gr_dlnode.h"
#include <algorithm>
#include <typeinfo.h>
#include "gr_dl.h"
#include "gr_dlattrib.h"
#include "gr_rrdlnode.h"
#include "gr_rrmanager.h"
#include "gr_selector.h"
#include "gr_selectionset.h"
#include "sl_mm.h"

GR_DLNode::GR_DLNode(const SL_Ptr<GR_DLNode>& pParentNode, GR_Selector* pSelector)
:GR_DL(pParentNode, false),
m_pSelector(pSelector)
{
	if(pParentNode.GetTarget())
		pParentNode->AddDLNode(this);
}

GR_DLNode::~GR_DLNode(void)
{
	// Cleanup the child nodes
	for(GR_DLNodePtrVect::const_iterator it = m_vDLNode.begin(); it != m_vDLNode.end(); ++it)
		DEL_OBJ((*it).GetTarget());
	m_vDLNode.clear();

	// Cleanup the child display lists
	for(GR_DLPtrVect::const_iterator it = m_vDL.begin(); it != m_vDL.end(); ++it)
		DEL_OBJ((*it).GetTarget());
	m_vDL.clear();

	if(m_pSelector)
		delete m_pSelector;
}

// Detach this node from its parent node
// We should call this function before delete it
bool GR_DLNode::Detach()
{
	SL_Ptr<GR_DLNode> pParentNode = GetParent();
	if(pParentNode.GetTarget())
		return pParentNode->RemoveDLNode(this);
	else
		return false;
}

// Invalidate the DL Node. We need to build the DL Node before render it
void GR_DLNode::Invalidate()
{
	// Build the child nodes
	for(GR_DLNodePtrVect::const_iterator it = m_vDLNode.begin(); it != m_vDLNode.end(); ++it)
	{
		if((*it).GetTarget())
			(*it)->Invalidate();
	}

	// Build the child display lists
	for(GR_DLPtrVect::const_iterator it = m_vDL.begin(); it != m_vDL.end(); ++it)
	{
		if((*it).GetTarget())
			(*it)->Invalidate();
	}
}

// Use GR_RRDLNode to render the display list node
// virtual
bool GR_DLNode::Render()
{
	GR_RRDL* pRRDL = GetRRDL();
	// Use GR_RR to render the display list
	if(!pRRDL)
	{
		// It will be deleted at de-constructor of GR_DL
		pRRDL = GR_RRManager::GetRRManager()->GetRRDL(this);
		SetRRDL(pRRDL);
	}

	return pRRDL->Render();
}

// Try to select the DL
// The created selections are stored in selSet
bool GR_DLNode::Select(GR_SelectionSet& selSet,
					   const GR_SelectionFilterSet& filterSet,
					   const MH_CrvRay& ray,
					   float fTolerance) const
{
	// Select the child nodes
	for(GR_DLNodePtrVect::const_iterator it = m_vDLNode.begin(); it != m_vDLNode.end(); ++it)
	{
		if((*it).GetTarget())
			(*it)->Select(selSet, filterSet, ray, fTolerance);
	}

	if(m_pSelector)
	{
		// Select the child display lists
		for(GR_DLPtrVect::const_iterator it = m_vDL.begin(); it != m_vDL.end(); ++it)
		{
			if((*it).GetTarget())
				m_pSelector->Select(selSet, filterSet, (*it).GetTarget(), ray, fTolerance);
		}
	}

	return selSet.IsNotEmpty();
}

// Add a DLNode to m_vDLNode
void GR_DLNode::AddDLNode(const SL_Ptr<GR_DLNode>& pDLNode)
{
	m_vDLNode.push_back(pDLNode);
}

// Remove a DLNode from m_vDLNode
bool GR_DLNode::RemoveDLNode(const SL_Ptr<GR_DLNode>& pDLNode)
{
	GR_DLNodePtrVect::iterator it = std::find(m_vDLNode.begin(), m_vDLNode.end(), pDLNode);
	if(it != m_vDLNode.end())
	{
		m_vDLNode.erase(it);
		return true;
	}
	return false;
}

// Add a DL to m_vDL
void GR_DLNode::AddDL(const SL_Ptr<GR_DL>& pDL)
{
	m_vDL.push_back(pDL);
}

// Remove a DL from m_vDL
bool GR_DLNode::RemoveDL(const SL_Ptr<GR_DL>& pDL)
{
	GR_DLPtrVect::iterator it = std::find(m_vDL.begin(), m_vDL.end(), pDL);
	if(it != m_vDL.end())
	{
		m_vDL.erase(it);
		return true;
	}
	return false;
}

// Get children of this node
void GR_DLNode::GetChildren(GR_DLNodePtrVect*& pvDLNode, GR_DLPtrVect*& pvDL)
{
	pvDLNode = &m_vDLNode;
	pvDL = &m_vDL;
}
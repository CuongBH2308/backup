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
#include "gr_dl.h"
#include "mh_matrix44.h"

class MH_Point3;
class MH_CrvRay;
class MH_Vector3;
class GR_DLAttrib;
class GR_Selector;
class GR_SelectionSet;
class GR_SelectionFilterSet;
class GR_DLNode : public GR_DL
{
public:
	GR_DLNode(const SL_Ptr<GR_DLNode>& pParentNode, GR_Selector* pSelector = NULL);
	virtual ~GR_DLNode(void);

//////////////////////////////////////////////////////////////////////////
// virtual functions
//////////////////////////////////////////////////////////////////////////
	// Detach this node from its parent node
	// We should call this function before deleting it
	virtual bool Detach();

	// Invalidate the DL Node. We need to build the DL Node before render it
	virtual void Invalidate();
		
	// Render the child nodes and display list
	virtual bool Render();

//////////////////////////////////////////////////////////////////////////
// public functions
//////////////////////////////////////////////////////////////////////////
	// Try to select the DL
	// The created selections are stored in selSet
	bool Select(GR_SelectionSet& selSet,
		const GR_SelectionFilterSet& filterSet,
		const MH_CrvRay& ray,
		float fTolerance) const;

	// Add a DLNode to m_vDLNode
	void AddDLNode(const SL_Ptr<GR_DLNode>& pDLNode);

	// Remove a DLNode from m_vDLNode
	bool RemoveDLNode(const SL_Ptr<GR_DLNode>& pDLNode);

	// Add a DL to m_vDL
	void AddDL(const SL_Ptr<GR_DL>& pDL);

	// Remove a DL from m_vDL
	bool RemoveDL(const SL_Ptr<GR_DL>& pDL);

	// Get children of this node
	void GetChildren(GR_DLNodePtrVect*& pvDLNode, GR_DLPtrVect*& pvDL);

private:
	// The children (nodes) of this node
	GR_DLNodePtrVect	m_vDLNode;

	// The children (DLs) of this node
	GR_DLPtrVect		m_vDL;

	// Used to determine whether this node can be selected
	// and it will create corresponding selections
	GR_Selector*		m_pSelector;
};

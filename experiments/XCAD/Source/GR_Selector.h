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
/************************************************************************/
/* 
      GR_DLNode1  ----->  GR_Selector1  <1, 2>
	      |_GR_DLNode2 ----->  GR_Selector2 <3>
		  |     |_GR_DL
		  |_GR_DL

How GR_Selector works:
Assuming the DL-Node structure is as above, then once user wants select kind 1,
we will 
1. check node from GR_DLNode1
2. check all child nodes of GR_DLNode1 but ignore the node (and its children) whose GR_Selector points to other kinds
3. check all child DL of GR_DLNode1

Prerequirment:
When a DLNode is created, we should know:
1. Which kinds of object can be found in this node and its children

Then we should:
1. Create a GR_Selector
2. Define some filters in that GR_Selector. Those filters are related to the kinds
   of objects in the DLNode
3. Set the GR_Selector to the DLNode

Select work flow:
1. A command cares kind1 object 
2. Mouse moves to a DLNode
3. DLNode::Select will be called
4. DLNode::Select will call GR_Selector_Derive::Select
5. GR_Selector_Derive::Select will create corresponding selection

Notice:
GR_Selector_Derive should know DLNode and its children mean which kinds of objects
*/
/************************************************************************/

class MH_CrvRay;
class GR_DL;
class GR_Selection;
class GR_SelectionSet;
class GR_SelectionFilterSet;
class GR_Selector
{
protected:
	GR_Selector(void);
public:
	// Destructor
	virtual ~GR_Selector(void);
	
	// Try to select the DL
	// The created selections are stored in selSet
	bool Select(GR_SelectionSet& selSet,
		const GR_SelectionFilterSet& filterSet,
		GR_DL* pDL, 
		const MH_CrvRay& ray,
		float fTolerance) const;

protected:
	// Check whether the DL potentially can be that selection
	// pSel will be created in OnQualify
	// So it should be deleted by the invoker
	virtual bool OnQualify(GR_SelectionSet& selSet, GR_DL* pDL) const = 0;
};

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
#include "gr_dlnode.h"
#include "gr_collect.h"

class DR_StXform;
class GR_DLNodeGrids : public GR_DLNode
{
public:
	GR_DLNodeGrids(const SL_Ptr<GR_DLNode>& pDLNode,
		const SL_Ptr<DR_StXform>& pStXform);
	virtual ~GR_DLNodeGrids(void);

	// Render the child nodes and display list
	// We should adjust the h/w of the grid here according to the view
	virtual bool Render();

private:
	// Specify X, Y, Z Axis
	SL_Ptr<DR_StXform> m_pStXform;

	// The grids of the sketch node
	GR_DLCrvPtrVect m_vDLCrvGrids;
};

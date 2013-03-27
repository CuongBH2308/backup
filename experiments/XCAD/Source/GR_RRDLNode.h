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
#include "gr_rrdl.h"

class GR_DLNode;
class GR_RRDLNode : public GR_RRDL
{
public:
	GR_RRDLNode(GR_DLNode* pDLNode);
	virtual ~GR_RRDLNode(void);

	// Build this display list node
	virtual bool Build();

protected:
	// Render the display list node
	virtual bool OnRender() const;

	// GR_DLNode that should be rendered by this renderer
	GR_DLNode* m_pDLNode;
};

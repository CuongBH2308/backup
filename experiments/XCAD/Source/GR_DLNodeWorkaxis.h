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

class DR_StCrvLine;
class GR_DLNode;
class GR_DLNodeWorkaxis : public GR_DLNode
{
public:
	GR_DLNodeWorkaxis(const SL_Ptr<GR_DLNode>& pParentNode, const SL_Ptr<DR_StCrvLine>& pStLine);
	virtual ~GR_DLNodeWorkaxis(void);
	
	// Get line
	const SL_Ptr<DR_StCrvLine>& GetStLine() const;

	// Set the color of the DL
	void SetColor(float r, float g, float b);
private:
	SL_Ptr<DR_StCrvLine>		m_pStLine;
};

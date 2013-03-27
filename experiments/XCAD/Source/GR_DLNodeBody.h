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

class DR_StBody;
class GR_DLNodeBody : public GR_DLNode
{
public:
	GR_DLNodeBody(const SL_Ptr<DR_StBody>& pStBody, const SL_Ptr<GR_DLNode>& pParentNode);
	virtual ~GR_DLNodeBody(void);

	bool Update();
private:
	// Body that need be shown
	SL_Ptr<DR_StBody> m_pStBody;
};

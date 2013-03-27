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
#include <vector>
#include "mh_obj.h"
#include "mh_facet.h"

class MH_Model : public MH_Obj
{
public:
	MH_Model(void);
	virtual ~MH_Model(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

private:
	std::vector<MH_Facet> m_vFacets;
};

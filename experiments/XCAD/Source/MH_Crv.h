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
#include "mh_obj.h"
#include "mh_crvpt.h"
#include "mh_collect.h"

class MH_Crv : public MH_Obj
{
public:
	MH_Crv(void);
	virtual ~MH_Crv(void);

	// Tessellate the curve
	// The points are stored in m_vPts
	virtual bool Tessellate(float fTolerance);

	// Copy this curve
	virtual MH_Crv* Copy() = 0;

	// Get the nurbs expression
	virtual MH_CrvNurbs GetNurbs() const = 0;

	// Cleanup the MH_LineSeg in m_vLineSegs
	bool Cleanup();

	// Get points
	const MH_CrvPtVect& GetPts() const;

	// Is it invalid
	const bool&	IsInvalid() const;

	// Invalidate the obj. We need to tessellate it 
	void Invalidate(bool bInvalid);

protected:
	MH_CrvPtVect m_vCrvPt;

private:
	bool m_bInvalid;
};

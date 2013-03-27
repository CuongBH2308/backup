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
#include "dr_stcrv.h"
#include "mh_crvnurbs.h"

class MH_Matrix44;
class DR_StCrvNurbs : public DR_StCrv
{
public:
	DR_StCrvNurbs(const SL_Ptr<DR_Fragment>& pFragment, const MH_CrvNurbs& nurbs);
	virtual ~DR_StCrvNurbs(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Get curve
	virtual MH_Crv* GetCrv();

	// Get start DR_StPoint
	virtual SL_Ptr<DR_StPoint> GetStartPt() const;

	// Get end DR_StPoint
	virtual SL_Ptr<DR_StPoint> GetEndPt() const;

    // Set Nurbs
	void SetNurbs(const MH_CrvNurbs& nurbs);

	// Get Nurbs
	const MH_CrvNurbs& GetNurbs() const;

	// Set the nIndex-th CV
	bool SetCV(size_t nIndex, const MH_CV& cv);

	// Set the nIndex-th CV
	bool SetCV(size_t nIndex, const MH_Point3& pt);

private:
	MH_CrvNurbs m_nurbs;
};

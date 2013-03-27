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
#include "mh_crvline.h"

class DR_StCrvLine : public DR_StCrv
{
public:
	DR_StCrvLine(const SL_Ptr<DR_Fragment>& pFragment, const MH_CrvLine& line);
	virtual ~DR_StCrvLine(void);

	// Transform this object
	virtual void Transform(const MH_Matrix44& mtx);

	// Get curve
	virtual MH_Crv* GetCrv();

	// Set line
	void SetLine(const MH_CrvLine& line);

	// Get line
	const MH_CrvLine& GetLine() const;
private:
	MH_CrvLine m_line;
};

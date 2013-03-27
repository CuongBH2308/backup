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
#include "dr_dctsketch.h"

class DR_StXform;
class DR_StVector3;
class DR_DCtSketch2D : public DR_DCtSketch
{
public:
	DR_DCtSketch2D(const SL_Ptr<DR_Fragment>& pFragment, const SL_Ptr<DR_StXform>& pStXform);
	virtual ~DR_DCtSketch2D(void);

	// Compute the normal in new condition
	virtual HRESULT Compute();

	// Get the normal of the sketch
	const SL_Ptr<DR_StVector3>& GetNormal() const;

	// Get transform 
	const SL_Ptr<DR_StXform>& GetStXform() const;

private:
	// Input of the constraint. 
	SL_Ptr<DR_StXform> m_pStXform;

	// Output of the constraint.
	// Normal of the sketch
	SL_Ptr<DR_StVector3> m_pNormal;
};

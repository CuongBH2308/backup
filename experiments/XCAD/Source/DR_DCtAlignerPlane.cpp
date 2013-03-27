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


#include "stdafx.h"
#include "dr_dctalignerplane.h"
#include "dr_result.h"
#include "dr_stplane.h"
#include "dr_stxform.h"
#include "mh_crdsys.h"
#include "mh_plane.h"

DR_DCtAlignerPlane::DR_DCtAlignerPlane(const SL_Ptr<DR_Fragment>& pFragment, 
									   const SL_Ptr<DR_StPlane>& pStPlane,
									   const SL_Ptr<DR_StXform>& pStXform)
:DR_DCtAligner(pFragment, pStXform),
m_pStPlane(pStPlane)
{
	// Add an input 
	AddInput(m_pStPlane.GetTarget());

	// Set output of the constraint
	AddOutput(pStXform.GetTarget());

	// Compute to update pStXform according to pStPlane
	HRESULT hr = Compute();
	ASSERT(SUCCEEDED(hr));
}

DR_DCtAlignerPlane::~DR_DCtAlignerPlane(void)
{
}

// Compute the transform matrix according to the DR_StPlane
// virtual 
HRESULT DR_DCtAlignerPlane::Compute()
{
	ASSERT(m_pStPlane.GetTarget());
	
	// Get geometry of the plane
	const MH_Plane& plane = m_pStPlane->GetPlane();

	// Get output of the constraint
	const SL_Ptr<DR_StXform>& pStXform = GetStXform();
	ASSERT(pStXform.GetTarget());
	if(!pStXform.GetTarget())
		return DR_RLT_INPUT_MISS;

	// Update data in the output
	pStXform->SetXform(MH_CrdSys(plane).GetTransform());

	return S_OK;
}
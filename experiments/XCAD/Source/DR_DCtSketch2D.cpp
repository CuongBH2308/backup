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
#include "dr_dctsketch2d.h"
#include "dr_result.h"
#include "dr_stvector3.h"
#include "dr_stxform.h"
#include "sl_mm.h"

DR_DCtSketch2D::DR_DCtSketch2D(const SL_Ptr<DR_Fragment>& pFragment, const SL_Ptr<DR_StXform>& pStXform)
:DR_DCtSketch(pFragment),
m_pStXform(pStXform)
{
	ASSERT(m_pStXform.GetTarget());

	// Add Input
	AddInput(m_pStXform.GetTarget());

	// Create the output: normal
	m_pNormal = NEW_OBJ(DR_StVector3, this)(pFragment);
	ASSERT(m_pNormal.GetTarget());

	// Set output
	AddOutput(m_pNormal.GetTarget());

	// Compute to update the output according to the inputs
	HRESULT hr = Compute();
	ASSERT(SUCCEEDED(hr));
}

DR_DCtSketch2D::~DR_DCtSketch2D(void)
{
}

// Get the normal of the sketch
const SL_Ptr<DR_StVector3>& DR_DCtSketch2D::GetNormal() const
{
	return m_pNormal;
}

// Get transform 
const SL_Ptr<DR_StXform>& DR_DCtSketch2D::GetStXform() const
{
	return m_pStXform;
}

// Compute the normal in new condition
// virtual 
HRESULT DR_DCtSketch2D::Compute()
{
	ASSERT(m_pStXform.GetTarget());
	if(!m_pStXform.GetTarget())
		return DR_RLT_INPUT_MISS;

	ASSERT(m_pNormal.GetTarget());
	if(!m_pNormal.GetTarget())
		return DR_RLT_OUTPUT_MISS;

	// Get the transformation matrix
	const MH_Matrix44& mtx = m_pStXform->GetXform();

	// Get the Z axis according to the matrix
	MH_Vector3 vZ(mtx[2], mtx[6], mtx[10]);
	vZ.Normalize();

	// Set the new normal
	m_pNormal->SetV(vZ);

	return S_OK;
}
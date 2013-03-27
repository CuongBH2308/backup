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
#include "dr_ct.h"
#include <algorithm>
#include "dr_fragment.h"
#include "dr_st.h"

DR_Ct::DR_Ct(const SL_Ptr<DR_Fragment>& pFragment)
:DR_Obj(pFragment),
m_nStatus(DR_Ct::eDirty)
{
	// Add this constraint into the fragment
	// pFragment->Add(this);
}

DR_Ct::~DR_Ct(void)
{
}

// Add a new input
// Will check whether it exists
void DR_Ct::AddInput(const SL_Ptr<DR_St>& pSt)
{
	DR_StPtrVect::const_iterator it = std::find(m_vInput.begin(), m_vInput.end(), pSt);
	if(it == m_vInput.end())
		m_vInput.push_back(pSt);

	// This constraint is the output of the St
	pSt->AddOutput(this);
}

// Get m_vInputs
const DR_StPtrVect& DR_Ct::GetInputs() const
{
	return m_vInput;
}

// Add a new output
// Will check whether it exists
void DR_Ct::AddOutput(const SL_Ptr<DR_St>& pSt)
{
	DR_StPtrVect::const_iterator it = std::find(m_vOutput.begin(), m_vOutput.end(), pSt);
	if(it == m_vOutput.end())
		m_vOutput.push_back(pSt);

	// This constraint is the input of the St
	pSt->AddInput(this);
}

// Get m_vOutputs
const DR_StPtrVect& DR_Ct::GetOutputs() const
{
	return m_vOutput;
}

// Add a new status
void DR_Ct::AddStatus(const DR_Ct::EStatus& eStatus)
{
	m_nStatus |= eStatus;
}

// Remove a status
void DR_Ct::RemoveStatus(const EStatus& eStatus)
{
	m_nStatus &= ~eStatus;
}

// Has eStatus
bool DR_Ct::InStatus(const DR_Ct::EStatus& eStatus) const
{
	return (m_nStatus&eStatus)!=0;
}

// Get status of the object
const DWORD& DR_Ct::GetStatus() const
{
	return m_nStatus;
}
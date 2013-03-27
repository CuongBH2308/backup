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
#include "dr_st.h"
#include <algorithm>
DR_St::DR_St(const SL_Ptr<DR_Fragment>& pFragment)
:DR_Obj(pFragment)
{
}

DR_St::~DR_St(void)
{
}

// Add pCt whose output is this St
void DR_St::AddInput(const SL_Ptr<DR_Ct>& pCt)
{
	DR_CtPtrVect::const_iterator it = std::find(m_vInput.begin(), m_vInput.end(), pCt);
	if(it == m_vInput.end())
		m_vInput.push_back(pCt);
}

// Get m_vInput
const DR_CtPtrVect& DR_St::GetInputs() const
{
	return m_vInput;
}

// Add a new output
// Will check whether it exists
void DR_St::AddOutput(const SL_Ptr<DR_Ct>& pCt)
{
	DR_CtPtrVect::const_iterator it = std::find(m_vOutput.begin(), m_vOutput.end(), pCt);
	if(it == m_vOutput.end())
		m_vOutput.push_back(pCt);
}

// Get m_vOutputs
const DR_CtPtrVect& DR_St::GetOutputs() const
{
	return m_vOutput;
}
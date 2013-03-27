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
#include "dr_dctsolver.h"
#include "dr_uct.h"

DR_DCtSolver::DR_DCtSolver(const SL_Ptr<DR_Fragment>& pFragment)
:DR_DCt(pFragment)
{
}

DR_DCtSolver::~DR_DCtSolver(void)
{
}

// Compute the output in new condition
// virtual 
HRESULT DR_DCtSolver::Compute()
{
	HRESULT hr = S_OK;
	DR_UCtPtrVect::const_iterator it = m_vUCt.begin();
	DR_UCtPtrVect::const_iterator itEnd = m_vUCt.end();
	for(; it!=itEnd; ++it)
	{
		hr = (*it)->Compute();
		if(FAILED(hr))
			return hr;
	}
	return hr;
}

// Add an undirected constraint
void DR_DCtSolver::AddUCt(const SL_Ptr<DR_UCt> pUCt)
{
	m_vUCt.push_back(pUCt);
}
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


#include "StdAfx.h"
#include ".\dr_constraintmanager.h"
#include <algorithm>
#include "DR_Constraint.h"

DR_ConstraintManager::DR_ConstraintManager(void)
{
}

DR_ConstraintManager::~DR_ConstraintManager(void)
{
}

// Add a new constraint
// will update m_mConstraint
bool DR_ConstraintManager::Add(DR_Constraint* pConstraint)
{
	// Get m_vInputs
	std::vector<MH_Obj*>& vInputs = pConstraint->GetInputs();
	for(std::vector<MH_Obj*>::iterator it = vInputs.begin(); it != vInputs.end(); it++)
	{
		std::vector<DR_Constraint*>* pvConstraint = m_mConstraint[*it]; 
		if(!pvConstraint)
		{
			pvConstraint = new std::vector<DR_Constraint*>;
			m_mConstraint[*it] = pvConstraint;
			pvConstraint->push_back(pConstraint);
		}
		else
		{
			std::vector<DR_Constraint*>::iterator i = std::find(pvConstraint->begin(), pvConstraint->end(), pConstraint);
			if(i == pvConstraint->end())
				pvConstraint->push_back(pConstraint);
		}
	}

	//// Get m_pOutput
	//MH_Obj*	pOutput = pConstraint->GetOutput();

	return true;
}

// Remove a constraint
// will update m_mConstraint
bool DR_ConstraintManager::Remove(DR_Constraint* pConstraint)
{
	// Get m_vInputs
	std::vector<MH_Obj*>& vInputs = pConstraint->GetInputs();
	for(std::vector<MH_Obj*>::iterator it = vInputs.begin(); it != vInputs.end(); it++)
	{
		std::vector<DR_Constraint*>* pvConstraint = m_mConstraint[*it]; 
		if(pvConstraint)
		{
			std::vector<DR_Constraint*>::iterator i = std::find(pvConstraint->begin(), pvConstraint->end(), pConstraint);
			if(i == pvConstraint->end())
			{
				pvConstraint->erase(i);
				if(pvConstraint->size() == 0)
				{
					delete pvConstraint;
					m_mConstraint[*it] = NULL;
					m_mConstraint.erase(*it);
				}
			}
		}
		else
		{
			ASSERT(0);
		}
	}

	return true;
}

// Call DR_Constraint::Compute from top to down
HRESULT DR_ConstraintManager::ComputeFrom(MH_Obj* pObj)
{
	HRESULT hr = S_OK;
	if(!pObj)
	{
		ASSERT(0);
		return hr;
	}

	std::vector<DR_Constraint*>* pvConstraint = m_mConstraint[pObj]; 
	for(std::vector<DR_Constraint*>::iterator it = pvConstraint->begin(); it != pvConstraint->end(); it++)
	{
		hr = (*it)->Compute();
		if(FAILED(hr))
		{
			ASSERT(0);
			break;
		}

		MH_Obj* pOutput = (*it)->GetOutput();
		if(pOutput)
		{
			hr = ComputeFrom(pOutput);
			if(FAILED(hr))
			{
				ASSERT(0);
				break;
			}
		}
	}
	
	return hr;
}

// Call DR_Constraint::Compute from top to down
HRESULT DR_ConstraintManager::Compute()
{
	HRESULT hr = S_OK;
	std::map<MH_Obj*, std::vector<DR_Constraint*>*>::const_iterator it = m_mConstraint.begin();
	MH_Obj* pBegin = it->first;
	if(pBegin)
		hr = ComputeFrom(pBegin);
	return hr;
}
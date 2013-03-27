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

#include <map>
#include <vector>

class MH_Obj;
class DR_Constraint;

class DR_ConstraintManager
{
public:
	DR_ConstraintManager(void);
	virtual ~DR_ConstraintManager(void);

	// Add a new constraint
	// will update m_mConstraint
	bool Add(DR_Constraint* pConstraint);

	// Remove a constraint
	// will update m_mConstraint
	bool Remove(DR_Constraint* pConstraint); 

	// Call DR_Constraint::Compute from top to down
	HRESULT ComputeFrom(MH_Obj* pObj);

	// Call DR_Constraint::Compute from top to down
	HRESULT Compute();

private:
	// Build the relationship between MH_Obj and the constraints whose INPUT is this MH_Obj
	std::map<MH_Obj*, std::vector<DR_Constraint*>*>	m_mConstraint;
};

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
#include "dr_obj.h"
#include "dr_collect.h"

/************************************************************************/
/* 
			DR_St ...	DR_St		----  Inputs
				\     /
				 \   /
				 DR_Ct
				   |
				   |
				 DR_St				---  Output
*/
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
// Constraint
//////////////////////////////////////////////////////////////////////////
class DR_St;
class DR_Ct : public DR_Obj
{
public:
	DR_Ct(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_Ct(void);

	enum EStatus
	{
		eHealthy	= 1,
		eDirty		= 1<<1
	};

	// Compute the output in new condition
	virtual HRESULT Compute() = 0;

	// Add a new input
	// Will check whether it exists
	void AddInput(const SL_Ptr<DR_St>& pSt);

	// Get m_vInputs
	const DR_StPtrVect& GetInputs() const;

	// Add a new output
	// Will check whether it exists
	void AddOutput(const SL_Ptr<DR_St>& pSt);

	// Get m_vOutputs
	const DR_StPtrVect& GetOutputs() const;

	// Add a new status
	void AddStatus(const EStatus& eStatus);

	// Remove a status
	void RemoveStatus(const EStatus& eStatus);

	// Has eStatus
	bool InStatus(const EStatus& eStatus) const;

	// Get status of the object
	const DWORD& GetStatus() const;
private:
	DR_StPtrVect m_vInput;
	DR_StPtrVect m_vOutput;
	DWORD	m_nStatus;
};

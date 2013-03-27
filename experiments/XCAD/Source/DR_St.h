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

//////////////////////////////////////////////////////////////////////////
// State
//////////////////////////////////////////////////////////////////////////
class DR_St : public DR_Obj
{
	friend class DR_Ct;
public:
	DR_St(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_St(void);

	// Get m_vInput
	const DR_CtPtrVect& GetInputs() const;

	// Get m_vOutputs
	const DR_CtPtrVect& GetOutputs() const;

private:
	// Add pCt whose output is this St
	void AddInput(const SL_Ptr<DR_Ct>& pCt);

	// Add a new output
	// Will check whether it exists
	void AddOutput(const SL_Ptr<DR_Ct>& pCt);

	DR_CtPtrVect	m_vInput;
	DR_CtPtrVect	m_vOutput;
};

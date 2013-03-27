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
#include "sl_obj.h"
#include "dr_collect.h"

class DR_DCtStop;
class DR_Fragment : public SL_Obj
{
public:
	DR_Fragment(void);
	virtual ~DR_Fragment(void);

#ifdef _DEBUG
	// Dump the fragment into a file
	// if bRunDotty is true, then run dotty.exe
	// Refer to http:www.graphviz.org/ for this tool
	void Dump(LPCTSTR lpFileName, BOOL bRunDotty = TRUE) const;
	void Dump(CString& str, const SL_Ptr<DR_Ct>& pCt) const;
#endif
	// Get stop state
	SL_Ptr<DR_DCtStop> GetDCtStop() const;

	// Make pSt and its outputs dirty
	// Then when we do the compute, just care those dirty Ct
	HRESULT Dirty(const SL_Ptr<DR_St>& pSt) const;

	// Compute the constraint pCt.
	// If some constraints above pCt have NOT been computed, then
	// these constraints should be computed first
	HRESULT Compute(const SL_Ptr<DR_Ct>& pCt) const;

	// Call DR_Constraint::Compute from top to down
	HRESULT Compute() const;

private:
	// Delete pCt and its inputs
	void Delete(const SL_Ptr<DR_Ct>& pCt) const;

	// Stop state
	SL_Ptr<DR_DCtStop> m_pDCtStop;
};

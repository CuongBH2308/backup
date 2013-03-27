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
#include "dr_dct.h"

/************************************************************************/
/* 
DR_DCtSolver will keep a serial of DR_UCt
DR_DCtSolver will solve (non)linear equations to determine the new position
of the objects constrained by DR_UCt(s)
*/
/************************************************************************/
class DR_UCt;
class DR_DCtSolver : public DR_DCt
{
public:
	DR_DCtSolver(const SL_Ptr<DR_Fragment>& pFragment);
	virtual ~DR_DCtSolver(void);

	// Compute the output in new condition
	virtual HRESULT Compute();

	// Add an undirected constraint
	void AddUCt(const SL_Ptr<DR_UCt> pUCt);
private:
	DR_UCtPtrVect	m_vUCt;
};

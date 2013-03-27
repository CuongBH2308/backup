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
#include "dr_uct.h"
#include "dr_collect.h"

class DR_StPoint;
class DR_StCrv;
class DR_UCtCVCrv :	public DR_UCt
{
public:
	// pStCV is the nIndex-th control point of pStCrv
	DR_UCtCVCrv(const SL_Ptr<DR_DCtSolver>& pSolver, 
		const SL_Ptr<DR_StPoint>&	pStCV,
		const SL_Ptr<DR_StCrv>& pStCrv,
		size_t nIndex);
	virtual ~DR_UCtCVCrv(void);

	// m_eCase=eFixCV:	should move the curve according to the cv
	// m_eCase=eFixCrv: should move the cv according to the curve
	enum ECase
	{
		eFixCV,
		eFixCrv
	};

	// Get DR_UCtCVCrv according to DR_StPoint/DR_StCrv
	static DR_UCtCVCrvPtrVect GetUCtCVCrvs(const SL_Ptr<DR_St>& pSt);

	// Set case to all UCtCVCrv
	static void SetCase(const DR_UCtCVCrvPtrVect& vUCtCVCrv, const DR_UCtCVCrv::ECase& eCase);

	// Compute all UCtCVCrv
	static HRESULT ComputeAll(const DR_UCtCVCrvPtrVect& vUCtCVCrv);

	// Set the case
	void SetCase(const ECase& eCase);

	// Get m_eCase
	const ECase& GetCase() const;

	// Get m_nIndex
	size_t	GetIndex() const;

	// Get m_pStCV
	const SL_Ptr<DR_StPoint>& GetStPoint() const;
protected:
	SL_Ptr<DR_StPoint>	m_pStCV;
	SL_Ptr<DR_StCrv>	m_pStCrv;
	size_t				m_nIndex;
	ECase				m_eCase;
};

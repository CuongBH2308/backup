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
#include "brep_entity.h"
#include "brep_collect.h"

class MH_Srf;
class BREP_Face : public BREP_Entity
{
public:
	// The constructed face is owned by pShell
	BREP_Face(const SL_Ptr<BREP_Shell>& pShell);

	// The constructed face is owned by pShell
	BREP_Face(const SL_Ptr<BREP_Shell>& pShell, const SL_Ptr<MH_Srf>& pSrf, const BREP_LoopPtrVect& vLoop);

	// De-constructor
	virtual ~BREP_Face(void);

	// Copy the entity
	BREP_Face* Copy(const SL_Ptr<BREP_Shell>& pShell);

	// Get m_pShell
	const SL_Ptr<BREP_Shell>& GetShell() const;

	// Get m_pSrf
	const SL_Ptr<MH_Srf>& GetSrf() const;

	// Add loop
	void AddLoop(const SL_Ptr<BREP_Loop>& pLoop);

	// Get m_vLoop
	const BREP_LoopPtrVect& GetLoops() const;
private:
	// The owner of this face
	SL_Ptr<BREP_Shell>	m_pShell;

	// Geometry information
	SL_Ptr<MH_Srf>		m_pSrf;

	// The face includes these loops
	BREP_LoopPtrVect	m_vLoop;
};

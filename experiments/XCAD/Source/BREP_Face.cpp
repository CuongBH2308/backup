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
#include "brep_face.h"
#include "brep_loop.h"
#include "brep_shell.h"
#include "mh_srf.h"
#include "sl_mm.h"

// The constructed face is owned by pShell
BREP_Face::BREP_Face(const SL_Ptr<BREP_Shell>& pShell)
:m_pShell(pShell)
{
	if(m_pShell.GetTarget())
		m_pShell->AddFace(this);
}

// The constructed face is owned by pShell
BREP_Face::BREP_Face(const SL_Ptr<BREP_Shell>& pShell, const SL_Ptr<MH_Srf>& pSrf, const BREP_LoopPtrVect& vLoop)
:m_pShell(pShell),
m_pSrf(pSrf),
m_vLoop(vLoop)
{
	if(m_pShell.GetTarget())
		m_pShell->AddFace(this);
}

// De-constructor
BREP_Face::~BREP_Face(void)
{
}

// Copy the entity
BREP_Face* BREP_Face::Copy(const SL_Ptr<BREP_Shell>& pShell)
{
	BREP_Face* pFace = NEW_OBJ(BREP_Face, pShell.GetTarget())(pShell);
	if(pFace)
	{
		BREP_LoopPtrVect::const_iterator it		= m_vLoop.begin();
		BREP_LoopPtrVect::const_iterator itEnd	= m_vLoop.end();
		for(; it!=itEnd; ++it)
		{
			BREP_Loop* pLoop = (*it)->Copy(pFace);
			ASSERT(pLoop);
			if(pLoop)
				pFace->AddLoop(pLoop);
		}

		// Copy the geometry information
		m_pSrf = pFace->m_pSrf->Copy();
	}
	return pFace;
}

// Get m_pShell
const SL_Ptr<BREP_Shell>& BREP_Face::GetShell() const
{
	return m_pShell;
}

// Get m_pSrf
const SL_Ptr<MH_Srf>& BREP_Face::GetSrf() const
{
	return m_pSrf;
}

// Add loop
void BREP_Face::AddLoop(const SL_Ptr<BREP_Loop>& pLoop)
{
	m_vLoop.push_back(pLoop);
}

// Get m_vLoop
const BREP_LoopPtrVect& BREP_Face::GetLoops() const
{
	return m_vLoop;
}
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
#include "brep_shell.h"
#include "brep_lump.h"
#include "brep_face.h"
#include "brep_wire.h"
#include "sl_mm.h"

// The constructed shell is owned by pLump
BREP_Shell::BREP_Shell(const SL_Ptr<BREP_Lump>& pLump)
:m_pLump(pLump)
{
	if(m_pLump.GetTarget())
		m_pLump->AddShell(this);
}

// The constructed shell is owned by pLump
BREP_Shell::BREP_Shell(const SL_Ptr<BREP_Lump>& pLump, const BREP_FacePtrVect& vFace, const BREP_WirePtrVect& vWire)
:m_pLump(pLump),
m_vFace(vFace),
m_vWire(vWire)
{
	if(m_pLump.GetTarget())
		m_pLump->AddShell(this);
}

// De-constructor
BREP_Shell::~BREP_Shell(void)
{
}

// Copy the entity
BREP_Shell* BREP_Shell::Copy(const SL_Ptr<BREP_Lump>& pLump)
{
	BREP_Shell* pShell = NEW_OBJ(BREP_Shell, pLump.GetTarget())(pLump);
	if(pShell)
	{
		BREP_FacePtrVect::const_iterator it		= m_vFace.begin();
		BREP_FacePtrVect::const_iterator itEnd	= m_vFace.end();
		for(; it!=itEnd; ++it)
		{
			BREP_Face* pFace = (*it)->Copy(pShell);
			ASSERT(pFace);
			if(pFace)
				pShell->AddFace(pFace);
		}

		BREP_WirePtrVect::const_iterator itWire		= m_vWire.begin();
		BREP_WirePtrVect::const_iterator itWireEnd	= m_vWire.end();
		for(; itWire!=itWireEnd; ++itWire)
		{
			BREP_Wire* pWire = (*itWire)->Copy(pShell);
			ASSERT(pWire);
			if(pWire)
				pShell->AddWire(pWire);
		}
	}
	return pShell;
}

// Get m_pLump
const SL_Ptr<BREP_Lump>& BREP_Shell::GetLump() const
{
	return m_pLump;
}

// Add face
void BREP_Shell::AddFace(const SL_Ptr<BREP_Face>& pFace)
{
	m_vFace.push_back(pFace);
}

// Get m_vFace
const BREP_FacePtrVect& BREP_Shell::GetFaces() const
{
	return m_vFace;
}

// Add wire
void BREP_Shell::AddWire(const SL_Ptr<BREP_Wire>& pWire)
{
	m_vWire.push_back(pWire);
}

// Get m_vWire
const BREP_WirePtrVect& BREP_Shell::GetWires() const
{
	return m_vWire;
}
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
#include "brep_lump.h"
#include "brep_body.h"
#include "brep_shell.h"
#include "sl_mm.h"

BREP_Lump::BREP_Lump(const SL_Ptr<BREP_Body>& pBody)
:m_pBody(pBody)
{
	if(m_pBody.GetTarget())
		m_pBody->AddLump(this);
}

// The constructed lump is owned by pBody
BREP_Lump::BREP_Lump(const SL_Ptr<BREP_Body>& pBody, const BREP_ShellPtrVect& vShell)
:m_pBody(pBody),
m_vShell(vShell)
{
	if(m_pBody.GetTarget())
		m_pBody->AddLump(this);
}

// De-constructor
BREP_Lump::~BREP_Lump(void)
{
}

// Copy the entity
BREP_Lump* BREP_Lump::Copy(const SL_Ptr<BREP_Body>& pBody)
{
	BREP_Lump* pLump = NEW_OBJ(BREP_Lump, pBody.GetTarget())(pBody);
	if(pLump)
	{
		BREP_ShellPtrVect::const_iterator it	= m_vShell.begin();
		BREP_ShellPtrVect::const_iterator itEnd	= m_vShell.end();
		for(; it!=itEnd; ++it)
		{
			BREP_Shell* pShell = (*it)->Copy(pLump);
			ASSERT(pShell);
			if(pShell)
				pLump->AddShell(pShell);
		}
	}
	return pLump;
}

// Get m_pBody
const SL_Ptr<BREP_Body>& BREP_Lump::GetBody() const
{
	return m_pBody;
}

// Add shell
void BREP_Lump::AddShell(const SL_Ptr<BREP_Shell>& pShell)
{
	m_vShell.push_back(pShell);
}

// Get m_vShell
const BREP_ShellPtrVect& BREP_Lump::GetShells() const
{
	return m_vShell;
}
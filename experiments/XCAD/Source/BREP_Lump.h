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

class BREP_Body;
class BREP_Lump : public BREP_Entity
{
public:
	// The constructed lump is owned by pBody
	BREP_Lump(const SL_Ptr<BREP_Body>& pBody);

	// The constructed lump is owned by pBody
	BREP_Lump(const SL_Ptr<BREP_Body>& pBody, const BREP_ShellPtrVect& vShell);

	// De-constructor
	virtual ~BREP_Lump(void);

	// Copy the entity
	BREP_Lump* Copy(const SL_Ptr<BREP_Body>& pBody);

	// Get m_pBody
	const SL_Ptr<BREP_Body>& GetBody() const;

	// Add shell
	void AddShell(const SL_Ptr<BREP_Shell>& pShell);

	// Get m_vShell
	const BREP_ShellPtrVect& GetShells() const;
private:
	// Owner of the lump
	SL_Ptr<BREP_Body>	m_pBody;

	// This lump includes these shells
	BREP_ShellPtrVect	m_vShell;
};

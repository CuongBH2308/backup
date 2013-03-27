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

class BREP_Shell : public BREP_Entity
{
public:
	// The constructed shell is owned by pLump
	BREP_Shell(const SL_Ptr<BREP_Lump>& pLump);

	// The constructed shell is owned by pLump
	BREP_Shell(const SL_Ptr<BREP_Lump>& pLump, const BREP_FacePtrVect& vFace, const BREP_WirePtrVect& vWire);
	
	// De-constructor
	virtual ~BREP_Shell(void);

	// Copy the entity
	BREP_Shell* Copy(const SL_Ptr<BREP_Lump>& pLump);

	// Get m_pLump
	const SL_Ptr<BREP_Lump>& GetLump() const;

	// Add face
	void AddFace(const SL_Ptr<BREP_Face>& pFace);

	// Get m_vFace
	const BREP_FacePtrVect& GetFaces() const;

	// Add wire
	void AddWire(const SL_Ptr<BREP_Wire>& pWire);

	// Get m_vWire
	const BREP_WirePtrVect& GetWires() const;
private:
	// The owner of this shell
	SL_Ptr<BREP_Lump>	m_pLump;

	// The shell includes these faces
	BREP_FacePtrVect	m_vFace;

	// The shell includes these wires
	BREP_WirePtrVect	m_vWire;
};

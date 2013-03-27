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

class BREP_Loop : public BREP_Entity
{
public:
	// The constructed face is owned by pFace
	BREP_Loop(const SL_Ptr<BREP_Face>& pFace);

	// The constructed face is owned by pFace
	BREP_Loop(const SL_Ptr<BREP_Face>& pFace, const BREP_CoEdgePtrVect& vCoEdge);

	// De-constructor
	virtual ~BREP_Loop(void);

	// Copy the entity
	BREP_Loop* Copy(const SL_Ptr<BREP_Face>& pFace);

	// Get m_pFace
	const SL_Ptr<BREP_Face>& GetFace() const;

	// Add CoEdge 
	void AddCoEdge(const SL_Ptr<BREP_CoEdge>& pCoEdge);

	// Get m_vCoEdge
	const BREP_CoEdgePtrVect& GetCoEdges() const;
private:
	// Owner of the loop
	SL_Ptr<BREP_Face>	m_pFace;

	// The loop includes these co-edges
	BREP_CoEdgePtrVect	m_vCoEdge;
};

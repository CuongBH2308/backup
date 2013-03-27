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

class BREP_Wire : public BREP_Entity
{
public:
	// The constructed wire is owned by pEntity
	BREP_Wire(const SL_Ptr<BREP_Entity>& pEntity);

	// The constructed wire is owned by pEntity
	BREP_Wire(const SL_Ptr<BREP_Entity>& pEntity, const BREP_CoEdgePtrVect& vCoEdge);

	// De-constructor
	virtual ~BREP_Wire(void);

	// The constructed wire is copied from pWire, and it is owned by pEntity
	BREP_Wire* Copy(const SL_Ptr<BREP_Entity>& pEntity);

	// Get m_pEntity
	const SL_Ptr<BREP_Entity>& GetEntity() const;

	// Add CoEdge into m_vCoEdge
	void AddCoEdge(const SL_Ptr<BREP_CoEdge>& pCoEdge);

	// Get m_vCoEdge
	const BREP_CoEdgePtrVect& GetCoEdges() const;
private:
	// Owner of this wire
	// Can be body or shell
	SL_Ptr<BREP_Entity> m_pEntity;

	// The wire includes these co-edges
	BREP_CoEdgePtrVect	m_vCoEdge;
};

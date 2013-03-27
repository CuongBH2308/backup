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
#include "brep_coedge.h"
#include "brep_loop.h"
#include "brep_wire.h"
#include "sl_mm.h"

// The constructed CoEdge is owned by pEntity
BREP_CoEdge::BREP_CoEdge(const SL_Ptr<BREP_Entity>& pEntity)
:m_pEntity(pEntity)
{
	if(m_pEntity.GetTarget())
	{
		BREP_Loop* pLoop = dynamic_cast<BREP_Loop*>(m_pEntity.GetTarget());
		BREP_Wire* pWire = dynamic_cast<BREP_Wire*>(pEntity.GetTarget());
		if(pLoop)
			pLoop->AddCoEdge(this);
		else if(pWire)
			pWire->AddCoEdge(this);
		else
			ASSERT(0);
	}
}

// The constructed CoEdge is owned by pEntity
BREP_CoEdge::BREP_CoEdge(const SL_Ptr<BREP_Entity>& pEntity, const SL_Ptr<BREP_Edge>& pEdge)
:m_pEntity(pEntity),
m_pEdge(pEdge)
{
	if(m_pEntity.GetTarget())
	{
		BREP_Loop* pLoop = dynamic_cast<BREP_Loop*>(m_pEntity.GetTarget());
		BREP_Wire* pWire = dynamic_cast<BREP_Wire*>(pEntity.GetTarget());
		if(pLoop)
			pLoop->AddCoEdge(this);
		else if(pWire)
			pWire->AddCoEdge(this);
		else
			ASSERT(0);
	}
}

// De-constructor
BREP_CoEdge::~BREP_CoEdge(void)
{
}

// Copy the entity
BREP_CoEdge* BREP_CoEdge::Copy(const SL_Ptr<BREP_Entity>& pEntity)
{
	BREP_CoEdge* pCoEdge = NEW_OBJ(BREP_CoEdge, pEntity.GetTarget())(pEntity);
	if(pCoEdge)
		pCoEdge->SetRev(m_bRev);

	return pCoEdge;
}

// Get m_pEntity
const SL_Ptr<BREP_Entity>& BREP_CoEdge::GetEntity() const
{
	return m_pEntity;
}

// Set m_pEdge
void BREP_CoEdge::SetEdge(const SL_Ptr<BREP_Edge>& pEdge)
{
	m_pEdge = pEdge;
}

// Get m_pEdge
const SL_Ptr<BREP_Edge>& BREP_CoEdge::GetEdge() const
{
	return m_pEdge;
}

// Set reverse flag
void BREP_CoEdge::SetRev(bool bRev)
{
	m_bRev = bRev;
}

// Is reversed
bool BREP_CoEdge::GetRev() const
{
	return m_bRev;
}
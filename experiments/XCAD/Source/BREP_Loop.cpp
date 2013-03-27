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
#include "brep_loop.h"
#include "brep_coedge.h"
#include "brep_face.h"
#include "sl_mm.h"

// The constructed face is owned by pFace
BREP_Loop::BREP_Loop(const SL_Ptr<BREP_Face>& pFace)
:m_pFace(pFace)
{
}

// The constructed face is owned by pFace
BREP_Loop::BREP_Loop(const SL_Ptr<BREP_Face>& pFace, const BREP_CoEdgePtrVect& vCoEdge)
:m_pFace(pFace),
m_vCoEdge(vCoEdge)
{
}

// De-constructor
BREP_Loop::~BREP_Loop(void)
{
}

// Copy the entity
BREP_Loop* BREP_Loop::Copy(const SL_Ptr<BREP_Face>& pFace)
{
	BREP_Loop* pLoop = NEW_OBJ(BREP_Loop, pFace.GetTarget())(pFace);
	if(pLoop)
	{
		BREP_CoEdgePtrVect::const_iterator it		= m_vCoEdge.begin();
		BREP_CoEdgePtrVect::const_iterator itEnd	= m_vCoEdge.end();
		for(; it!=itEnd; ++it)
		{
			BREP_CoEdge* pCoEdge = dynamic_cast<BREP_CoEdge*>((*it)->Copy(pLoop));
			ASSERT(pCoEdge);
			if(pCoEdge)
				pLoop->AddCoEdge(pCoEdge);
		}
	}
	return pLoop;
}

// Get m_pFace
const SL_Ptr<BREP_Face>& BREP_Loop::GetFace() const
{
	return m_pFace;
}

// Add CoEdge 
void BREP_Loop::AddCoEdge(const SL_Ptr<BREP_CoEdge>& pCoEdge)
{
	m_vCoEdge.push_back(pCoEdge);
}

// Get m_vCoEdge
const BREP_CoEdgePtrVect& BREP_Loop::GetCoEdges() const
{
	return m_vCoEdge;
}
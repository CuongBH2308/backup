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
#include "brep_util.h"
#include <algorithm>
#include "brep_body.h"
#include "brep_coedge.h"
#include "brep_edge.h"
#include "brep_entity.h"
#include "brep_face.h"
#include "brep_loop.h"
#include "brep_lump.h"
#include "brep_shell.h"
#include "brep_vertex.h"
#include "brep_result.h"
#include "brep_wire.h"
#include "mh_crvline.h"
#include "mh_crvlineseg.h"
#include "mh_crvnurbs.h"
#include "mh_srfnurbs.h"
#include "sl_mm.h"

// Delete a BREP_Entity
HRESULT BREP_Util::DeleteEntity(BREP_Entity* pEntity)
{
	return S_OK;
}

// Create a vertex owned by pEdge
HRESULT BREP_Util::CreateVertex(BREP_Edge* pEdge, const MH_Point3& pt, BREP_Vertex*& pVertex)
{
	pVertex = NEW_OBJ(BREP_Vertex, pEdge)(pEdge, pt);
	if(pVertex)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create an edge owned by pCoEdge
HRESULT BREP_Util::CreateEdge(BREP_CoEdge* pCoEdge, MH_Crv* pCrv, BREP_Vertex* pVtxStart, BREP_Vertex* pVtxEnd, BREP_Edge*& pEdge)
{
	pEdge = NEW_OBJ(BREP_Edge, pCoEdge)(pCoEdge, pCrv, pVtxStart, pVtxEnd);
	if(pEdge)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create a CoEdge owned by pEntity
HRESULT BREP_Util::CreateCoEdge(BREP_Entity* pEntity, BREP_Edge* pEdge, BREP_CoEdge*& pCoEdge)
{
	pCoEdge = NEW_OBJ(BREP_CoEdge, pEntity)(pEntity, SL_Ptr<BREP_Edge>(pEdge));
	if(pCoEdge)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create a loop owned by pFace
HRESULT BREP_Util::CreateLoop(BREP_Face* pFace, const BREP_CoEdgePtrVect& vCoEdge, BREP_Loop*& pLoop)
{
	pLoop = NEW_OBJ(BREP_Loop, pFace)(pFace, vCoEdge);
	if(pLoop)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create a wire owned by pEntity
// It can be a body or shell
HRESULT BREP_Util::CreateWire(BREP_Entity* pEntity, const BREP_CoEdgePtrVect& vCoEdge, BREP_Wire*& pWire)
{
	pWire = NEW_OBJ(BREP_Wire, pEntity)(pEntity, vCoEdge);
	if(pWire)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create a face owned by pShell
HRESULT BREP_Util::CreateFace(BREP_Shell* pShell, MH_Srf* pSrf, const BREP_LoopPtrVect& vLoop, BREP_Face*& pFace)
{
	pFace = NEW_OBJ(BREP_Face, pShell)(pShell, pSrf, vLoop);
	if(pFace)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create a shell owned by pLump
HRESULT BREP_Util::CreateShell(BREP_Lump* pLump, const BREP_FacePtrVect& vFace, const BREP_WirePtrVect& vWire, BREP_Shell*& pShell)
{
	pShell = NEW_OBJ(BREP_Shell, pShell)(pLump, vFace, vWire);
	if(pShell)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create a lump owned by pBody
HRESULT BREP_Util::CreateLump(BREP_Body* pBody, const BREP_ShellPtrVect& vShell, BREP_Lump*& pLump)
{
	pLump = NEW_OBJ(BREP_Lump, pBody)(pBody, vShell);
	if(pLump)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Create an empty BREP_Body
HRESULT BREP_Util::CreateBody(BREP_Body*& pBody)
{
	pBody = NEW_OBJ2(BREP_Body)();
	if(pBody)
		return S_OK;
	return E_OUTOFMEMORY;
}

// Get edges
HRESULT BREP_Util::GetEdges(const BREP_CoEdgePtrVect& vCoEdge, BREP_EdgePtrVect& vEdge)
{
	vEdge.clear();
	BREP_CoEdgePtrVect::const_iterator it		= vCoEdge.begin();
	BREP_CoEdgePtrVect::const_iterator itEnd	= vCoEdge.end();
	for(; it!=itEnd; ++it)
	{
		SL_Ptr<BREP_Edge> pEdge = (*it)->GetEdge();
		if(std::find(vEdge.begin(), vEdge.end(), pEdge) == vEdge.end())
			vEdge.push_back(pEdge);
	}
	return S_OK;
}

// Get edges
HRESULT BREP_Util::GetEdges(BREP_Loop* pLoop, BREP_EdgePtrVect& vEdge)
{
	return GetEdges(pLoop->GetCoEdges(), vEdge);
}

// Get edges
HRESULT BREP_Util::GetEdges(BREP_Wire* pWire, BREP_EdgePtrVect& vEdge)
{
	return GetEdges(pWire->GetCoEdges(), vEdge);	
}

// Get edges
HRESULT BREP_Util::GetEdges(BREP_Face* pFace, BREP_EdgePtrVect& vEdge)
{
	HRESULT hr = S_OK;
	vEdge.clear();
	const BREP_LoopPtrVect& vLoop =	pFace->GetLoops();
	BREP_LoopPtrVect::const_iterator it		= vLoop.begin();
	BREP_LoopPtrVect::const_iterator itEnd	= vLoop.end();
	for(; it!=itEnd; ++it)
	{
		BREP_EdgePtrVect vEdgeTemp;
		hr = GetEdges((*it).GetTarget(), vEdgeTemp);
		if(FAILED(hr))
			break;
		vEdge.insert(vEdge.end(), vEdgeTemp.begin(), vEdgeTemp.end());
	}
	
	if(FAILED(hr))
		vEdge.clear();
	else
		std::unique(vEdge.begin(), vEdge.end());

	return hr;
}

// Get edges
HRESULT BREP_Util::GetEdges(BREP_Shell* pShell, BREP_EdgePtrVect& vEdge)
{
	HRESULT hr = S_OK;
	vEdge.clear();
	const BREP_FacePtrVect& vFace =	pShell->GetFaces();
	BREP_FacePtrVect::const_iterator it		= vFace.begin();
	BREP_FacePtrVect::const_iterator itEnd	= vFace.end();
	for(; it!=itEnd; ++it)
	{
		BREP_EdgePtrVect vEdgeTemp;
		hr = GetEdges((*it).GetTarget(), vEdgeTemp);
		if(FAILED(hr))
			break;
		vEdge.insert(vEdge.end(), vEdgeTemp.begin(), vEdgeTemp.end());
	}

	if(FAILED(hr))
	{
		vEdge.clear();
		return hr;
	}

	const BREP_WirePtrVect& vWire =	pShell->GetWires();
	BREP_WirePtrVect::const_iterator itWire		= vWire.begin();
	BREP_WirePtrVect::const_iterator itWireEnd	= vWire.end();
	for(; itWire!=itWireEnd; ++itWire)
	{
		BREP_EdgePtrVect vEdgeTemp;
		hr = GetEdges((*itWire).GetTarget(), vEdgeTemp);
		if(FAILED(hr))
			break;
		vEdge.insert(vEdge.end(), vEdgeTemp.begin(), vEdgeTemp.end());
	}

	if(FAILED(hr))
		vEdge.clear();
	else
		std::unique(vEdge.begin(), vEdge.end());
	return hr;
}

// Get edges
HRESULT BREP_Util::GetEdges(BREP_Lump* pLump, BREP_EdgePtrVect& vEdge)
{
	HRESULT hr = S_OK;
	vEdge.clear();
	const BREP_ShellPtrVect& vShell = pLump->GetShells();
	BREP_ShellPtrVect::const_iterator it	= vShell.begin();
	BREP_ShellPtrVect::const_iterator itEnd	= vShell.end();
	for(; it!=itEnd; ++it)
	{
		BREP_EdgePtrVect vEdgeTemp;
		hr = GetEdges((*it).GetTarget(), vEdgeTemp);
		if(FAILED(hr))
			break;
		vEdge.insert(vEdge.end(), vEdgeTemp.begin(), vEdgeTemp.end());
	}

	if(FAILED(hr))
		vEdge.clear();
	else
		std::unique(vEdge.begin(), vEdge.end());

	return hr;
}

// Get edges
HRESULT BREP_Util::GetEdges(BREP_Body* pBody, BREP_EdgePtrVect& vEdge)
{
	HRESULT hr = S_OK;
	vEdge.clear();
	const BREP_LumpPtrVect& vLump =	pBody->GetLumps();
	BREP_LumpPtrVect::const_iterator it		= vLump.begin();
	BREP_LumpPtrVect::const_iterator itEnd	= vLump.end();
	for(; it!=itEnd; ++it)
	{
		BREP_EdgePtrVect vEdgeTemp;
		hr = GetEdges((*it).GetTarget(), vEdgeTemp);
		if(FAILED(hr))
			break;
		vEdge.insert(vEdge.end(), vEdgeTemp.begin(), vEdgeTemp.end());
	}

	if(FAILED(hr))
	{
		vEdge.clear();
		return hr;
	}

	const BREP_WirePtrVect& vWire =	pBody->GetWires();
	BREP_WirePtrVect::const_iterator itWire		= vWire.begin();
	BREP_WirePtrVect::const_iterator itWireEnd	= vWire.end();
	for(; itWire!=itWireEnd; ++itWire)
	{
		BREP_EdgePtrVect vEdgeTemp;
		hr = GetEdges((*itWire).GetTarget(), vEdgeTemp);
		if(FAILED(hr))
			break;
		vEdge.insert(vEdge.end(), vEdgeTemp.begin(), vEdgeTemp.end());
	}

	if(FAILED(hr))
		vEdge.clear();
	else
		std::unique(vEdge.begin(), vEdge.end());
	return hr;
}

HRESULT BREP_Util::GetCoEdges(BREP_Loop* pLoop,	BREP_CoEdgePtrVect& vCoEdge)
{
	vCoEdge = pLoop->GetCoEdges();
	return S_OK;
}

HRESULT BREP_Util::GetCoEdges(BREP_Wire* pWire,	BREP_CoEdgePtrVect& vCoEdge)
{
	vCoEdge = pWire->GetCoEdges();
	return S_OK;
}

HRESULT BREP_Util::GetCoEdges(BREP_Face* pFace,	BREP_CoEdgePtrVect& vCoEdge)
{
	HRESULT hr = S_OK;
	vCoEdge.clear();
	const BREP_LoopPtrVect& vLoop =	pFace->GetLoops();
	BREP_LoopPtrVect::const_iterator it		= vLoop.begin();
	BREP_LoopPtrVect::const_iterator itEnd	= vLoop.end();
	for(; it!=itEnd; ++it)
	{
		BREP_CoEdgePtrVect vCoEdgeTemp;
		hr = GetCoEdges((*it).GetTarget(), vCoEdgeTemp);
		if(FAILED(hr))
			break;
		vCoEdge.insert(vCoEdge.end(), vCoEdgeTemp.begin(), vCoEdgeTemp.end());
	}

	if(FAILED(hr))
		vCoEdge.clear();
	else
		std::unique(vCoEdge.begin(), vCoEdge.end());

	return hr;
}

HRESULT BREP_Util::GetCoEdges(BREP_Shell* pShell, BREP_CoEdgePtrVect& vCoEdge)
{
	HRESULT hr = S_OK;
	vCoEdge.clear();
	const BREP_FacePtrVect& vFace =	pShell->GetFaces();
	BREP_FacePtrVect::const_iterator it		= vFace.begin();
	BREP_FacePtrVect::const_iterator itEnd	= vFace.end();
	for(; it!=itEnd; ++it)
	{
		BREP_CoEdgePtrVect vCoEdgeTemp;
		hr = GetCoEdges((*it).GetTarget(), vCoEdgeTemp);
		if(FAILED(hr))
			break;
		vCoEdge.insert(vCoEdge.end(), vCoEdgeTemp.begin(), vCoEdgeTemp.end());
	}

	if(FAILED(hr))
	{
		vCoEdge.clear();
		return hr;
	}

	const BREP_WirePtrVect& vWire =	pShell->GetWires();
	BREP_WirePtrVect::const_iterator itWire		= vWire.begin();
	BREP_WirePtrVect::const_iterator itWireEnd	= vWire.end();
	for(; itWire!=itWireEnd; ++itWire)
	{
		BREP_CoEdgePtrVect vCoEdgeTemp;
		hr = GetCoEdges((*itWire).GetTarget(), vCoEdgeTemp);
		if(FAILED(hr))
			break;
		vCoEdge.insert(vCoEdge.end(), vCoEdgeTemp.begin(), vCoEdgeTemp.end());
	}

	if(FAILED(hr))
		vCoEdge.clear();
	else
		std::unique(vCoEdge.begin(), vCoEdge.end());
	return hr;
}

HRESULT BREP_Util::GetCoEdges(BREP_Lump* pLump,	BREP_CoEdgePtrVect& vCoEdge)
{
	HRESULT hr = S_OK;
	vCoEdge.clear();
	const BREP_ShellPtrVect& vShell = pLump->GetShells();
	BREP_ShellPtrVect::const_iterator it	= vShell.begin();
	BREP_ShellPtrVect::const_iterator itEnd	= vShell.end();
	for(; it!=itEnd; ++it)
	{
		BREP_CoEdgePtrVect vCoEdgeTemp;
		hr = GetCoEdges((*it).GetTarget(), vCoEdgeTemp);
		if(FAILED(hr))
			break;
		vCoEdge.insert(vCoEdge.end(), vCoEdgeTemp.begin(), vCoEdgeTemp.end());
	}

	if(FAILED(hr))
		vCoEdge.clear();
	else
		std::unique(vCoEdge.begin(), vCoEdge.end());

	return hr;
}

HRESULT BREP_Util::GetCoEdges(BREP_Body* pBody,	BREP_CoEdgePtrVect& vCoEdge)
{
	HRESULT hr = S_OK;
	vCoEdge.clear();
	const BREP_LumpPtrVect& vLump =	pBody->GetLumps();
	BREP_LumpPtrVect::const_iterator it		= vLump.begin();
	BREP_LumpPtrVect::const_iterator itEnd	= vLump.end();
	for(; it!=itEnd; ++it)
	{
		BREP_CoEdgePtrVect vCoEdgeTemp;
		hr = GetCoEdges((*it).GetTarget(), vCoEdgeTemp);
		if(FAILED(hr))
			break;
		vCoEdge.insert(vCoEdge.end(), vCoEdgeTemp.begin(), vCoEdgeTemp.end());
	}

	if(FAILED(hr))
	{
		vCoEdge.clear();
		return hr;
	}

	const BREP_WirePtrVect& vWire =	pBody->GetWires();
	BREP_WirePtrVect::const_iterator itWire		= vWire.begin();
	BREP_WirePtrVect::const_iterator itWireEnd	= vWire.end();
	for(; itWire!=itWireEnd; ++itWire)
	{
		BREP_CoEdgePtrVect vCoEdgeTemp;
		hr = GetCoEdges((*itWire).GetTarget(), vCoEdgeTemp);
		if(FAILED(hr))
			break;
		vCoEdge.insert(vCoEdge.end(), vCoEdgeTemp.begin(), vCoEdgeTemp.end());
	}

	if(FAILED(hr))
		vCoEdge.clear();
	else
		std::unique(vCoEdge.begin(), vCoEdge.end());
	return hr;
}

// Get faces
HRESULT BREP_Util::GetFaces(BREP_Shell* pShell, BREP_FacePtrVect& vFace)
{
	vFace = pShell->GetFaces();
	return S_OK;
}

// Get faces
HRESULT BREP_Util::GetFaces(BREP_Lump* pLump, BREP_FacePtrVect& vFace)
{
	HRESULT hr = S_OK;
	vFace.clear();
	const BREP_ShellPtrVect& vShell = pLump->GetShells();
	BREP_ShellPtrVect::const_iterator it	= vShell.begin();
	BREP_ShellPtrVect::const_iterator itEnd	= vShell.end();
	for(; it!=itEnd; ++it)
	{
		BREP_FacePtrVect vFacesTemp;
		hr = GetFaces((*it).GetTarget(), vFacesTemp);
		if(FAILED(hr))
			break;
		vFace.insert(vFace.end(), vFacesTemp.begin(), vFacesTemp.end());
	}

	if(FAILED(hr))
		vFace.clear();
	else
		std::unique(vFace.begin(), vFace.end());
	return hr;	
}

// Get faces
HRESULT BREP_Util::GetFaces(BREP_Body* pBody, BREP_FacePtrVect& vFace)
{
	HRESULT hr = S_OK;
	vFace.clear();
	const BREP_LumpPtrVect& vLump = pBody->GetLumps();
	BREP_LumpPtrVect::const_iterator it		= vLump.begin();
	BREP_LumpPtrVect::const_iterator itEnd	= vLump.end();
	for(; it!=itEnd; ++it)
	{
		BREP_FacePtrVect vFacesTemp;
		hr = GetFaces((*it).GetTarget(), vFacesTemp);
		if(FAILED(hr))
			break;
		vFace.insert(vFace.end(), vFacesTemp.begin(), vFacesTemp.end());
	}

	if(FAILED(hr))
		vFace.clear();
	else
		std::unique(vFace.begin(), vFace.end());
	return hr;	
}

// Get wires
HRESULT BREP_Util::GetWires(BREP_Shell* pShell,	BREP_WirePtrVect& vWire)
{
	vWire = pShell->GetWires();
	return S_OK;
}

HRESULT BREP_Util::GetWires(BREP_Lump* pLump, BREP_WirePtrVect& vWire)
{
	HRESULT hr = S_OK;
	vWire.clear();
	const BREP_ShellPtrVect& vShell = pLump->GetShells();
	BREP_ShellPtrVect::const_iterator it	= vShell.begin();
	BREP_ShellPtrVect::const_iterator itEnd	= vShell.end();
	for(; it!=itEnd; ++it)
	{
		BREP_WirePtrVect vWireTemp;
		hr = GetWires((*it).GetTarget(), vWireTemp);
		if(FAILED(hr))
			break;
		vWire.insert(vWire.end(), vWireTemp.begin(), vWireTemp.end());
	}

	if(FAILED(hr))
		vWire.clear();
	return hr;	
}

// Get wires
HRESULT BREP_Util::GetWires(BREP_Body* pBody, BREP_WirePtrVect& vWire)
{
	HRESULT hr = S_OK;
	vWire.clear();
	const BREP_LumpPtrVect& vLump = pBody->GetLumps();
	BREP_LumpPtrVect::const_iterator it		= vLump.begin();
	BREP_LumpPtrVect::const_iterator itEnd	= vLump.end();
	for(; it!=itEnd; ++it)
	{
		BREP_WirePtrVect vWireTemp;
		hr = GetWires((*it).GetTarget(), vWireTemp);
		if(FAILED(hr))
			break;
		vWire.insert(vWire.end(), vWireTemp.begin(), vWireTemp.end());
	}

	if(FAILED(hr))
	{
		vWire.clear();
		return hr;
	}

	const BREP_WirePtrVect& vWireTemp =	pBody->GetWires();
	vWire.insert(vWire.end(), vWireTemp.begin(), vWireTemp.end());
	std::unique(vWire.begin(), vWire.end());
	return hr;	
}

// Get shells
HRESULT BREP_Util::GetShells(BREP_Lump* pLump, BREP_ShellPtrVect& vShell)
{
	vShell = pLump->GetShells();
	return S_OK;
}

// Get shells
HRESULT BREP_Util::GetShells(BREP_Body* pBody, BREP_ShellPtrVect& vShell)
{
	HRESULT hr = S_OK;
	vShell.clear();
	const BREP_LumpPtrVect& vLump = pBody->GetLumps();
	BREP_LumpPtrVect::const_iterator it		= vLump.begin();
	BREP_LumpPtrVect::const_iterator itEnd	= vLump.end();
	for(; it!=itEnd; ++it)
	{
		BREP_ShellPtrVect vShellTemp;
		hr = GetShells((*it).GetTarget(), vShellTemp);
		if(FAILED(hr))
			break;
		vShell.insert(vShell.end(), vShellTemp.begin(), vShellTemp.end());
	}

	if(FAILED(hr))
		vShell.clear();
	return hr;	
}

// Get lumps
HRESULT BREP_Util::GetLumps(BREP_Body* pBody, BREP_LumpPtrVect& vLump)
{
	vLump = pBody->GetLumps();
	return S_OK;
}

// Create a wire
// This API constructs a wire from an array of positions and an array of
// pointers to curves. If the wire is closed, set closed to TRUE, and vCrv.size() == vPt3.size().
// If the wire is open, vCrv.size() == vPt3.size()-1
// The API does not determine if the wire is self-intersecting.
HRESULT BREP_Util::BuildWire(const MH_CrvPtrVect& vCrv, const MH_Point3Vect& vPt3, BREP_Wire*& pWire)
{
	bool bClosed = (vCrv.size() == vPt3.size());

	pWire = NULL;
	HRESULT hr = CreateWire(NULL, BREP_CoEdgePtrVect(), pWire);
	if(FAILED(hr))
		goto wrapup;

	BREP_Vertex* pVertex0 = NULL;
	size_t nSize = vCrv.size();
	for(size_t n = 0; n<nSize; ++n)
	{
		// Create CoEdge and attach it to pWire
		BREP_CoEdge* pCoEdge = NULL;
		hr = CreateCoEdge(pWire, NULL, pCoEdge);
		if(FAILED(hr))
			goto wrapup;
		pWire->AddCoEdge(pCoEdge);

		// Create Edge and attach it to CoEdge
		BREP_Edge* pEdge = NULL;
		hr = CreateEdge(pCoEdge, vCrv[n].GetTarget(), NULL, NULL, pEdge);
		if(FAILED(hr))
			goto wrapup;

		// Create start vertex and attach it to Edge
		BREP_Vertex* pVertexStart	= NULL;
		hr = CreateVertex(pEdge, vPt3[n], pVertexStart);
		if(FAILED(hr))
			goto wrapup;
		pEdge->SetStartVertex(pVertexStart);
		if(n==0)
			pVertex0 = pVertexStart;

		// Create end vertex and attach it to Edge
		BREP_Vertex* pVertexEnd		= NULL;
		if(bClosed)
		{
			if(n < nSize-1)
				hr = CreateVertex(pEdge, vPt3[n+1], pVertexEnd);
			else
				pVertexEnd = pVertex0;
		}
		else
			hr = CreateVertex(pEdge, vPt3[n+1], pVertexEnd);
		if(FAILED(hr))
			goto wrapup;
		pEdge->SetEndVertex(pVertexEnd);
	}
wrapup:
	if(FAILED(hr))
		DeleteEntity(pWire);
	return hr;
}

// Is the wire closed
HRESULT BREP_Util::IsClosed(BREP_Wire* pWire, bool& bClosed)
{
	const BREP_CoEdgePtrVect& vCoEdge = pWire->GetCoEdges();
	SL_Ptr<BREP_CoEdge> pCoEdgeStart = vCoEdge.front();
	SL_Ptr<BREP_CoEdge> pCoEdgeEnd = vCoEdge.back();
	SL_Ptr<BREP_Vertex> pVertexStart;
	SL_Ptr<BREP_Vertex> pVertexEnd;

	if(!pCoEdgeStart->GetRev())
		pVertexStart = pCoEdgeStart->GetEdge()->GetStartVertex();
	else
		pVertexStart = pCoEdgeStart->GetEdge()->GetEndVertex();

	if(!pCoEdgeEnd->GetRev())
		pVertexEnd = pCoEdgeEnd->GetEdge()->GetEndVertex();
	else
		pVertexEnd = pCoEdgeEnd->GetEdge()->GetStartVertex();

	bClosed = (pVertexStart == pVertexEnd);
	return S_OK;
}

// pBody = pWire revolves around pAxis
HRESULT BREP_Util::BuildRevolve(BREP_Wire* pWire, BREP_Edge* pAxis, BREP_Body*& pBody)
{
	pBody = NULL;
	BREP_Lump*	pLump	= NULL;
	BREP_Shell* pShell	= NULL;
	BREP_Face*  pFace	= NULL;
	BREP_EdgePtrVect vEdge;
	BREP_EdgePtrVect::const_iterator it, itEnd;

	HRESULT hr = CreateBody(pBody);
	if(FAILED(hr))
		goto wrapup;
	pBody->AddWire(pWire);

	hr = CreateLump(pBody, BREP_ShellPtrVect(), pLump);
	if(FAILED(hr))
		goto wrapup;

	hr = CreateShell(pLump, BREP_FacePtrVect(), BREP_WirePtrVect(), pShell);
	if(FAILED(hr))
		goto wrapup;

	hr = GetEdges(pWire, vEdge);
	if(FAILED(hr))
		goto wrapup;

	it		= vEdge.begin();
	itEnd	= vEdge.end();
	for(; it!=itEnd; ++it)
	{
		MH_Crv* pCrvProfile = (*it)->GetCrv().GetTarget();
		if(!pCrvProfile)
		{
			hr = BREP_RLT_NO_PROFILE;
			goto wrapup;
		}

		MH_CrvNurbs* pCrvNurbs = dynamic_cast<MH_CrvNurbs*>(pCrvProfile);
		if(!pCrvNurbs)
		{
			hr = E_NOTIMPL;
			goto wrapup;
		}

		MH_Crv* pCrvPath = pAxis->GetCrv().GetTarget();
		if(!pCrvPath)
		{
			hr = BREP_RLT_NO_PATH;
			goto wrapup;
		}
		MH_SrfNurbs* pSrf = NEW_OBJ(MH_SrfNurbs, pShell)();
		if(!pSrf)
		{
			hr = E_OUTOFMEMORY;;
			goto wrapup;
		}

		MH_CrvLine crvLine;
		MH_CrvLine*		pCrvLine	= dynamic_cast<MH_CrvLine*>(pCrvPath);
		MH_CrvLineSeg*	pCrvLineSeg	= dynamic_cast<MH_CrvLineSeg*>(pCrvPath);
		if(pCrvLine)
			crvLine = *pCrvLine;
		else if(pCrvLineSeg)
			crvLine = MH_CrvLine(*pCrvLineSeg);
		else
		{
			ASSERT(0);
			hr = E_NOTIMPL;
			goto wrapup;
		}

		*pSrf = pCrvNurbs->Revolve(crvLine);
		hr = CreateFace(pShell, pSrf, BREP_LoopPtrVect(), pFace);
		if(FAILED(hr))
			goto wrapup;
	}

wrapup:
	if(FAILED(hr))
		DeleteEntity(pBody);
	return hr;
}

// Create revolve face
HRESULT BREP_Util::BuildRevolveFace(BREP_Edge* pProfile, BREP_Edge* pAxis, BREP_Shell* pShell, BREP_Face*& pFace)
{
	MH_Crv* pCrvProfile = pProfile->GetCrv().GetTarget();
	if(!pCrvProfile)
		return BREP_RLT_NO_PROFILE;

	MH_CrvNurbs* pCrvNurbs = dynamic_cast<MH_CrvNurbs*>(pCrvProfile);
	if(!pCrvNurbs)
		return E_NOTIMPL;

	MH_Crv* pCrvPath = pAxis->GetCrv().GetTarget();
	if(!pCrvPath)
		return BREP_RLT_NO_PATH;

	MH_CrvLine crvLine;
	MH_CrvLine*		pCrvLine	= dynamic_cast<MH_CrvLine*>(pCrvPath);
	MH_CrvLineSeg*	pCrvLineSeg	= dynamic_cast<MH_CrvLineSeg*>(pCrvPath);
	if(pCrvLine)
		crvLine = *pCrvLine;
	else if(pCrvLineSeg)
		crvLine = MH_CrvLine(*pCrvLineSeg);
	else
		ASSERT(0);

	MH_SrfNurbs* pSrf = NEW_OBJ(MH_SrfNurbs, pShell)();
	*pSrf = pCrvNurbs->Revolve(crvLine);
	return CreateFace(pShell, pSrf, BREP_LoopPtrVect(), pFace);
}

// Create body upon revolve face
HRESULT BREP_Util::BuildRevolveFaceBody(BREP_Edge* pProfile, BREP_Edge* pAxis, BREP_Body*& pFaceBody)
{
	pFaceBody = NULL;
	BREP_Lump*	pLump	= NULL;
	BREP_Shell* pShell	= NULL;
	BREP_Face*  pFace	= NULL;

	HRESULT hr = CreateBody(pFaceBody);
	if(FAILED(hr))
		goto wrapup;

	hr = CreateLump(pFaceBody, BREP_ShellPtrVect(), pLump);
	if(FAILED(hr))
		goto wrapup;

	hr = CreateShell(pLump, BREP_FacePtrVect(), BREP_WirePtrVect(), pShell);
	if(FAILED(hr))
		goto wrapup;

	hr = BuildRevolveFace(pProfile, pAxis, pShell, pFace);
	if(FAILED(hr))
		goto wrapup;

	pShell->AddFace(pFace);
	pLump->AddShell(pShell);
wrapup:
	return hr;
}

// The profile can be edge, face, etc
HRESULT BREP_Util::BuildRevolveBody(BREP_Entity* pProfile, BREP_Edge* pAxis, BREP_Body*& pBody)
{
	BREP_Edge* pEdge = dynamic_cast<BREP_Edge*>(pProfile);
	BREP_Wire* pWire = dynamic_cast<BREP_Wire*>(pProfile);
	BREP_Face* pFace = dynamic_cast<BREP_Face*>(pProfile);
	if(!pEdge && !pWire && !pFace)
		return BREP_RLT_NO_PROFILE;

	if(pEdge)
		return BuildRevolveFaceBody(pEdge, pAxis, pBody);
	else if(pWire)
	{
		//NEW_OBJ1()
		//BREP_EdgePtrVect vEdge;
		//HRESULT hr = GetEdges(pWire, vEdge);
		//if(FAILED(hr))
		//	return hr;
		//
		//hr = CreateBody(pBody);
		//if(FAILED(hr))
		//	return hr;

		//BREP_EdgePtrVect::const_iterator it		= vEdge.begin();
		//BREP_EdgePtrVect::const_iterator itEnd	= vEdge.end();
		//for(; it!=itEnd; ++it)
		//{
		//	BREP_Lump*	pLump	= NULL;
		//	BREP_Shell* pShell	= NULL;
		//	BREP_Face*  pFace	= NULL;

		//	HRESULT hr = CreateBody(pFaceBody);
		//	if(FAILED(hr))
		//		goto wrapup;

		//	hr = CreateLump(pFaceBody, BREP_ShellPtrVect(), pLump);
		//	if(FAILED(hr))
		//		goto wrapup;

		//	hr = CreateShell(pLump, BREP_FacePtrVect(), BREP_WirePtrVect(), pShell);
		//	if(FAILED(hr))
		//		goto wrapup;

		//	hr = BuildRevolveFace(pProfile, pAxis, pShell, pFace);
		//	if(FAILED(hr))
		//		goto wrapup;

		//	pShell->AddFace(pFace);
		//	pLump->AddShell(pShell);

		//	BuildRevolveFace((*it).GetTarget(), pAxis,  )
		//}


	}
	else if(pFace)
		return E_NOTIMPL;
	
	return E_NOTIMPL;
}

// Delete a BREP_Body
HRESULT BREP_Util::DeleteBody(BREP_Body* pBody)
{
	return S_OK;
}

// Boolean two bodies
// The two bodies are combined. 
// If the API is successful, it returns the blank body and deletes the tool body, 
HRESULT BREP_Util::Boolean(BREP_Body* pTool, BREP_Body* pBlank, EBooleanType eType)
{
	return S_OK;
}

//// Build wire body according to curves and points of the curves
//HRESULT BREP_Util::BuildWireBody(const MH_CrvPtrVect& vCrv, const MH_Point3PtrVect& vPt3, 
//								 bool bClosed, BREP_Body*& pBody)
//{
//	HRESULT hr = S_OK;
//	MH_CrvPtrVect::const_iterator itCrv, itCrvEnd;
//	pBody = NEW_OBJ2(BREP_Body)();
//	if(!pBody)
//	{
//		hr = E_OUTOFMEMORY;
//		goto wrapup;
//	}
//
//	BREP_Wire* pWire = NEW_OBJ(BREP_Wire, pBody)(pBody);
//	if(!pWire)
//	{
//		hr = E_OUTOFMEMORY;
//		goto wrapup;
//	}
//
//	itCrv		= vCrv.begin();
//	itCrvEnd	= vCrv.end();
//	for(; itCrv!=itCrvEnd; ++itCrv)
//	{
//		BREP_CoEdge* pCoEdge = NEW_OBJ(BREP_CoEdge, pBody)(pWire);
//		if(!pCoEdge)
//		{
//			hr = E_OUTOFMEMORY;
//			goto wrapup;
//		}
//
//		BREP_Edge* pEdge = NEW_OBJ(BREP_Edge, pBody)(pCoEdge);
//		if(!pEdge)
//		{
//			hr = E_OUTOFMEMORY;
//			goto wrapup;
//		}
//		pCoEdge->SetEdge(pEdge);
//		pEdge->SetCoEdge(pCoEdge);
//		pEdge->SetCrv((*itCrv)->Copy());
//	}
//wrapup:
//	if(FAILED(hr))
//	{
//		DeleteBody(pBody);
//		pBody = NULL;
//	}
//
//    return hr;
//}

// The profile can be edge, face, etc
// The path can be edge or a body that contains only one non-branched wire
HRESULT BREP_Util::BuildSweepBody(BREP_Entity* pProfile, BREP_Entity* pPath, BREP_Body*& pBody)
{
	return S_OK;
}

// The profile is an edge
// The path is an edge
HRESULT BREP_Util::BuildSweepFace(BREP_Edge* pProfile, BREP_Edge* pPath, BREP_Face*& pFace)
{
	MH_Crv* pCrvProfile = pProfile->GetCrv().GetTarget();
	if(!pCrvProfile)
		return BREP_RLT_NO_PROFILE;

	MH_Crv* pCrvPath	= pPath->GetCrv().GetTarget();
	if(!pCrvPath)
		return BREP_RLT_NO_PATH;
}

// The profile is an edge
// The axis is an edge
HRESULT BREP_Util::BuildRevolveFace(BREP_Edge* pProfile, BREP_Edge* pPath, BREP_Face*& pFace)
{
	MH_Crv* pCrvProfile = pProfile->GetCrv().GetTarget();
	if(!pCrvProfile)
		return BREP_RLT_NO_PROFILE;

	MH_CrvNurbs* pCrvNurbs = dynamic_cast<MH_CrvNurbs*>(pCrvProfile);
	if(!pCrvNurbs)
		return E_NOTIMPL;

	MH_Crv* pCrvPath = pPath->GetCrv().GetTarget();
	if(!pCrvPath)
		return BREP_RLT_NO_PATH;

	MH_CrvLine crvLine;
	MH_CrvLine*		pCrvLine	= dynamic_cast<MH_CrvLine*>(pCrvPath);
	MH_CrvLineSeg*	pCrvLineSeg	= dynamic_cast<MH_CrvLineSeg*>(pCrvPath);
	if(pCrvLine)
		crvLine = *pCrvLine;
	else if(pCrvLineSeg)
		crvLine = MH_CrvLine(*pCrvLineSeg);
	else
		ASSERT(0);

	MH_SrfNurbs srfNurbs = pCrvNurbs->Revolve(crvLine);

	return S_OK;
}


// Facet the face with tolerance
HRESULT BREP_Util::Facet(BREP_Face* pFace, float fTol, MH_SrfPolygon*& pSrfPolygon)
{
	return S_OK;
}

// Get faces from the entity
// The entity can be: body, lump, shell
HRESULT BREP_Util::GetFaces(BREP_Entity* pEntity, BREP_FacePtrVect& pvFaces)
{
	return S_OK;
}
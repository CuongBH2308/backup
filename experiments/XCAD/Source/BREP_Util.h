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
#include "brep_collect.h"
#include "mh_collect.h"
#include "mh_srf.h"

enum EBooleanType
{
	UNION, 
	INTERSECTION, 
	SUBTRACTION, 
	NONREG_UNION, 
	NONREG_INTERSECTION, 
	NONREG_SUBTRACTION
};

class BREP_Body;
class BREP_Edge;
class BREP_Entity;
class BREP_Face;
class BREP_Vertex;
class MH_SrfPolygon;
namespace BREP_Util
{
	// Delete a BREP_Entity
	HRESULT DeleteEntity(BREP_Entity* pEntity);

	// Create a vertex owned by pEdge
	HRESULT CreateVertex(BREP_Edge* pEdge, const MH_Point3& pt, BREP_Vertex*& pVertex);

	// Create an edge owned by pCoEdge
	HRESULT CreateEdge(BREP_CoEdge* pCoEdge, MH_Crv* pCrv, BREP_Vertex* pVtxStart, BREP_Vertex* pVtxEnd, BREP_Edge*& pEdge);

	// Create a CoEdge owned by pEntity
	// It can be a loop or wire
	HRESULT CreateCoEdge(BREP_Entity* pEntity, BREP_Edge* pEdge, BREP_CoEdge*& pCoEdge);

	// Create a loop owned by pFace
	HRESULT CreateLoop(BREP_Face* pFace, const BREP_CoEdgePtrVect& vCoEdge, BREP_Loop*& pLoop);

	// Create a wire owned by pEntity
	// It can be a body or shell
	HRESULT CreateWire(BREP_Entity* pEntity, const BREP_CoEdgePtrVect& vCoEdge, BREP_Wire*& pWire);

	// Create a face owned by pShell
	HRESULT CreateFace(BREP_Shell* pShell, MH_Srf* pSrf, const BREP_LoopPtrVect& vLoop, BREP_Face*& pFace);

	// Create a shell owned by pLump
	HRESULT CreateShell(BREP_Lump* pLump, const BREP_FacePtrVect& vFace, const BREP_WirePtrVect& vWire, BREP_Shell*& pShell);

	// Create a lump owned by pBody
	HRESULT CreateLump(BREP_Body* pBody, const BREP_ShellPtrVect& vShell, BREP_Lump*& pLump);

	// Create an empty BREP_Body
	HRESULT CreateBody(BREP_Body*& pBody);

	//////////////////////////////////////////////////////////////////////////
	// Functions to get edges
	//////////////////////////////////////////////////////////////////////////
	HRESULT GetEdges(const BREP_CoEdgePtrVect& vCoEdge, BREP_EdgePtrVect& vEdge);
	HRESULT GetEdges(BREP_Loop* pLoop,		BREP_EdgePtrVect& vEdge);
	HRESULT GetEdges(BREP_Wire* pWire,		BREP_EdgePtrVect& vEdge);
	HRESULT GetEdges(BREP_Face* pFace,		BREP_EdgePtrVect& vEdge);
	HRESULT GetEdges(BREP_Shell* pShell,	BREP_EdgePtrVect& vEdge);
	HRESULT GetEdges(BREP_Lump* pLump,		BREP_EdgePtrVect& vEdge);
	HRESULT GetEdges(BREP_Body* pBody,		BREP_EdgePtrVect& vEdge);

	//////////////////////////////////////////////////////////////////////////
	// Functions to get co-edges
	//////////////////////////////////////////////////////////////////////////
	HRESULT GetCoEdges(BREP_Loop* pLoop,	BREP_CoEdgePtrVect& vCoEdge);
	HRESULT GetCoEdges(BREP_Wire* pWire,	BREP_CoEdgePtrVect& vCoEdge);
	HRESULT GetCoEdges(BREP_Face* pFace,	BREP_CoEdgePtrVect& vCoEdge);
	HRESULT GetCoEdges(BREP_Shell* pShell,	BREP_CoEdgePtrVect& vCoEdge);
	HRESULT GetCoEdges(BREP_Lump* pLump,	BREP_CoEdgePtrVect& vCoEdge);
	HRESULT GetCoEdges(BREP_Body* pBody,	BREP_CoEdgePtrVect& vCoEdge);

	//////////////////////////////////////////////////////////////////////////
	// Functions to get faces
	//////////////////////////////////////////////////////////////////////////
	HRESULT GetFaces(BREP_Shell* pShell,	BREP_FacePtrVect& vFace);
	HRESULT GetFaces(BREP_Lump* pLump,		BREP_FacePtrVect& vFace);
	HRESULT GetFaces(BREP_Body* pBody,		BREP_FacePtrVect& vFace);

	//////////////////////////////////////////////////////////////////////////
	// Functions to get wire
	//////////////////////////////////////////////////////////////////////////
	HRESULT GetWires(BREP_Shell* pShell,	BREP_WirePtrVect& vWire);
	HRESULT GetWires(BREP_Lump* pLump,		BREP_WirePtrVect& vWire);
	HRESULT GetWires(BREP_Body* pBody,		BREP_WirePtrVect& vWire);

	//////////////////////////////////////////////////////////////////////////
	// Functions to get shells
	//////////////////////////////////////////////////////////////////////////
	HRESULT GetShells(BREP_Lump* pLump,		BREP_ShellPtrVect& vShell);
	HRESULT GetShells(BREP_Body* pBody,		BREP_ShellPtrVect& vShell);

	//////////////////////////////////////////////////////////////////////////
	// Functions to get lumps
	//////////////////////////////////////////////////////////////////////////
	HRESULT GetLumps(BREP_Body* pBody,		BREP_LumpPtrVect& vLump);

	// Create a wire from an array of positions and an array of
	// pointers to curves. If the wire is closed, set closed to TRUE, and vCrv.size() == vPt3.size().
	// If the wire is open, vCrv.size() == vPt3.size()-1
	// The API does not determine if the wire is self-intersecting.
	HRESULT BuildWire(const MH_CrvPtrVect& vCrv, const MH_Point3Vect& vPt3, BREP_Wire*& pWire);

	// pBody = pWire revolves around pAxis
	HRESULT BuildRevolve(BREP_Wire* pWire, BREP_Edge* pAxis, BREP_Body*& pBody);

	// Is the wire closed
	HRESULT IsClosed(BREP_Wire* pWire, bool& bClosed);




    // Create revolve face
	HRESULT BuildRevolveFace(BREP_Edge* pProfile, BREP_Edge* pAxis, BREP_Shell* pShell, BREP_Face*& pFace);

	// Create body upon revolve face
	HRESULT BuildRevolveFaceBody(BREP_Edge* pProfile, BREP_Edge* pAxis, BREP_Body*& pFaceBody);

	// The profile can be edge, face, etc
	HRESULT BuildRevolveBody(BREP_Entity* pProfile, BREP_Edge* pAxis, BREP_Body*& pBody);

    // Delete a BREP_Body
	HRESULT DeleteBody(BREP_Body* pBody);

	// Boolean two bodies
	// The two bodies are combined. 
	// If the API is successful, it returns the blank body and deletes the tool body, 
	HRESULT Boolean(BREP_Body* pTool, BREP_Body* pBlank, EBooleanType eType);

	// The profile can be edge, face, etc
	// The path can be edge or a body that contains only one non-branched wire
	HRESULT BuildSweepBody(BREP_Entity* pProfile, BREP_Entity* pPath, BREP_Body*& pBody);

	// The profile is an edge
	// The path is an edge
	HRESULT BuildSweepFace(BREP_Edge* pProfile, BREP_Edge* pPath, BREP_Face*& pFace);

	// The profile is an edge
	// The axis is an edge
	HRESULT BuildRevolveFace(BREP_Edge* pProfile, BREP_Edge* pPath, BREP_Face*& pFace);

	// Get faces from the entity
	// The entity can be: body, lump, shell
	HRESULT GetFaces(BREP_Entity* pEntity, BREP_FacePtrVect& pvFaces);

	// Facet the face with tolerance
	HRESULT Facet(BREP_Face* pFace, float fTol, MH_SrfPolygon*& pSrfPolygon);
};

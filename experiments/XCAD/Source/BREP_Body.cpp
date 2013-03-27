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
#include "brep_body.h"
#include "brep_lump.h"
#include "sl_mm.h"

#ifdef _DEBUG
#include "brep_shell.h"
#include "brep_face.h"
#include "brep_loop.h"
#include "brep_vertex.h"
#include "brep_coedge.h"
#include "brep_edge.h"

// Dump the fragment into a file
// if bRunDotty is true, then run dotty.exe
// Refer to http:www.graphviz.org/ for this tool
void BREP_Body::Dump(LPCTSTR lpFileName, BOOL bRunDotty) const
{
	CString strModuleName;
	// Get module file name: D:\XCAD8_20\Debug\XCAD.exe
	if(!::GetModuleFileName(NULL, strModuleName.GetBuffer(_MAX_PATH), _MAX_PATH))
		return;

	CString strDottyPath;
	strModuleName.ReleaseBuffer();
	strModuleName.MakeLower();
	strModuleName.TrimRight("\\xcad.exe");
	strModuleName = strModuleName.Left(strModuleName.ReverseFind(TCHAR('\\')));
	strDottyPath = strModuleName + _T("\\Graphviz\\dotty.exe");
	strModuleName= strModuleName + _T("\\Graphviz\\") + lpFileName;

	CFile file;
	if(!file.Open(strModuleName, CFile::modeCreate | CFile::modeReadWrite))
		return;

	const static CString strPrefix = "digraph G {\r\nsize =\"25,25\";\r\n";
	const static CString strSuffix = "}";
	
	CString str;

	CString strBody2Lumps;
	if(m_vLump.size() > 0)
		strBody2Lumps.Format(_T("Body%x -> { "), this);

	for(size_t nLump = 0; nLump<m_vLump.size(); ++nLump)
	{
		const BREP_ShellPtrVect& vShell = m_vLump[nLump]->GetShells();
		CString strLump2Shells;
		CString strLump;
		strLump.Format(_T("Lump%x"), m_vLump[nLump].GetTarget());
		if(vShell.size() > 0)
			strLump2Shells = strLump + _T(" -> {");

		if(nLump == m_vLump.size()-1)
			strLump += _T(" };\r\n");
		else
			strLump += _T(", ");
		strBody2Lumps += strLump;

		for(size_t nShell = 0; nShell<vShell.size(); ++nShell)
		{
			const BREP_FacePtrVect& vFace = vShell[nShell]->GetFaces();
			CString strShell2Faces;
			CString strShell;
			strShell.Format(_T("Shell%x"), vShell[nShell].GetTarget());
			if(vFace.size() > 0)
				strShell2Faces = strShell + _T(" -> {");

			if(nShell == vShell.size()-1)
				strShell += _T(" };\r\n");
			else
				strShell += _T(", ");
			strLump2Shells += strShell;

			for(size_t nFace = 0; nFace<vFace.size(); ++nFace)
			{
				const BREP_LoopPtrVect& vLoop = vFace[nFace]->GetLoops();
				CString strFace2Loops;
				CString strFace;
				strFace.Format(_T("Face%x"), vFace[nFace].GetTarget());
				if(vLoop.size() > 0)
					strFace2Loops = strFace + _T(" -> {");

				if(nFace == vFace.size()-1)
					strFace += _T(" };\r\n");
				else
					strFace += _T(", ");
				strShell2Faces += strFace;

				for(size_t nLoop = 0; nLoop<vLoop.size(); ++nLoop)
				{
					const BREP_CoEdgePtrVect& vCoEdge = vLoop[nLoop]->GetCoEdges();
					CString strLoop2CoEdges;
					CString strLoop;
					strLoop.Format(_T("Loop%x"), vLoop[nLoop].GetTarget());
					if(vCoEdge.size() > 0)
						strLoop2CoEdges = strLoop + _T(" -> {");

					if(nFace == vFace.size()-1)
						strLoop += _T(" };\r\n");
					else
						strLoop += _T(", ");
					strFace2Loops += strLoop;

					for(size_t nCoEdge = 0; nCoEdge<vCoEdge.size(); ++nCoEdge)
					{
						CString strCoEdge2Edge;
						CString strCoEdge;
						strCoEdge.Format(_T("CoEdge%x"), vCoEdge[nCoEdge].GetTarget());
						BREP_Edge* pEdge = vCoEdge[nCoEdge]->GetEdge().GetTarget();
						if(pEdge)
						{
							strCoEdge2Edge = strCoEdge + _T(" -> ");

							CString strEdge;
							strEdge.Format(_T("Edge%x"), pEdge);
							strCoEdge2Edge += strEdge + _T(";\r\n");
							CString strEdge2Verteces;			

							BREP_Vertex* pVertexStart	= pEdge->GetStartVertex().GetTarget();
							BREP_Vertex* pVertexEnd		= pEdge->GetEndVertex().GetTarget();
							if(pVertexStart || pVertexEnd)
								strEdge2Verteces = strEdge + _T(" -> { ");
							if(pVertexStart)
							{
								CString strVertex;
								if(pVertexEnd)
									strVertex.Format(_T("Vertex%x,"), pVertexStart);
								else
									strVertex.Format(_T("Vertex%x };\r\n"), pVertexStart);
								strEdge2Verteces += strVertex;
							}
							if(pVertexEnd)
							{
								CString strVertex;
								strVertex.Format(_T("Vertex%x };\r\n"), pVertexEnd);
								strEdge2Verteces += strVertex;
							}
							str += strEdge2Verteces;
						}
						str += strCoEdge2Edge;

						if(nCoEdge == vCoEdge.size()-1)
							strCoEdge += _T(" };\r\n");
						else
							strCoEdge += _T(", ");
						strLoop2CoEdges += strCoEdge;
					}
					str += strLoop2CoEdges;
				}
				str += strFace2Loops;
			}
			str += strShell2Faces;
		}
		str += strLump2Shells;
	}
	str += strBody2Lumps;

	str = strPrefix + str + strSuffix;
	file.Write(str.GetBuffer(0), str.GetLength());
	file.Close();
	str.ReleaseBuffer();

	if(bRunDotty)
	{
		CString strCmd = strDottyPath + _T(" ") + strModuleName;
		::WinExec(strCmd, SW_SHOW);
	}
}

#endif

BREP_Body::BREP_Body(void)
{
}

BREP_Body::~BREP_Body(void)
{
}

// Copy the entity
BREP_Body* BREP_Body::Copy()
{
	BREP_Body* pBody = NEW_OBJ2(BREP_Body)();
	if(pBody)
	{
		pBody->SetTransformation(m_mtxTransform);
		BREP_LumpPtrVect::const_iterator it		= m_vLump.begin();
		BREP_LumpPtrVect::const_iterator itEnd	= m_vLump.end();
		for(; it!=itEnd; ++it)
		{
			BREP_Lump* pLump = (*it)->Copy(this);
			ASSERT(pLump);
			if(pLump)
				pBody->AddLump(pLump);
		}
	}
	return pBody;
}

void BREP_Body::SetTransformation(const MH_Matrix44& mtx)
{
	m_mtxTransform = mtx;
}

const MH_Matrix44& BREP_Body::GetTransformation() const
{
	return m_mtxTransform;
}

void BREP_Body::AddLump(const SL_Ptr<BREP_Lump>& pLump)
{
	m_vLump.push_back(pLump);
}

const BREP_LumpPtrVect& BREP_Body::GetLumps() const
{
	return m_vLump;
}

void BREP_Body::AddWire(const SL_Ptr<BREP_Wire>& pWire)
{
	m_vWire.push_back(pWire);
}

const BREP_WirePtrVect& BREP_Body::GetWires() const
{
	return m_vWire;
}

// Get one point from the body
MH_Point3 BREP_Body::GetPoint() const
{
	return MH_Point3();
}
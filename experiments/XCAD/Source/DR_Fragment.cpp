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
#include "dr_fragment.h"
#include <algorithm>
#include <typeinfo.h>
#include "dr_ct.h"
#include "dr_collect.h"
#include "dr_dctstop.h"
#include "dr_dctsolver.h"
#include "dr_st.h"
#include "dr_uct.h"
#include "sl_mm.h"


// Dump the fragment into a file
// if bRunDotty is true, then run dotty.exe
// Refer to http://www.graphviz.org/ for this tool
/*
Sample:
digraph G {
size ="15,15";
DR_StPoint94801ec -> {DR_DCtStop9480188[shape=box] };
DR_StLine94802c4 -> {DR_DCtStop9480188[shape=box] };
DR_StLine948040c -> {DR_DCtStop9480188[shape=box] };
DR_StLine9480570 -> {DR_DCtStop9480188[shape=box] };
DR_StPlane94806f0 -> {DR_DCtStop9480188[shape=box] };
DR_StPlane9480898 -> {DR_DCtStop9480188[shape=box] };
DR_StPlane9480998 -> {DR_DCtStop9480188[shape=box] };
}
*/
#ifdef _DEBUG
void DR_Fragment::Dump(CString& str, const SL_Ptr<DR_Ct>& pCt) const
{
	if(!pCt.GetTarget())
		return;

	const DR_StPtrVect& vStInput = pCt->GetInputs();
	DR_StPtrVect::const_iterator it = vStInput.begin();
	DR_StPtrVect::const_iterator itEnd = vStInput.end();

	CString strClassName = typeid(*pCt.GetTarget()).name();
	strClassName.TrimLeft(_T("class "));
	CString strAddress;
	strAddress.Format(_T("%x"), pCt.GetTarget());

	CString strThisInfo;
	if(pCt->InStatus(DR_Ct::eDirty))
		strThisInfo = strClassName+strAddress+_T(" [shape=box, color=brown]");
	else
		strThisInfo = strClassName+strAddress+_T(" [shape=box]");

	for(; it!=itEnd; ++it)
	{
		if(!(*it).GetTarget())
			continue;

		strClassName = typeid(*(*it).GetTarget()).name();
		strClassName.TrimLeft(_T("class "));
		strAddress.Format(_T("%x"), (*it).GetTarget());
		CString strStInfo = strClassName+strAddress;
		str = str + strStInfo + _T(" -> {") +strThisInfo+_T("};\r\n");

		const DR_CtPtrVect& vCtAbove = (*it)->GetInputs();
		DR_CtPtrVect::const_iterator itCtAbove = vCtAbove.begin();
		DR_CtPtrVect::const_iterator itCtAboveEnd = vCtAbove.end();
		for(; itCtAbove!=itCtAboveEnd; ++itCtAbove)
		{
			const SL_Ptr<DR_Ct>& pCtAbove = (*itCtAbove);
			if(!pCtAbove.GetTarget())
				continue;

			strClassName = typeid(*pCtAbove.GetTarget()).name();
			strClassName.TrimLeft(_T("class "));
			strAddress.Format(_T("%x"), pCtAbove.GetTarget());

			if(dynamic_cast<DR_UCt*>(pCtAbove.GetTarget()))
				str = str + _T("{") + strClassName + strAddress + _T(" [shape=diamond]} -> {") + strStInfo +_T("};\r\n");
			else if(pCtAbove->InStatus(DR_Ct::eDirty))
				str = str + _T("{") + strClassName + strAddress + _T(" [shape=box, color=brown]} -> {") + strStInfo +_T("};\r\n");
			else
				str = str + _T("{") + strClassName + strAddress + _T(" [shape=box]} -> {") + strStInfo +_T("};\r\n");
			Dump(str, pCtAbove);
		}
	}
}

void DR_Fragment::Dump(LPCTSTR lpFileName, BOOL bRunDotty) const
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
	strModuleName = strModuleName.Left(strModuleName.ReverseFind(TCHAR('\\')));
	strDottyPath = strModuleName + _T("\\3p\\Graphviz\\dotty.exe");
	strModuleName= strModuleName + _T("\\3p\\Graphviz\\") + lpFileName;

	CFile file;
	if(!file.Open(strModuleName, CFile::modeCreate | CFile::modeReadWrite))
		return;

	const static CString strPrefix = "digraph G {\r\nsize =\"25,25\";\r\n";
	const static CString strSuffix = "}";
	CString str;

	Dump(str, m_pDCtStop.GetTarget());

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

DR_Fragment::DR_Fragment(void)
{
	// Create the stop state, and it will be added into the fragment automatically
	m_pDCtStop = NEW_OBJ(DR_DCtStop, this)(this);
}

DR_Fragment::~DR_Fragment(void)
{
	Delete(m_pDCtStop.GetTarget());
}

// Get stop state
SL_Ptr<DR_DCtStop> DR_Fragment::GetDCtStop() const
{
	return m_pDCtStop;
}

// Make pSt and its outputs dirty
// Then when we do the compute, just care those dirty Ct
HRESULT DR_Fragment::Dirty(const SL_Ptr<DR_St>& pSt) const
{
	HRESULT hr = S_OK;
	if(!pSt.GetTarget())
		return hr;

	// Check whether there is solver in its inputs
	const DR_CtPtrVect& vCtIn = pSt->GetInputs();
	DR_CtPtrVect::const_iterator it = vCtIn.begin();
	DR_CtPtrVect::const_iterator itEnd = vCtIn.end();
	for(; it!=itEnd; ++it)
	{
		if(!(*it).GetTarget())
			continue;

		DR_DCtSolver* pSolver = dynamic_cast<DR_DCtSolver*>((*it).GetTarget());
		if(pSolver)
			pSolver->AddStatus(DR_Ct::eDirty);
	}

	// Check its outputs
	const DR_CtPtrVect& vCtOut = pSt->GetOutputs();
	it = vCtOut.begin();
	itEnd = vCtOut.end();
	for(; it!=itEnd; ++it)
	{
		if(!(*it).GetTarget())
			continue;

		// Make the constraints dirty
		(*it)->AddStatus(DR_Ct::eDirty);
		const DR_StPtrVect& vSt = (*it)->GetOutputs();
		DR_StPtrVect::const_iterator itSt = vSt.begin();
		DR_StPtrVect::const_iterator itStEnd = vSt.end();
		for(; itSt!=itStEnd; ++itSt)
		{
			if(!(*itSt).GetTarget())
				continue;
			Dirty(*itSt);
		}
	}

	return hr;
}

// Compute the fragment from pCt
HRESULT DR_Fragment::Compute(const SL_Ptr<DR_Ct>& pCt) const
{
	HRESULT hr = S_OK;
	if(!pCt.GetTarget())
		return hr;

	// Jackie ??????
	//// Only compute the dirty constraint
	//if(!pCt->InStatus(DR_Ct::eDirty))
	//	return hr;

	// Ignore if it is an un-directed constraint
	if(dynamic_cast<DR_UCt*>(pCt.GetTarget()))
		return hr;

	const DR_StPtrVect& vStInput = pCt->GetInputs();
	DR_StPtrVect::const_iterator it = vStInput.begin();
	DR_StPtrVect::const_iterator itEnd = vStInput.end();

	for(; it!=itEnd; ++it)
	{
		if(!(*it).GetTarget())
			continue;

		const DR_CtPtrVect& vCtAbove = (*it)->GetInputs();
		DR_CtPtrVect::const_iterator itCtAbove = vCtAbove.begin();
		DR_CtPtrVect::const_iterator itCtAboveEnd = vCtAbove.end();
		for(; itCtAbove!=itCtAboveEnd; ++itCtAbove)
		{
			const SL_Ptr<DR_Ct>& pCtAbove = (*itCtAbove);
			if(!pCtAbove.GetTarget())
				continue;

			hr = Compute(pCtAbove);
			if(FAILED(hr))
			{
				ASSERT(0);
				break;
			}
		}
		if(FAILED(hr))
			break;
	}
	if(SUCCEEDED(hr))
	{
		hr = pCt->Compute();
		ASSERT(SUCCEEDED(hr));
		if(SUCCEEDED(hr))
		{
			pCt->RemoveStatus(DR_Ct::eDirty);
			pCt->AddStatus(DR_Ct::eHealthy);
		}
		else
			pCt->RemoveStatus(DR_Ct::eHealthy);
	}
	return hr;
}

// Call DR_Ct::Compute from top to down
HRESULT DR_Fragment::Compute() const
{
	if(m_pDCtStop.GetTarget())
		return Compute(m_pDCtStop.GetTarget());
	return E_FAIL;
}

// Delete pCt and its inputs
void DR_Fragment::Delete(const SL_Ptr<DR_Ct>& pCt) const
{
	if(!pCt.GetTarget())
		return;

	const DR_StPtrVect& vStInput = pCt->GetInputs();
	DR_StPtrVect::const_iterator it = vStInput.begin();
	DR_StPtrVect::const_iterator itEnd = vStInput.end();

	for(; it!=itEnd; ++it)
	{
		if(!(*it).GetTarget())
			continue;

		const DR_CtPtrVect& vCtAbove = (*it)->GetInputs();
		DR_CtPtrVect::const_iterator itCtAbove = vCtAbove.begin();
		DR_CtPtrVect::const_iterator itCtAboveEnd = vCtAbove.end();
		for(; itCtAbove!=itCtAboveEnd; ++itCtAbove)
		{
			const SL_Ptr<DR_Ct>& pCtAbove = (*itCtAbove);
			if(!pCtAbove.GetTarget())
				continue;
			Delete(pCtAbove);
		}
		DEL_OBJ((*it).GetTarget());
	}
	DEL_OBJ(pCt.GetTarget());
}
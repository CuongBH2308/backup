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
#include "dr_stsetbodywire.h"
#include "dr_stbodywire.h"
#include "brep_body.h"
#include "brep_util.h"

DR_StSetBodyWire::DR_StSetBodyWire(const SL_Ptr<DR_Fragment>& pFragment)
:DR_StSet(pFragment)
{
}

DR_StSetBodyWire::~DR_StSetBodyWire(void)
{
}

// Get combined BREP_Body
HRESULT DR_StSetBodyWire::GetBody(BREP_Body*& pBody) const
{
//	pBody = NULL;
//	HRESULT hr = BREP_Util::CreateBody(pBody);
//	ASSERT(SUCCEEDED(hr));
//	if(FAILED(hr))
//		return hr;
//
//	DR_StBodyWireVect::const_iterator it = m_vStBodyWire.begin();
//	DR_StBodyWireVect::const_iterator itEnd = m_vStBodyWire.end();
//	for(; it!=itEnd; ++it)
//	{
//		BREP_Body* pBodyTemp = NULL;
//
//		// Copy the item in the body vector
//		hr = BREP_Util::CopyBody((*it)->GetBody().GetTarget(), pBodyTemp);
//		ASSERT(SUCCEEDED(hr));
//		if(FAILED(hr))
//			goto wrapup;
//
//
//		// pBodyTemp will be deleted in this function
//		// pBody is the boolean result
//		hr = BREP_Util::Boolean(pBodyTemp, pBody, UNION);
//		ASSERT(SUCCEEDED(hr));
//		if(FAILED(hr))
//		{
//			hr = BREP_Util::DeleteBody(pBodyTemp);
//			ASSERT(SUCCEEDED(hr));
//			goto wrapup;
//		}
//	}
//wrapup:
//	if(FAILED(hr) && pBody)
//	{
//		hr = BREP_Util::DeleteBody(pBody);
//		ASSERT(SUCCEEDED(hr));
//	}
//	return hr;
	return S_OK;
}
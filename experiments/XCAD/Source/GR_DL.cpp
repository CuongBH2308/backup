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
#include "gr_dl.h"
#include <algorithm>
#include <typeinfo.h>
#include "gr_dlnode.h"
#include "gr_rrdl.h"
#include "gr_rrmanager.h"
#include "gr_dlattribtransform.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribselect.h"
#include "sl_objcreator.h"

// {A67A2248-FD9D-447c-B2DE-81D771D80E57}
IMPLEMENT_CREATOR(GR_DL, 
0xa67a2248, 0xfd9d, 0x447c, 0xb2, 0xde, 0x81, 0xd7, 0x71, 0xd8, 0xe, 0x57);

GR_DL::GR_DL(const SL_Ptr<GR_DLNode>& pParentNode, bool bIsDL)
:m_pParentNode(pParentNode),
m_bInvalid(true),
m_pRRDL(NULL)
{
	if(bIsDL)
	{
		ASSERT(m_pParentNode.GetTarget());
		m_pParentNode->AddDL(this);
	}
}

GR_DL::~GR_DL(void)
{
	if(m_pRRDL)
		DEL_OBJ(m_pRRDL);

	for(GR_DLAttribPtrVect::const_iterator it = m_vDLAttrib.begin(); it != m_vDLAttrib.end(); it++)
		DEL_OBJ((*it).GetTarget());
	m_vDLAttrib.clear();
}

// Get the type of the DL
// virtual 
GR_DL::EType GR_DL::GetType()
{
	return GR_DL::eUnKnown;
}

HRESULT GR_DL::Save(const SL_Stream& stream) const
{
	HRESULT hr = SL_Obj::Save(stream);
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	switch(m_nVersion)
	{
	case 0:
		break;
	default:
		break;
	}

	return hr;
}

HRESULT GR_DL::Load(const SL_Stream& stream)
{
	HRESULT hr = SL_Obj::Load(stream);
	ASSERT(SUCCEEDED(hr));
	if(FAILED(hr))
		return hr;

	switch(m_nVersion)
	{
	case 0:
		break;
	default:
		break;
	}
	return hr;
}

//////////////////////////////////////////////////////////////////////////
// virtual functions
//////////////////////////////////////////////////////////////////////////
// Detach this list from its parent node
// We should call this function before delete it
bool GR_DL::Detach()
{
	if(m_pParentNode.GetTarget())
		return m_pParentNode->RemoveDL(this);
	else
		return false;
}

// Invalidate the DL. We need to build the DL before render it
void GR_DL::Invalidate(bool bInvalid)
{
	m_bInvalid = bInvalid;
}

// Use GR_RR to render the display list
bool GR_DL::Render()
{
	// Use GR_RR to render the display list
	if(!m_pRRDL)
	{
		// It will be deleted at de-constructor of GR_DL
		m_pRRDL = GR_RRManager::GetRRManager()->GetRRDL(this);
	}

	if(IsInvalid())
	{
		m_pRRDL->Build();
		Invalidate(false);
	}
	return m_pRRDL->Render();
}

// Is the DL selected
// virtual 
bool GR_DL::HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
// public functions
//////////////////////////////////////////////////////////////////////////
// Get parent node
const SL_Ptr<GR_DLNode>& GR_DL::GetParent() const
{
	return m_pParentNode;
}

// Set RRDL
void GR_DL::SetRRDL(GR_RRDL* pRRDL)
{
	m_pRRDL = pRRDL;
}

// Get RRDL
GR_RRDL* GR_DL::GetRRDL() const
{
	return m_pRRDL;
}

// Push attribute
bool GR_DL::AddAttrib(SL_Ptr<GR_DLAttrib> pDLAttrib, bool bAppend)
{
	GR_DLAttribPtrVect::const_iterator it = std::find(m_vDLAttrib.begin(),
		m_vDLAttrib.end(), pDLAttrib);

	if(it == m_vDLAttrib.end())
	{
		if(bAppend)
			m_vDLAttrib.push_back(pDLAttrib);
		else
			m_vDLAttrib.insert(m_vDLAttrib.begin(), pDLAttrib);
	}

	return true;
}

// Delete an attribute
void GR_DL::DelAttrib(SL_Ptr<GR_DLAttrib> pDLAttrib)
{
	GR_DLAttribPtrVect::iterator it = std::find(m_vDLAttrib.begin(),
		m_vDLAttrib.end(), pDLAttrib);
	if(it != m_vDLAttrib.end())
	{
		delete (*it).GetTarget();
		m_vDLAttrib.erase(it);
	}
}

// Get this type of attribute
SL_Ptr<GR_DLAttrib> GR_DL::GetAttrib(const type_info& info)
{
	for(int i = (int)m_vDLAttrib.size()-1; i >=0 ; --i)
	{
		if(info == typeid(*m_vDLAttrib[i]))
			return m_vDLAttrib[i];
	}

	return NULL_PTR(GR_DLAttrib);
}

// Apply Attributes
bool GR_DL::ApplyAttrib(bool bApply) const
{
	if(bApply)
	{
		for(int i = 0; i < (int)m_vDLAttrib.size(); i++)
		{
			bool bOK = m_vDLAttrib[i]->Apply(bApply);
			ASSERT(bOK);
		}
	}
	else if(m_vDLAttrib.size()>0)
	{
		for(int i = (int)m_vDLAttrib.size()-1; i >=0 ; i--)
		{
			bool bOK = m_vDLAttrib[i]->Apply(bApply);
			ASSERT(bOK);
		}
	}

	return true;
}

// Get attributes
const GR_DLAttribPtrVect& GR_DL::GetAttribs() const
{
	return m_vDLAttrib;
}

// Is it invalid
const bool& GR_DL::IsInvalid() const
{
	return m_bInvalid;
}

// Set transformation
void GR_DL::SetTransform(const MH_Matrix44& mtx)
{
	m_mtxTransform = mtx;
}

// Get transformation
const MH_Matrix44& GR_DL::GetTransform() const
{
	return m_mtxTransform;
}

// Get net transformation
MH_Matrix44 GR_DL::GetNetTransform() const
{
	MH_Matrix44 mtx;

	if(m_pParentNode.GetTarget())
		mtx = m_pParentNode->GetNetTransform()*m_mtxTransform;
	else
		mtx = m_mtxTransform;

	return mtx;
}

// Set color
void GR_DL::SetColor(const GR_Color& clr)
{
	// Get this type of attribute
	GR_DLAttrib* pDL = GetAttrib(typeid(GR_DLAttribColor)).GetTarget();
	if(pDL)
	{
		GR_DLAttribColor* pDLAttribColor = dynamic_cast<GR_DLAttribColor*>(pDL);
		ASSERT(pDLAttribColor);
		pDLAttribColor->SetColor(clr);
	}
	else
		AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(clr));
}

// Set select status
void GR_DL::SetSelect(const GR_SelectionSet::EStatus eStatus)
{
	// Get this type of attribute
	GR_DLAttrib* pDLAttrib = GetAttrib(typeid(GR_DLAttribSelect)).GetTarget();
	if(pDLAttrib)
	{
		// If the DL is unselected, we should delete the attribute
		if(eStatus == GR_SelectionSet::eUnSel)
			DelAttrib(pDLAttrib);
		else
		{
			GR_DLAttribSelect* pDLAttribSelect = dynamic_cast<GR_DLAttribSelect*>(pDLAttrib);
			ASSERT(pDLAttribSelect);
			pDLAttribSelect->SetStatus(eStatus);
		}
	}
	else
	{
		if(eStatus != GR_SelectionSet::eUnSel)
		{
			// We should use new (not NEW_OBJ)
			GR_DLAttribSelect* pDLAttribSelect = new GR_DLAttribSelect();
			ASSERT(pDLAttribSelect);
			pDLAttribSelect->SetStatus(eStatus);

			// Should APPEND this attribute to the tail of the stack
			// to ensure it can be apply LAST
			AddAttrib(pDLAttribSelect, true);
		}
	}
}
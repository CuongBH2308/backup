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

// By using a display list, you create the object just once. 
// You can texture map it, color it, whatever you want to do. 
// You give the display list a name. Now any time I want to draw the textured / colored object on the screen, 
// all you have to do is call glCallList(*). The pre-made object will instantly appear on the screen. 
// Because the object has already built in the display list, OpenGL doesn't have to figure out how to build it. 
// It's pre-built in memory. This takes a lot of strain off your processor and allows your programs to run a lot faster!

#include "sl_obj.h"
#include "gr_collect.h"
#include "gr_dlattrib.h"
#include "gr_selectionset.h"
#include "mh_matrix44.h"
#include "sl_ptr.h"

class GR_Color;
class GR_DLNode;
class GR_RRDL;
class MH_Point3;
class MH_CrvRay;
class type_info;
class GR_DL : public SL_Obj
{
public:
	GR_DL(const SL_Ptr<GR_DLNode>& pParentNode, bool bIsDL = true);
	virtual ~GR_DL(void);

	enum EType
	{
		eUnKnown= 0,
		ePoint  = 1,
		eCrv	= 1<<1,
		eSrf	= 1<<2
	};

	// Get the type of the DL
	virtual GR_DL::EType GetType();

	// Declare the default constructor of thisCls (based on SL_Stream)
	DECLARE_CREATOR(GR_DL);

	// Save this object to the stream
	virtual HRESULT Save(const SL_Stream& stream) const;

	// Load an object from the stream
	virtual HRESULT Load(const SL_Stream& stream);

//////////////////////////////////////////////////////////////////////////
// virtual functions
//////////////////////////////////////////////////////////////////////////
	// Detach this node from its parent node
	// We should call this function before delete it
	virtual bool	Detach();

	// Invalidate the DL. We need to build the DL before render it
	virtual void	Invalidate(bool bInvalid = true);

	// Use GR_RR to render the display list
	virtual bool	Render();

	// Is the DL selected
	virtual bool	HitTest(const MH_CrvRay& ray, MH_Point3& ptHit, float fTolerance) const;

//////////////////////////////////////////////////////////////////////////
// public functions
//////////////////////////////////////////////////////////////////////////
    // Get parent node
	const SL_Ptr<GR_DLNode>&GetParent() const;

	// Set RRDL
	void					SetRRDL(GR_RRDL* pRRDL);

	// Get RRDL
	GR_RRDL*				GetRRDL() const;

	// Insert at the beginning or Push at the end
	bool					AddAttrib(SL_Ptr<GR_DLAttrib> pDLAttrib, bool bAppend = false);

	// Delete an attribute
	void					DelAttrib(SL_Ptr<GR_DLAttrib> pDLAttrib);

	// Get this type of attribute
	SL_Ptr<GR_DLAttrib>		GetAttrib(const type_info& info);

	// Apply Attributes
	bool					ApplyAttrib(bool bApply = true) const;

	// Get attributes
	const GR_DLAttribPtrVect&	GetAttribs() const;

	// Is it invalid
	const bool&				IsInvalid() const;

	// Set transformation
	void					SetTransform(const MH_Matrix44& mtx);

	// Get transformation
	const MH_Matrix44&		GetTransform() const;

	// Get net transformation
	MH_Matrix44				GetNetTransform() const;

	// Set color
	void					SetColor(const GR_Color& clr);

	// Set select status
	void					SetSelect(const GR_SelectionSet::EStatus eStatus);
private:
	GR_RRDL*				m_pRRDL;
	SL_Ptr<GR_DLNode>		m_pParentNode;
	GR_DLAttribPtrVect		m_vDLAttrib;
	MH_Matrix44				m_mtxTransform;
	bool					m_bInvalid;
};

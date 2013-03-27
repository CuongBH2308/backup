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

class FW_View;
class GR_DL;
class GR_DLAttrib;
class GR_RRDL;
class GR_RR;
class GR_RRDLAttrib;
class GR_RRManager
{
public:
	GR_RRManager(void);
	virtual ~GR_RRManager(void);

	enum ERender
	{
		eOpenGL,
		eD3D
	};

	static GR_RRManager* GetRRManager();
	
	// Delete RR
	void DeleteRR(GR_RR* pRR) const;

	// Get renderer
	GR_RR* GetRR() const;

	// Get the renderer of the DL
	GR_RRDL* GetRRDL(GR_DL* pDL) const;

	// Get the renderer of the attribute
	GR_RRDLAttrib* GetRRDLAttrib(GR_DLAttrib* pDLAttrib) const;

private:
	ERender m_eRender;
};

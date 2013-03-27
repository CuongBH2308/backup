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
#include "gr_rrdlattrib.h"
#include "gr_color.h"

class GR_DLAttribSelect;
class GR_RRDLAttribSelectOpenGL : public GR_RRDLAttrib
{
public:
	GR_RRDLAttribSelectOpenGL(GR_DLAttribSelect* pDLAttribSelect);
	virtual ~GR_RRDLAttribSelectOpenGL(void);

	// Apply this attribute
	virtual bool Apply(bool bApply);

	enum EType
	{
		ePreSelect,
		eSelect
	};

	// Set the preselect and select color
	void SetColor(EType etype, const GR_Color& clr);

private:
	GR_DLAttribSelect* m_pDLAttribSelect;

	// Preselect color
	GR_Color m_clrPreSelect;

	// Select color
	GR_Color m_clrSelect;
};

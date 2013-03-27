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
#include "gr_dlattrib.h"
#include "gr_color.h"

class GR_DLAttribColor : public GR_DLAttrib
{
public:
	GR_DLAttribColor(const GR_Color& color);
	virtual ~GR_DLAttribColor(void);

	// Set color
	void SetColor(const GR_Color& clr);

	// Get color
	const GR_Color& GetColor() const;
private:
	GR_Color m_color;
};

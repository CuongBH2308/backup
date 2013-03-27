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
#include "sl_obj.h"
#include "sl_ptr.h"

// Render GR

class GR_DL;
class GR_RRDL
{
public:
	GR_RRDL(GR_DL* pDL);
	virtual ~GR_RRDL(void);

	// Apply the attributes and call OnRender
	bool Render() const;

	// Build this display list
	virtual bool Build() = 0;

protected:
	// Render the display list
	virtual bool OnRender() const = 0;

	// Get DL
	GR_DL* GetDL() const;
private:
	GR_DL* m_pDL;
};

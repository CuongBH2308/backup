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
#include "dr_stcrvline.h"

DR_StCrvLine::DR_StCrvLine(const SL_Ptr<DR_Fragment>& pFragment, const MH_CrvLine& line)
:DR_StCrv(pFragment),
m_line(line)
{
}

DR_StCrvLine::~DR_StCrvLine(void)
{
}

// Transform this object
// virtual 
void DR_StCrvLine::Transform(const MH_Matrix44& mtx)
{
	m_line.Transform(mtx);
}

// Get curve
// virtual
MH_Crv* DR_StCrvLine::GetCrv()
{
	return &m_line;
}

// Set line
void DR_StCrvLine::SetLine(const MH_CrvLine& line)
{
	m_line = line;
}

// Get line
const MH_CrvLine& DR_StCrvLine::GetLine() const
{
	return m_line;
}
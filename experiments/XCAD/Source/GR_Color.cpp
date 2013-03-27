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
#include "gr_color.h"

GR_Color::GR_Color()
:m_fRed(0),
m_fGreen(0),
m_fBlue(0),
m_fAlpha(1)
{
}

GR_Color::GR_Color(const GR_Color& color)
{
	*this = color;
}

GR_Color::GR_Color(unsigned char red,
				   unsigned char green,
				   unsigned char blue,
				   unsigned char alpha)
:m_fRed(red/255.0f),
m_fGreen(green/255.0f),
m_fBlue(blue/255.0f),
m_fAlpha(alpha/255.0f)
{

}

GR_Color::GR_Color(float red,
				   float green,
				   float blue,
				   float alpha)
:m_fRed(red),
m_fGreen(green),
m_fBlue(blue),
m_fAlpha(alpha)
{
}

GR_Color::~GR_Color(void)
{
}

GR_Color& GR_Color::operator = (const GR_Color& color)
{
	m_fRed		= color.m_fRed;
	m_fGreen	= color.m_fGreen;
	m_fBlue		= color.m_fBlue;
	m_fAlpha	= color.m_fAlpha;
	return(*this);
}

float GR_Color::GetRed() const
{
	return m_fRed;
}

float GR_Color::GetGreen() const
{
	return m_fGreen;
}

float GR_Color::GetBlue() const
{
	return m_fBlue;
}

float GR_Color::GetAlpha() const
{
	return m_fAlpha;
}

void GR_Color::Set(float red, float green, float blue, float alpha)
{
	m_fRed		= red;
	m_fGreen	= green;
	m_fBlue		= blue;
	m_fAlpha	= alpha;
}
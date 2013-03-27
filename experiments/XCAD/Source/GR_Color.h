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

class GR_Color
{
public:
	GR_Color();
	GR_Color(const GR_Color& color);

	GR_Color(unsigned char red,
		unsigned char green,
		unsigned char blue,
		unsigned char alpha);

	GR_Color(float red,
		float green,
		float blue,
		float alpha);

	virtual ~GR_Color(void);

	GR_Color& operator = (const GR_Color& color);

	float GetRed() const;
	float GetGreen() const;
	float GetBlue() const;
	float GetAlpha() const;

	void Set(float red,
		float green,
		float blue,
		float alpha);
private:
	float m_fRed;
	float m_fGreen;
	float m_fBlue;
	float m_fAlpha;
};

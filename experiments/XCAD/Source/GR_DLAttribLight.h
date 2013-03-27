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

class GR_DLAttribLight : public GR_DLAttrib
{
public:
	// Ambient light is light that doesn¡¯t come from any particular direction. 
	// It has a source, but the rays of light have bounced around the room or scene and
	// become direction-less. Objects illuminated by ambient light are evenly lit on
	// all surfaces in all directions.
	class Ambient
	{
	public:
		Ambient():m_bValid(false){}
		Ambient(float fR, float fG, float fB, float fA = 1.0f):m_bValid(true){ m_fRGBA[0] = fR; m_fRGBA[1] = fG; m_fRGBA[2] = fB; m_fRGBA[3] = fA;}
		float m_fRGBA[4];
		bool m_bValid;
	};

	// Diffuse light comes from a particular direction but is reflected evenly off a surface. 
	// Even though the light is reflected evenly, the object surface is brighter 
	// if the light is pointed directly at the surface than if the light grazes	the surface from an angle.
	class Diffuse
	{
	public:
		Diffuse():m_bValid(false){}
		Diffuse(float fR, float fG, float fB, float fA = 1.0f):m_bValid(true){ m_fRGBA[0] = fR; m_fRGBA[1] = fG; m_fRGBA[2] = fB; m_fRGBA[3] = fA;}
		float m_fRGBA[4];
		bool m_bValid;
	};

	// Like diffuse light, specular light is directional, but it is reflected sharply and in a particular direction.
	// A highly specular light tends to cause a bright spot on the surface it shines upon, which is called the specular highlight.
	class Specular
	{
	public:
		Specular():m_bValid(false){}
		Specular(float fR, float fG, float fB, float fA = 1.0f):m_bValid(true){ m_fRGBA[0] = fR; m_fRGBA[1] = fG; m_fRGBA[2] = fB; m_fRGBA[3] = fA;}
		float m_fRGBA[4];
		bool m_bValid;
	};

	class Position
	{
	public:
		Position(){}
		Position(float x, float y, float z, float w = 1.0f){ m_fPos[0] = x; m_fPos[1] = y; m_fPos[2] = z; m_fPos[3] = w; }
		float m_fPos[4];
	};

public:
	GR_DLAttribLight(void);
	virtual ~GR_DLAttribLight(void);

	// Set component ambient
	void SetAmbient(const Ambient& ambient);

	// Get component ambient
	const Ambient&	GetAmbient() const;

	// Set component diffuse
	void SetDiffuse(const Diffuse& diffuse);

	// Get component diffuse
	const Diffuse&	GetDiffuse() const;

	// Set component specular
	void SetSpecular(const Specular& specular);

	// Get component specular
	const Specular& GetSpecular() const;

	// Set light's position
	void SetPosition(const Position& position);

	// Get light's position
	const Position& GetPosition() const;

private:
	Ambient		m_ambient;
	Diffuse		m_diffuse;
	Specular	m_specular;
	Position	m_position;
};

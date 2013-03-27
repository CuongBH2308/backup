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
#include "gr_dlattriblight.h"

GR_DLAttribLight::GR_DLAttribLight(void)
{
}

GR_DLAttribLight::~GR_DLAttribLight(void)
{
}

// Set component ambient
void GR_DLAttribLight::SetAmbient(const GR_DLAttribLight::Ambient& ambient)
{
	m_ambient = ambient;
}

// Get component ambient
const GR_DLAttribLight::Ambient& GR_DLAttribLight::GetAmbient() const
{
	return m_ambient;
}

// Set component diffuse
void GR_DLAttribLight::SetDiffuse(const GR_DLAttribLight::Diffuse& diffuse)
{
	m_diffuse = diffuse;
}

// Get component diffuse
const GR_DLAttribLight::Diffuse& GR_DLAttribLight::GetDiffuse() const
{
	return m_diffuse;
}

// Set component specular
void GR_DLAttribLight::SetSpecular(const GR_DLAttribLight::Specular& specular)
{
	m_specular = specular;
}

// Get component specular
const GR_DLAttribLight::Specular& GR_DLAttribLight::GetSpecular() const
{
	return m_specular;
}

// Set light's position
void GR_DLAttribLight::SetPosition(const GR_DLAttribLight::Position& position)
{
	m_position = position;
}

// Get light's position
const GR_DLAttribLight::Position& GR_DLAttribLight::GetPosition() const
{
	return m_position;
}
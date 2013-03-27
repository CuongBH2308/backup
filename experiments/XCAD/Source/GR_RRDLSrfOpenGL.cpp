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
#include "gr_rrdlsrfopengl.h"
#include "gr_dlattribtexture.h"
#include "gr_dlsrf.h"
#include "mh_point3.h"
#include "mh_srf.h"
#include "mh_srfpt.h"
#include "mh_util.h"

#ifdef _GLUNURBSOBJ
#include <gl/glu.h>
#include "mh_srfnurbs.h"
#include "mh_cv.h"
#endif

#ifdef _GLUNURBSOBJ
#ifdef _DEBUG
CString GR_RRDLSrfOpenGL::Dump(GLfloat* p, GLint i) const
{
	CString str;
	CString s;
	for(int j=0; j<i; j++)
	{
		s.Format(_T("%f,"), p[j]);
		str += s;
	}
	return str;
}
#endif
#endif

GR_RRDLSrfOpenGL::GR_RRDLSrfOpenGL(GR_DLSrf* pDLSrf)
:GR_RRDLOpenGL(pDLSrf),
m_pDLSrf(pDLSrf)
{
#ifdef _GLUNURBSOBJ
	if(dynamic_cast<MH_SrfNurbs*>(m_pDLSrf->GetSrf().GetTarget()))
	{
		m_pnobj = ::gluNewNurbsRenderer();
		::gluNurbsProperty(m_pnobj, GLU_SAMPLING_TOLERANCE, 50.0); 
	}
	else
		m_pnobj = NULL;
#endif
}

GR_RRDLSrfOpenGL::~GR_RRDLSrfOpenGL(void)
{
#ifdef _GLUNURBSOBJ
	if(m_pnobj)
	{
		::gluDeleteNurbsRenderer(m_pnobj);
		m_pnobj = NULL;
	}
#endif
}

// Build this display list
// virtual 
bool GR_RRDLSrfOpenGL::OnBuild()
{
	if(!m_pDLSrf)
		return false;

	const SL_Ptr<MH_Srf>& pSrf = m_pDLSrf->GetSrf();
	if(!pSrf.GetTarget())
		return false;

	if(pSrf->GetPts().size()==0)
		pSrf->Facet(MH_Util::GetTolerance());

	const MH_SrfPtVect& vPts = pSrf->GetPts();

	// Has texture
	bool bTexture = (m_pDLSrf->GetAttrib(typeid(GR_DLAttribTexture)).GetTarget() != NULL);

	::glEnable(GL_DEPTH_TEST);
	::glDepthFunc(GL_LEQUAL);

	switch(pSrf->GetFacetType())
	{
	case MH_Srf::eTriangles:
		{
			::glBegin(GL_TRIANGLES);
			size_t nFacet = vPts.size()/3;
			for(size_t n = 0; n < nFacet; ++n)
			{
				MH_Point3	pt0 = vPts[n*3].GetPoint3();
				MH_Point3	pt1 = vPts[n*3+1].GetPoint3();
				MH_Point3	pt2 = vPts[n*3+2].GetPoint3();
				MH_Vector3	vNormal = (pt1-pt0)^(pt2-pt1);
				::glNormal3f(vNormal.m_f[0], vNormal.m_f[1], vNormal.m_f[2]);

				if(bTexture)
					::glTexCoord2f(vPts[n*3].GetS(), vPts[n*3].GetT());
				::glVertex3f(pt0.m_f[0], pt0.m_f[1], pt0.m_f[2]);

				if(bTexture)
					::glTexCoord2f(vPts[n*3+1].GetS(), vPts[n*3+1].GetT());
				::glVertex3f(pt1.m_f[0], pt1.m_f[1], pt1.m_f[2]);

				if(bTexture)
					::glTexCoord2f(vPts[n*3+2].GetS(), vPts[n*3+2].GetT());
				::glVertex3f(pt2.m_f[0], pt2.m_f[1], pt2.m_f[2]);
			}
			::glEnd();
		}
		break;
	case MH_Srf::eTriangleStrip:
//		eFacetType = GL_TRIANGLE_STRIP;
		break;
	case MH_Srf::eTriangleFan:
		{
			::glBegin(GL_TRIANGLES);
			size_t nFacet = vPts.size()-2;
			MH_Point3 pt0 = vPts[0].GetPoint3();
			float s0 = vPts[0].GetS();
			float t0 = vPts[0].GetT();
			for(size_t n = 0; n < nFacet; ++n)
			{
				MH_Point3	pt1 = vPts[n+1].GetPoint3();
				MH_Point3	pt2 = vPts[n+2].GetPoint3();
				MH_Vector3	vNormal = (pt1-pt0)^(pt2-pt1);
				::glNormal3f(vNormal.m_f[0], vNormal.m_f[1], vNormal.m_f[2]);

				if(bTexture)
					::glTexCoord2f(s0, t0);
				::glVertex3f(pt0.m_f[0], pt0.m_f[1], pt0.m_f[2]);

				if(bTexture)
					::glTexCoord2f(vPts[n+1].GetS(), vPts[n+1].GetT());
				::glVertex3f(pt1.m_f[0], pt1.m_f[1], pt1.m_f[2]);

				if(bTexture)
					::glTexCoord2f(vPts[n+2].GetS(), vPts[n+2].GetT());
				::glVertex3f(pt2.m_f[0], pt2.m_f[1], pt2.m_f[2]);
			}
			::glEnd();
		}
		break;
	default:
		break;
	}

	if(pSrf->GetFacetType() != MH_Srf::eLineStrip)
	{
		//// Has texture
		//bool bTexture = (m_pDLSrf->GetAttrib(typeid(GR_DLAttribTexture)).GetTarget() != NULL);

		//::glEnable(GL_DEPTH_TEST);
		//::glDepthFunc(GL_LEQUAL);
		//::glBegin(eFacetType);



		//MH_SrfPtVect::const_iterator it		= vPts.begin();
		//MH_SrfPtVect::const_iterator itEnd	= vPts.end();
		//for(; it!=itEnd; ++it)
		//{
		//	MH_Point3 pt;
		//	pt = (*it).GetPoint3();
		//	if(bTexture)
		//		::glTexCoord2f((*it).GetS(), (*it).GetT());
		//	::glVertex3f(pt.m_f[0], pt.m_f[1], pt.m_f[2]);
		//}
		//::glEnd();

		static bool bDrawMesh = 0;
		if(bDrawMesh)
		{
			::glColor4f(1.0f,0,1.0f,0.5f);
			if(pSrf->GetFacetType() == MH_Srf::eTriangles)
			{
				size_t nNumTri = vPts.size()/3;
				for(size_t i=0; i<nNumTri; i++)
				{
					MH_Point3 pt[3];
					pt[0] = vPts[i*3].GetPoint3();
					pt[1] = vPts[i*3+1].GetPoint3();
					pt[2] = vPts[i*3+2].GetPoint3();

					::glBegin(GL_LINE_LOOP);
					::glVertex3f(pt[0].m_f[0], pt[0].m_f[1], pt[0].m_f[2]);
					::glVertex3f(pt[1].m_f[0], pt[1].m_f[1], pt[1].m_f[2]);
					::glVertex3f(pt[2].m_f[0], pt[2].m_f[1], pt[2].m_f[2]);
					::glEnd();
				}
			}
		}
	}

	return true;
}

// Render the display list
// virtual
bool GR_RRDLSrfOpenGL::OnRender() const
{
#ifdef _GLUNURBSOBJ
	MH_SrfNurbs* pSrfNurbs = dynamic_cast<MH_SrfNurbs*>(m_pDLSrf->GetSrf().GetTarget());
	if(pSrfNurbs)
	{
		CString str;
		const FloatVect& vKnotS = pSrfNurbs->GetKnotsS();
		const FloatVect& vKnotT = pSrfNurbs->GetKnotsT();
		const MH_CVVect& vCV	= pSrfNurbs->GetCVs();

		GLint sknot_count	= (GLint)vKnotS.size();
		GLint tknot_count	= (GLint)vKnotT.size();
		GLfloat *sknot		= NULL;
		GLfloat *tknot		= NULL;
		GLfloat *ctlarray	= NULL;
		if(sknot_count==0 && tknot_count==0)
			goto wrapup;

		sknot				= new GLfloat [sknot_count];
		if(!sknot)
			goto wrapup;

		tknot				= new GLfloat [tknot_count];
		if(!tknot)
			goto wrapup;

		GLint s_stride		= 4;
		GLint t_stride		= (GLint)(4*pSrfNurbs->GetCVNumS());

		size_t iCVNum		= vCV.size();
		ctlarray			= new GLfloat[4*iCVNum];
		memset(ctlarray,0,sizeof(GLfloat)*4*iCVNum);

		size_t i=0;
		for(i=0;i<iCVNum;i++)
		{
			ctlarray[i*4]  =vCV[i].m_f[0];
			ctlarray[i*4+1]=vCV[i].m_f[1];
			ctlarray[i*4+2]=vCV[i].m_f[2];
			ctlarray[i*4+3]=vCV[i].m_f[3];
		}

		for(i=0;i<vKnotS.size();i++)
			sknot[i]=vKnotS[i];

		for(i=0;i<vKnotT.size();i++)
			tknot[i]=vKnotT[i];

		::glPushAttrib(GL_TRANSFORM_BIT);
		::glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
		GLfloat clr[4];
		::glGetFloatv(GL_CURRENT_COLOR, clr);
		::glColor4f(1.0f, 1.0f, 0, 0.3f);
		::glEnable(GL_BLEND);
		::glDisable(GL_DEPTH_TEST);
		::glBlendFunc(GL_SRC_ALPHA,GL_ONE);

		::glMatrixMode(GL_MODELVIEW);
		::glMultMatrixf(&m_pDLSrf->GetTransform().Transpose()[0]);
		::gluBeginSurface(m_pnobj);
		::gluNurbsSurface(m_pnobj,
			sknot_count,
			sknot,
			tknot_count,
			tknot,
			s_stride,
			t_stride,
			ctlarray,
			(GLint)pSrfNurbs->GetOrderS(),
			(GLint)pSrfNurbs->GetOrderT(),
			GL_MAP2_VERTEX_4);
		::gluEndSurface(m_pnobj);
		::glDisable(GL_BLEND);
		::glPopAttrib();
		::glCallList(m_nList);
		::glPopAttrib();
		::glColor4f(clr[0], clr[1], clr[2], clr[3]);


#ifdef _GLUNURBSOBJ
#ifdef _DEBUG
		str = Dump(sknot, sknot_count) + _T("\n")+
			Dump(tknot, tknot_count)+ _T("\n") +
			Dump(ctlarray, (GLint)iCVNum*4);
#endif
#endif

wrapup:
		if(sknot)
			delete [] sknot;
		if(tknot)
			delete [] tknot;
		if(ctlarray)
			delete [] ctlarray;

		return true;
	}
#endif
	return GR_RRDLOpenGL::OnRender();
}
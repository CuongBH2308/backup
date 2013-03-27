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
#include "gr_dlnodecrdsys.h"
#include "gr_dlpoint.h"
#include "gr_dlcrv.h"
#include "gr_dlsrf.h"
#include "gr_dlattribcolor.h"
#include "gr_dlattribpointsize.h"
#include "gr_dlattribpointsmooth.h"
#include "gr_dlattribcurvewidth.h"
#include "gr_dlattribcurvestipple.h"
#include "gr_dlattribblend.h"
#include "gr_dlnodeworkpoint.h"
#include "gr_dlnodeworkaxis.h"
#include "gr_dlnodeworkplane.h"
#include "mh_crvline.h"
#include "mh_crvlineseg.h"
#include "mh_facet.h"
#include "mh_srfrect.h"
#include "sl_mm.h"

#define AXIS_LENGTH 2
GR_DLNodeCrdSys::GR_DLNodeCrdSys(const SL_Ptr<GR_DLNode>& pDLNode)
:GR_DLNode(pDLNode)
{
	//// Origin
	//m_pOrigin = NEW_OBJ(GR_DLNodeWorkpoint, this)(this, NEW_OBJ(MH_Point3, this)(0,0,0));
	//m_pOrigin->GetDLPoint()->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 1.0f, 1.0f)));
	//m_pOrigin->GetDLPoint()->AddAttrib(NEW_OBJ(GR_DLAttribPointSize, this)(4.0));
	//m_pOrigin->GetDLPoint()->AddAttrib(NEW_OBJ(GR_DLAttribPointSmooth, this)(false));

	//// X Axis
	//MH_CrvLineSeg* pLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(MH_Point3(0,0,0),MH_Point3(AXIS_LENGTH,0,0));
	//m_pXAxis = NEW_OBJ(GR_DLNodeWorkaxis, this)(this, pLineSeg);
	//m_pXAxis->GetDLCrv()->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 0.0f, 0.0f, 1.0f)));
	//m_pXAxis->GetDLCrv()->AddAttrib(NEW_OBJ(GR_DLAttribCurveWidth, this)(2.0f));

	//// Y Axis
	//pLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(MH_Point3(0,0,0),MH_Point3(0,AXIS_LENGTH,0));
	//m_pYAxis = NEW_OBJ(GR_DLNodeWorkaxis, this)(this, pLineSeg);
	//m_pYAxis->GetDLCrv()->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(0.0f, 1.0f, 0.0f, 1.0f)));
	//m_pYAxis->GetDLCrv()->AddAttrib(NEW_OBJ(GR_DLAttribCurveWidth, this)(2.0f));

	//// Z Axis
	//pLineSeg = NEW_OBJ(MH_CrvLineSeg, this)(MH_Point3(0,0,0),MH_Point3(0,0,AXIS_LENGTH));
	//m_pZAxis = NEW_OBJ(GR_DLNodeWorkaxis, this)(this, pLineSeg);
	//m_pZAxis->GetDLCrv()->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(0.0f, 0.0f, 1.0f, 1.0f)));
	//m_pZAxis->GetDLCrv()->AddAttrib(NEW_OBJ(GR_DLAttribCurveWidth, this)(2.0f));

	//// XY plane
	//m_pXYPlane = NEW_OBJ(GR_DLNodeWorkplane, this)(this, NEW_OBJ(MH_SrfRect, this)(MH_Point3(), MH_Vector3(0,0,1), MH_Vector3(AXIS_LENGTH/2,0,0)));
	//m_pXYPlane->GetDLSrf()->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 0.0f, 0.3f)));
	//m_pXYPlane->GetDLSrf()->AddAttrib(NEW_OBJ(GR_DLAttribBlend, this)(true));

	//// YZ plane
	//m_pYZPlane = NEW_OBJ(GR_DLNodeWorkplane, this)(this, NEW_OBJ(MH_SrfRect, this)(MH_Point3(), MH_Vector3(1,0,0), MH_Vector3(0, AXIS_LENGTH/2,0)));
	//m_pYZPlane->GetDLSrf()->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 0.0f, 0.3f)));
	//m_pYZPlane->GetDLSrf()->AddAttrib(NEW_OBJ(GR_DLAttribBlend, this)(true));

	//// XZ plane
	//m_pXZPlane = NEW_OBJ(GR_DLNodeWorkplane, this)(this, NEW_OBJ(MH_SrfRect, this)(MH_Point3(), MH_Vector3(0,-1,0), MH_Vector3(AXIS_LENGTH/2, 0, 0)));
	//m_pXZPlane->GetDLSrf()->AddAttrib(NEW_OBJ(GR_DLAttribColor, this)(GR_Color(1.0f, 1.0f, 0.0f, 0.3f)));
	//m_pXZPlane->GetDLSrf()->AddAttrib(NEW_OBJ(GR_DLAttribBlend, this)(true));
}

GR_DLNodeCrdSys::~GR_DLNodeCrdSys(void)
{
	//// Origin
	//if(m_pOrigin.GetTarget() && m_pOrigin->GetDLPoint().GetTarget() && m_pOrigin->GetDLPoint()->GetPoint().GetTarget())
	//	DEL_OBJ(m_pOrigin->GetDLPoint()->GetPoint().GetTarget());

	//// X Axis 
	//if(m_pXAxis.GetTarget() && m_pXAxis->GetDLCrv().GetTarget() && m_pXAxis->GetDLCrv()->GetCrv().GetTarget())
	//	DEL_OBJ(m_pXAxis->GetDLCrv()->GetCrv().GetTarget());

	//// Y Axis
	//if(m_pYAxis.GetTarget() && m_pYAxis->GetDLCrv().GetTarget() && m_pYAxis->GetDLCrv()->GetCrv().GetTarget())
	//	DEL_OBJ(m_pYAxis->GetDLCrv()->GetCrv().GetTarget());

	//// Z Axis
	//if(m_pZAxis.GetTarget() && m_pZAxis->GetDLCrv().GetTarget() && m_pZAxis->GetDLCrv()->GetCrv().GetTarget())
	//	DEL_OBJ(m_pZAxis->GetDLCrv()->GetCrv().GetTarget());

	//// XY plane
	//if(m_pXYPlane.GetTarget() && m_pXYPlane->GetDLSrf().GetTarget() && m_pXYPlane->GetDLSrf()->GetSrf())
	//	DEL_OBJ(m_pXYPlane->GetDLSrf()->GetSrf());

	//// YZ plane
	//if(m_pYZPlane.GetTarget() && m_pYZPlane->GetDLSrf().GetTarget() && m_pYZPlane->GetDLSrf()->GetSrf())
	//	DEL_OBJ(m_pYZPlane->GetDLSrf()->GetSrf());

	//// XZ plane
	//if(m_pXZPlane.GetTarget() && m_pXZPlane->GetDLSrf().GetTarget() && m_pXZPlane->GetDLSrf()->GetSrf())
	//	DEL_OBJ(m_pXZPlane->GetDLSrf()->GetSrf());
}

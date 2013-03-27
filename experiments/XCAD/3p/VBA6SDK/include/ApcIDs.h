/* --------------------------------------------------------------------------
 * ApcIDs.h
 *
 * This file is part of the Microsoft Applications Programability Control (APC)
 * Copyright (c) 1999, Microsoft Corporation. All Rights Reserved.
 * Information Contained Herein Is Proprietary and Confidential.
 * -------------------------------------------------------------------------- */
#ifndef __APCIDS_H__
#define __APCIDS_H__


//---------------------------------------------------------------------------
// Host
//---------------------------------------------------------------------------
#define DISPID_BEFORERUN 1
#define DISPID_AFTERRUN 2
#define DISPID_BEFOREPAUSE 3
#define DISPID_AFTERPAUSE 4
#define DISPID_BEFOREMODALDLG 5
#define DISPID_AFTERMODALDLG 6
#define DISPID_VIEWHOSTWINDOW 7
#define DISPID_PROJECTNAMECHANGE 8
#define DISPID_OPENREFERENCEDPROJECT 9
#define DISPID_SHOWHIDE 10
#define DISPID_SHOWHELP 11
#define DISPID_FINDFILE 12

//---------------------------------------------------------------------------
// Project
//---------------------------------------------------------------------------
#define DISPID_PROJECTRESET 1
#define DISPID_PROJECTSAVE 2
#define DISPID_DELETINGPROJECTITEM 3
#define DISPID_MODECHANGE 4
#define DISPID_MODULECHANGE 5
#define DISPID_ITEMNAMECHANGE 6
#define DISPID_PROCEDURE_ADD 7
#define DISPID_PROCEDURE_DELETE 8
#define DISPID_OPENPROJECTITEM 9
#define DISPID_MODULEDIRTYCHANGE 10

//---------------------------------------------------------------------------
// ProjectItem
//---------------------------------------------------------------------------
#define DISPID_PROJITEMRESET 1
#define DISPID_VIEWOBJECT 2	// view object button was pressed
#define DISPID_GOTACTIVE 3
#define DISPID_LOSTACTIVE 4

//---------------------------------------------------------------------------
// MacrosDialog
//---------------------------------------------------------------------------
#define DISPID_MACROCREATE 13

//---------------------------------------------------------------------------
// Control event dispids
//---------------------------------------------------------------------------
#define DISPID_CONTROL_ACTIVATE 1

#endif // !defined(__APCIDS_H__)


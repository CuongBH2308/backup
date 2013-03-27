/**
* Copyright (C) 2006, XXX Inc.- All Rights Reserved
*
* DevAssistantDefs.h : Export or import the API
*
* @author: vector
* 
* @date:   2006-05-08
*
*/
#ifndef _DGEXPORTS_H
#define _DGEXPORTS_H

/**
*	export/import declaration
*/
#ifdef DG_EXPORTS
#define DGEXPORTS_API __declspec(dllexport)
#else
#define DGEXPORTS_API __declspec(dllimport)
#endif

#endif
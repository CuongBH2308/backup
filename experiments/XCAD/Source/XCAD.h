#pragma once


#ifdef XCAD_EXPORT_FUNC
#define XCAD_EXPORT __declspec(dllexport)
#else
#define XCAD_EXPORT __declspec(dllimport)
#endif
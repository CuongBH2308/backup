// "Portions Copyright (C) Steve Rabin, 2000"
// %, Total, Ave, Max, Min, #, Name
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS

//#define _PROFILE

#ifdef _PROFILE
#include <windows.h>

void ProfileInit();
void ProfileBegin(const char* name);
void ProfileEnd(const char* name);
void ProfileDumpOutputToBuffer(const char* filename);

class TinyProfiler
{
public:
	TinyProfiler(const char* name):m_pName(name){ ProfileBegin(name); }
	~TinyProfiler(void){ ProfileEnd(m_pName); }
private:
	const char* m_pName;
};

#define INIT_PROFILER ProfileInit()
#define DONE_PROFILER(filename) ProfileDumpOutputToBuffer(filename)

#define BEGIN_PROFILE(samplename) ProfileBegin(samplename)
#define END_PROFILE(samplename) ProfileEnd(samplename)
#define PROFILE_SCOPE(samplename) TinyProfiler profilerInstance(samplename)

#else
#define INIT_PROFILER
#define DONE_PROFILER(filename)

#define BEGIN_PROFILE(samplename) 
#define END_PROFILE(samplename)
#define PROFILE_SCOPE(samplename)
#endif


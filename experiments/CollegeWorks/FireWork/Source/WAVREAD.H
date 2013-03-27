/*******************************************************************
 *         Advanced 3D Game Programming using DirectX 9.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * copyright (c) 2003 by Peter A Walsh and Adrian Perez
 * See license.txt for modification and distribution information
 ******************************************************************/
//-----------------------------------------------------------------------------
// File: WavRead.h
//
// Desc: Support for loading and playing Wave files using DirectSound sound
//       buffers.
//
// Copyright (c) 1999 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------
#ifndef WAVE_READ_H
#define WAVE_READ_H


#include <mmreg.h>
#include <mmsystem.h>


//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }

namespace DXSound{
	
	HRESULT ReadMMIO( HMMIO hmmioIn, MMCKINFO* pckInRIFF, WAVEFORMATEX** ppwfxInfo );
	HRESULT WaveOpenFile( CHAR* strFileName, HMMIO* phmmioIn, WAVEFORMATEX** ppwfxInfo,
		MMCKINFO* pckInRIFF );
	HRESULT WaveStartDataRead( HMMIO* phmmioIn, MMCKINFO* pckIn,
						  MMCKINFO* pckInRIFF );
	HRESULT WaveReadFile( HMMIO hmmioIn, UINT cbRead, BYTE* pbDest,
		MMCKINFO* pckIn, UINT* cbActualRead );
	
	//-----------------------------------------------------------------------------
	// Name: class CWaveSoundRead
	// Desc: A class to read in sound data from a Wave file
	//-----------------------------------------------------------------------------
	class CWaveSoundRead
	{
		
	public:
		CWaveSoundRead();
		~CWaveSoundRead();
		
		HRESULT Open( CHAR* strFilename );
		HRESULT Reset();
		HRESULT Read( UINT nSizeToRead, BYTE* pbData, UINT* pnSizeRead );
		HRESULT Close();
		
		
	public:
		WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
		HMMIO         m_hmmioIn;     // MM I/O handle for the WAVE
		MMCKINFO      m_ckIn;        // Multimedia RIFF chunk
		MMCKINFO      m_ckInRiff;    // Use in opening a WAVE file
		
		
		
	};
	
}

#endif WAVE_READ_H




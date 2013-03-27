/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 26 15:12:34 2004
 */
/* Compiler settings for D:\项目\VC故障诊断专家系统\算法库\Algorithm Com\AlgorithmCOM\AlgorithmCOM.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IBlurAlgo = {0x979F45D4,0x1C55,0x4dd7,{0x8A,0x6F,0x11,0xE7,0x4B,0x73,0x28,0x74}};


const IID LIBID_AlgorithmCOMLib = {0x38A734A2,0x445F,0x491c,{0xA1,0xA4,0x94,0x7B,0x46,0x00,0x8A,0x62}};


const CLSID CLSID_AlgorithmCOM = {0x495FA11F,0x036E,0x4b49,{0x83,0x4F,0x51,0x56,0x6E,0x89,0xD0,0x0B}};


#ifdef __cplusplus
}
#endif


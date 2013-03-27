/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Dec 09 12:05:25 2004
 */
/* Compiler settings for D:\航天部项目\源程序\fqz\Reason\Reason.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

const IID IID_IReasonCom = {0x18C466F3,0x87E0,0x44C6,{0xBA,0xF6,0xDA,0xE0,0x19,0xB1,0x60,0x16}};


const IID LIBID_REASONLib = {0x58974038,0xD997,0x4033,{0x80,0xA1,0xF7,0xA7,0x62,0x97,0x5F,0x5F}};


const CLSID CLSID_ReasonCom = {0xA962099D,0xEC3B,0x4327,{0xA3,0x4F,0xFF,0x3E,0xE5,0xAD,0xBC,0xEF}};


#ifdef __cplusplus
}
#endif


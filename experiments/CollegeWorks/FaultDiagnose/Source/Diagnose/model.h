/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Oct 23 22:07:12 2004
 */
/* Compiler settings for E:\专家系统设计\检查2\model\model.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __model_h__
#define __model_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMyCom1_FWD_DEFINED__
#define __IMyCom1_FWD_DEFINED__
typedef interface IMyCom1 IMyCom1;
#endif 	/* __IMyCom1_FWD_DEFINED__ */


#ifndef __IMyCom2_FWD_DEFINED__
#define __IMyCom2_FWD_DEFINED__
typedef interface IMyCom2 IMyCom2;
#endif 	/* __IMyCom2_FWD_DEFINED__ */


#ifndef __IBaseCom_FWD_DEFINED__
#define __IBaseCom_FWD_DEFINED__
typedef interface IBaseCom IBaseCom;
#endif 	/* __IBaseCom_FWD_DEFINED__ */


#ifndef __IMyLineCom_FWD_DEFINED__
#define __IMyLineCom_FWD_DEFINED__
typedef interface IMyLineCom IMyLineCom;
#endif 	/* __IMyLineCom_FWD_DEFINED__ */


#ifndef __IMyCom11_FWD_DEFINED__
#define __IMyCom11_FWD_DEFINED__
typedef interface IMyCom11 IMyCom11;
#endif 	/* __IMyCom11_FWD_DEFINED__ */


#ifndef __IMyCom12_FWD_DEFINED__
#define __IMyCom12_FWD_DEFINED__
typedef interface IMyCom12 IMyCom12;
#endif 	/* __IMyCom12_FWD_DEFINED__ */


#ifndef __IMyCom3_FWD_DEFINED__
#define __IMyCom3_FWD_DEFINED__
typedef interface IMyCom3 IMyCom3;
#endif 	/* __IMyCom3_FWD_DEFINED__ */


#ifndef __IMyCom4_FWD_DEFINED__
#define __IMyCom4_FWD_DEFINED__
typedef interface IMyCom4 IMyCom4;
#endif 	/* __IMyCom4_FWD_DEFINED__ */


#ifndef __MyCom1_FWD_DEFINED__
#define __MyCom1_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCom1 MyCom1;
#else
typedef struct MyCom1 MyCom1;
#endif /* __cplusplus */

#endif 	/* __MyCom1_FWD_DEFINED__ */


#ifndef __MyCom2_FWD_DEFINED__
#define __MyCom2_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCom2 MyCom2;
#else
typedef struct MyCom2 MyCom2;
#endif /* __cplusplus */

#endif 	/* __MyCom2_FWD_DEFINED__ */


#ifndef __BaseCom_FWD_DEFINED__
#define __BaseCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class BaseCom BaseCom;
#else
typedef struct BaseCom BaseCom;
#endif /* __cplusplus */

#endif 	/* __BaseCom_FWD_DEFINED__ */


#ifndef __MyLineCom_FWD_DEFINED__
#define __MyLineCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyLineCom MyLineCom;
#else
typedef struct MyLineCom MyLineCom;
#endif /* __cplusplus */

#endif 	/* __MyLineCom_FWD_DEFINED__ */


#ifndef __MyCom11_FWD_DEFINED__
#define __MyCom11_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCom11 MyCom11;
#else
typedef struct MyCom11 MyCom11;
#endif /* __cplusplus */

#endif 	/* __MyCom11_FWD_DEFINED__ */


#ifndef __MyCom12_FWD_DEFINED__
#define __MyCom12_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCom12 MyCom12;
#else
typedef struct MyCom12 MyCom12;
#endif /* __cplusplus */

#endif 	/* __MyCom12_FWD_DEFINED__ */


#ifndef __MyCom3_FWD_DEFINED__
#define __MyCom3_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCom3 MyCom3;
#else
typedef struct MyCom3 MyCom3;
#endif /* __cplusplus */

#endif 	/* __MyCom3_FWD_DEFINED__ */


#ifndef __MyCom4_FWD_DEFINED__
#define __MyCom4_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCom4 MyCom4;
#else
typedef struct MyCom4 MyCom4;
#endif /* __cplusplus */

#endif 	/* __MyCom4_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMyCom1_INTERFACE_DEFINED__
#define __IMyCom1_INTERFACE_DEFINED__

/* interface IMyCom1 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCom1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("83448C4B-4205-49F9-B7A3-150BC55FF5A4")
    IMyCom1 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCom1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyCom1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyCom1 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyCom1 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyCom1 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyCom1 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyCom1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyCom1 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IMyCom1 __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IMyCom1 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IMyCom1Vtbl;

    interface IMyCom1
    {
        CONST_VTBL struct IMyCom1Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCom1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyCom1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyCom1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyCom1_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyCom1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyCom1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyCom1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyCom1_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom1_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom1_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IMyCom1_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IMyCom1_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IMyCom1_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IMyCom1_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IMyCom1_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IMyCom1_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IMyCom1_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IMyCom1_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IMyCom1_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IMyCom1_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IMyCom1_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IMyCom1_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IMyCom1_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IMyCom1_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IMyCom1_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IMyCom1_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IMyCom1_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IMyCom1_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IMyCom1_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IMyCom1_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IMyCom1_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_Draw_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom1_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_DrawOffset_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom1_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_PtInRgn_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IMyCom1_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_SetID_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IMyCom1_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_SetName_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom1_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetIID_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IMyCom1_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetCLSID_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IMyCom1_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetTopLeft_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_SetActive_Proxy( 
    IMyCom1 __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IMyCom1_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetActive_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IMyCom1_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetRgn_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IMyCom1_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_InOtherRgn_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IMyCom1_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_InOtherRect_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IMyCom1_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_OffsetRgn_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetTopCenter_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetBottomCenter_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetLeftCenter_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetRightCenter_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_SetStartPoint_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_SetEndPoint_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom1_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetName_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom1_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetID_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IMyCom1_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_GetGrahpInfo_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom1_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom1_SetGraphInfo_Proxy( 
    IMyCom1 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom1_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyCom1_INTERFACE_DEFINED__ */


#ifndef __IMyCom2_INTERFACE_DEFINED__
#define __IMyCom2_INTERFACE_DEFINED__

/* interface IMyCom2 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCom2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B2174A73-5C8A-470F-B3C0-7C773A9529F4")
    IMyCom2 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCom2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyCom2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyCom2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyCom2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyCom2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyCom2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyCom2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyCom2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IMyCom2 __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IMyCom2 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IMyCom2Vtbl;

    interface IMyCom2
    {
        CONST_VTBL struct IMyCom2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCom2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyCom2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyCom2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyCom2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyCom2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyCom2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyCom2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyCom2_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom2_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom2_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IMyCom2_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IMyCom2_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IMyCom2_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IMyCom2_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IMyCom2_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IMyCom2_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IMyCom2_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IMyCom2_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IMyCom2_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IMyCom2_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IMyCom2_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IMyCom2_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IMyCom2_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IMyCom2_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IMyCom2_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IMyCom2_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IMyCom2_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IMyCom2_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IMyCom2_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IMyCom2_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IMyCom2_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_Draw_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom2_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_DrawOffset_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom2_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_PtInRgn_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IMyCom2_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_SetID_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IMyCom2_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_SetName_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom2_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetIID_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IMyCom2_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetCLSID_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IMyCom2_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetTopLeft_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_SetActive_Proxy( 
    IMyCom2 __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IMyCom2_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetActive_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IMyCom2_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetRgn_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IMyCom2_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_InOtherRgn_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IMyCom2_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_InOtherRect_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IMyCom2_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_OffsetRgn_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetTopCenter_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetBottomCenter_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetLeftCenter_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetRightCenter_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_SetStartPoint_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_SetEndPoint_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom2_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetName_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom2_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetID_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IMyCom2_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_GetGrahpInfo_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom2_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom2_SetGraphInfo_Proxy( 
    IMyCom2 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom2_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyCom2_INTERFACE_DEFINED__ */


#ifndef __IBaseCom_INTERFACE_DEFINED__
#define __IBaseCom_INTERFACE_DEFINED__

/* interface IBaseCom */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBaseCom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5268440E-10C8-4B0D-899C-2C747BEE9DE8")
    IBaseCom : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBaseComVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBaseCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBaseCom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBaseCom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBaseCom __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBaseCom __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBaseCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBaseCom __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IBaseCom __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IBaseCom __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IBaseCom __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IBaseCom __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IBaseCom __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IBaseCom __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IBaseComVtbl;

    interface IBaseCom
    {
        CONST_VTBL struct IBaseComVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBaseCom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBaseCom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBaseCom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBaseCom_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBaseCom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBaseCom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBaseCom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBaseCom_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IBaseCom_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IBaseCom_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IBaseCom_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IBaseCom_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IBaseCom_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IBaseCom_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IBaseCom_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IBaseCom_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IBaseCom_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IBaseCom_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IBaseCom_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IBaseCom_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IBaseCom_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IBaseCom_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IBaseCom_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IBaseCom_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IBaseCom_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IBaseCom_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IBaseCom_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IBaseCom_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IBaseCom_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IBaseCom_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IBaseCom_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_Draw_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IBaseCom_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_DrawOffset_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IBaseCom_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_PtInRgn_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IBaseCom_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_SetID_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IBaseCom_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_SetName_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IBaseCom_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetIID_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IBaseCom_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetCLSID_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IBaseCom_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetTopLeft_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_SetActive_Proxy( 
    IBaseCom __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IBaseCom_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetActive_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IBaseCom_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetRgn_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IBaseCom_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_InOtherRgn_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IBaseCom_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_InOtherRect_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IBaseCom_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_OffsetRgn_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetTopCenter_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetBottomCenter_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetLeftCenter_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetRightCenter_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_SetStartPoint_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_SetEndPoint_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IBaseCom_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetName_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IBaseCom_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetID_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IBaseCom_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_GetGrahpInfo_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IBaseCom_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IBaseCom_SetGraphInfo_Proxy( 
    IBaseCom __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IBaseCom_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBaseCom_INTERFACE_DEFINED__ */


#ifndef __IMyLineCom_INTERFACE_DEFINED__
#define __IMyLineCom_INTERFACE_DEFINED__

/* interface IMyLineCom */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyLineCom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0C226EFC-4C5F-4BC5-8905-B16625000F71")
    IMyLineCom : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyLineComVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyLineCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyLineCom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyLineCom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyLineCom __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyLineCom __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyLineCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyLineCom __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IMyLineCom __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IMyLineCom __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IMyLineComVtbl;

    interface IMyLineCom
    {
        CONST_VTBL struct IMyLineComVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyLineCom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyLineCom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyLineCom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyLineCom_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyLineCom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyLineCom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyLineCom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyLineCom_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyLineCom_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyLineCom_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IMyLineCom_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IMyLineCom_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IMyLineCom_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IMyLineCom_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IMyLineCom_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IMyLineCom_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IMyLineCom_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IMyLineCom_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IMyLineCom_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IMyLineCom_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IMyLineCom_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IMyLineCom_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IMyLineCom_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IMyLineCom_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IMyLineCom_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IMyLineCom_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IMyLineCom_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IMyLineCom_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IMyLineCom_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IMyLineCom_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IMyLineCom_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_Draw_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyLineCom_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_DrawOffset_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyLineCom_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_PtInRgn_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IMyLineCom_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_SetID_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IMyLineCom_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_SetName_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyLineCom_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetIID_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IMyLineCom_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetCLSID_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IMyLineCom_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetTopLeft_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_SetActive_Proxy( 
    IMyLineCom __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IMyLineCom_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetActive_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IMyLineCom_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetRgn_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IMyLineCom_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_InOtherRgn_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IMyLineCom_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_InOtherRect_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IMyLineCom_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_OffsetRgn_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetTopCenter_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetBottomCenter_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetLeftCenter_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetRightCenter_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_SetStartPoint_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_SetEndPoint_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyLineCom_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetName_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyLineCom_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetID_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IMyLineCom_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_GetGrahpInfo_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyLineCom_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyLineCom_SetGraphInfo_Proxy( 
    IMyLineCom __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyLineCom_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyLineCom_INTERFACE_DEFINED__ */


#ifndef __IMyCom11_INTERFACE_DEFINED__
#define __IMyCom11_INTERFACE_DEFINED__

/* interface IMyCom11 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCom11;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FA9ECDC-C6AA-4E4A-AB9D-40E9DBA986CC")
    IMyCom11 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCom11Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyCom11 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyCom11 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyCom11 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyCom11 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyCom11 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyCom11 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyCom11 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IMyCom11 __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IMyCom11 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IMyCom11Vtbl;

    interface IMyCom11
    {
        CONST_VTBL struct IMyCom11Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCom11_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyCom11_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyCom11_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyCom11_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyCom11_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyCom11_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyCom11_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyCom11_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom11_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom11_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IMyCom11_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IMyCom11_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IMyCom11_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IMyCom11_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IMyCom11_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IMyCom11_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IMyCom11_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IMyCom11_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IMyCom11_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IMyCom11_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IMyCom11_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IMyCom11_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IMyCom11_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IMyCom11_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IMyCom11_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IMyCom11_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IMyCom11_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IMyCom11_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IMyCom11_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IMyCom11_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IMyCom11_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_Draw_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom11_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_DrawOffset_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom11_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_PtInRgn_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IMyCom11_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_SetID_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IMyCom11_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_SetName_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom11_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetIID_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IMyCom11_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetCLSID_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IMyCom11_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetTopLeft_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_SetActive_Proxy( 
    IMyCom11 __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IMyCom11_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetActive_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IMyCom11_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetRgn_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IMyCom11_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_InOtherRgn_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IMyCom11_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_InOtherRect_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IMyCom11_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_OffsetRgn_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetTopCenter_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetBottomCenter_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetLeftCenter_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetRightCenter_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_SetStartPoint_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_SetEndPoint_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom11_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetName_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom11_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetID_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IMyCom11_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_GetGrahpInfo_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom11_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom11_SetGraphInfo_Proxy( 
    IMyCom11 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom11_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyCom11_INTERFACE_DEFINED__ */


#ifndef __IMyCom12_INTERFACE_DEFINED__
#define __IMyCom12_INTERFACE_DEFINED__

/* interface IMyCom12 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCom12;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B824429C-B924-4721-8080-1A8E8E3B710B")
    IMyCom12 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCom12Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyCom12 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyCom12 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyCom12 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyCom12 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyCom12 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyCom12 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyCom12 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IMyCom12 __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IMyCom12 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IMyCom12Vtbl;

    interface IMyCom12
    {
        CONST_VTBL struct IMyCom12Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCom12_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyCom12_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyCom12_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyCom12_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyCom12_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyCom12_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyCom12_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyCom12_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom12_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom12_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IMyCom12_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IMyCom12_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IMyCom12_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IMyCom12_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IMyCom12_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IMyCom12_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IMyCom12_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IMyCom12_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IMyCom12_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IMyCom12_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IMyCom12_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IMyCom12_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IMyCom12_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IMyCom12_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IMyCom12_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IMyCom12_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IMyCom12_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IMyCom12_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IMyCom12_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IMyCom12_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IMyCom12_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_Draw_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom12_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_DrawOffset_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom12_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_PtInRgn_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IMyCom12_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_SetID_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IMyCom12_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_SetName_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom12_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetIID_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IMyCom12_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetCLSID_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IMyCom12_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetTopLeft_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_SetActive_Proxy( 
    IMyCom12 __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IMyCom12_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetActive_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IMyCom12_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetRgn_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IMyCom12_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_InOtherRgn_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IMyCom12_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_InOtherRect_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IMyCom12_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_OffsetRgn_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetTopCenter_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetBottomCenter_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetLeftCenter_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetRightCenter_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_SetStartPoint_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_SetEndPoint_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom12_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetName_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom12_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetID_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IMyCom12_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_GetGrahpInfo_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom12_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom12_SetGraphInfo_Proxy( 
    IMyCom12 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom12_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyCom12_INTERFACE_DEFINED__ */


#ifndef __IMyCom3_INTERFACE_DEFINED__
#define __IMyCom3_INTERFACE_DEFINED__

/* interface IMyCom3 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCom3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DFB34E53-F59B-4245-AA73-0FBC9C099EE1")
    IMyCom3 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCom3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyCom3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyCom3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyCom3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyCom3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyCom3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyCom3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyCom3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IMyCom3 __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IMyCom3 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IMyCom3Vtbl;

    interface IMyCom3
    {
        CONST_VTBL struct IMyCom3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCom3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyCom3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyCom3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyCom3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyCom3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyCom3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyCom3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyCom3_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom3_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom3_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IMyCom3_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IMyCom3_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IMyCom3_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IMyCom3_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IMyCom3_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IMyCom3_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IMyCom3_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IMyCom3_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IMyCom3_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IMyCom3_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IMyCom3_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IMyCom3_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IMyCom3_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IMyCom3_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IMyCom3_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IMyCom3_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IMyCom3_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IMyCom3_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IMyCom3_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IMyCom3_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IMyCom3_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_Draw_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom3_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_DrawOffset_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom3_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_PtInRgn_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IMyCom3_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_SetID_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IMyCom3_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_SetName_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom3_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetIID_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IMyCom3_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetCLSID_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IMyCom3_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetTopLeft_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_SetActive_Proxy( 
    IMyCom3 __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IMyCom3_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetActive_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IMyCom3_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetRgn_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IMyCom3_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_InOtherRgn_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IMyCom3_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_InOtherRect_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IMyCom3_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_OffsetRgn_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetTopCenter_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetBottomCenter_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetLeftCenter_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetRightCenter_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_SetStartPoint_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_SetEndPoint_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom3_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetName_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom3_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetID_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IMyCom3_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_GetGrahpInfo_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom3_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom3_SetGraphInfo_Proxy( 
    IMyCom3 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom3_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyCom3_INTERFACE_DEFINED__ */


#ifndef __IMyCom4_INTERFACE_DEFINED__
#define __IMyCom4_INTERFACE_DEFINED__

/* interface IMyCom4 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyCom4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("26236F0A-E679-490B-9737-0F1D0452E550")
    IMyCom4 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw( 
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DrawOffset( 
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PtInRgn( 
            unsigned long point,
            unsigned long return_flag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetID( 
            unsigned long ID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetIID( 
            unsigned long pIID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCLSID( 
            unsigned long pCLSID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopLeft( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActive( 
            BOOL IsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActive( 
            unsigned long pIsActive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRgn( 
            unsigned long pRgn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRgn( 
            unsigned long pRgn,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InOtherRect( 
            unsigned long pRect,
            unsigned long pFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OffsetRgn( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTopCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBottomCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLeftCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRightCenter( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEndPoint( 
            unsigned long pPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetName( 
            unsigned long pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetID( 
            unsigned long pID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetGrahpInfo( 
            unsigned long pGraphInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetGraphInfo( 
            unsigned long pGraphInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyCom4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMyCom4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMyCom4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMyCom4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMyCom4 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMyCom4 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMyCom4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMyCom4 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pStartPoint,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DrawOffset )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long m_pDC,
            unsigned long m_pOffset,
            double m_Scale,
            unsigned long m_pGraphInfo,
            BOOL scale_flag,
            BOOL m_active_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PtInRgn )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long point,
            unsigned long return_flag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetID )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long ID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIID )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pIID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCLSID )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pCLSID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopLeft )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActive )( 
            IMyCom4 __RPC_FAR * This,
            BOOL IsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetActive )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pIsActive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRgn )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pRgn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRgn )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pRgn,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InOtherRect )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pRect,
            unsigned long pFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OffsetRgn )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTopCenter )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBottomCenter )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeftCenter )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRightCenter )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartPoint )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEndPoint )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGrahpInfo )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphInfo )( 
            IMyCom4 __RPC_FAR * This,
            unsigned long pGraphInfo);
        
        END_INTERFACE
    } IMyCom4Vtbl;

    interface IMyCom4
    {
        CONST_VTBL struct IMyCom4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyCom4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyCom4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyCom4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyCom4_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMyCom4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMyCom4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMyCom4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMyCom4_Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> Draw(This,m_pDC,m_pStartPoint,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom4_DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)	\
    (This)->lpVtbl -> DrawOffset(This,m_pDC,m_pOffset,m_Scale,m_pGraphInfo,scale_flag,m_active_flag)

#define IMyCom4_PtInRgn(This,point,return_flag)	\
    (This)->lpVtbl -> PtInRgn(This,point,return_flag)

#define IMyCom4_SetID(This,ID)	\
    (This)->lpVtbl -> SetID(This,ID)

#define IMyCom4_SetName(This,pName)	\
    (This)->lpVtbl -> SetName(This,pName)

#define IMyCom4_GetIID(This,pIID)	\
    (This)->lpVtbl -> GetIID(This,pIID)

#define IMyCom4_GetCLSID(This,pCLSID)	\
    (This)->lpVtbl -> GetCLSID(This,pCLSID)

#define IMyCom4_GetTopLeft(This,pPoint)	\
    (This)->lpVtbl -> GetTopLeft(This,pPoint)

#define IMyCom4_SetActive(This,IsActive)	\
    (This)->lpVtbl -> SetActive(This,IsActive)

#define IMyCom4_GetActive(This,pIsActive)	\
    (This)->lpVtbl -> GetActive(This,pIsActive)

#define IMyCom4_GetRgn(This,pRgn)	\
    (This)->lpVtbl -> GetRgn(This,pRgn)

#define IMyCom4_InOtherRgn(This,pRgn,pFlag)	\
    (This)->lpVtbl -> InOtherRgn(This,pRgn,pFlag)

#define IMyCom4_InOtherRect(This,pRect,pFlag)	\
    (This)->lpVtbl -> InOtherRect(This,pRect,pFlag)

#define IMyCom4_OffsetRgn(This,pPoint)	\
    (This)->lpVtbl -> OffsetRgn(This,pPoint)

#define IMyCom4_GetTopCenter(This,pPoint)	\
    (This)->lpVtbl -> GetTopCenter(This,pPoint)

#define IMyCom4_GetBottomCenter(This,pPoint)	\
    (This)->lpVtbl -> GetBottomCenter(This,pPoint)

#define IMyCom4_GetLeftCenter(This,pPoint)	\
    (This)->lpVtbl -> GetLeftCenter(This,pPoint)

#define IMyCom4_GetRightCenter(This,pPoint)	\
    (This)->lpVtbl -> GetRightCenter(This,pPoint)

#define IMyCom4_SetStartPoint(This,pPoint)	\
    (This)->lpVtbl -> SetStartPoint(This,pPoint)

#define IMyCom4_SetEndPoint(This,pPoint)	\
    (This)->lpVtbl -> SetEndPoint(This,pPoint)

#define IMyCom4_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IMyCom4_GetID(This,pID)	\
    (This)->lpVtbl -> GetID(This,pID)

#define IMyCom4_GetGrahpInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> GetGrahpInfo(This,pGraphInfo)

#define IMyCom4_SetGraphInfo(This,pGraphInfo)	\
    (This)->lpVtbl -> SetGraphInfo(This,pGraphInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_Draw_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pStartPoint,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom4_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_DrawOffset_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long m_pDC,
    unsigned long m_pOffset,
    double m_Scale,
    unsigned long m_pGraphInfo,
    BOOL scale_flag,
    BOOL m_active_flag);


void __RPC_STUB IMyCom4_DrawOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_PtInRgn_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long point,
    unsigned long return_flag);


void __RPC_STUB IMyCom4_PtInRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_SetID_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long ID);


void __RPC_STUB IMyCom4_SetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_SetName_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom4_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetIID_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pIID);


void __RPC_STUB IMyCom4_GetIID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetCLSID_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pCLSID);


void __RPC_STUB IMyCom4_GetCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetTopLeft_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_GetTopLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_SetActive_Proxy( 
    IMyCom4 __RPC_FAR * This,
    BOOL IsActive);


void __RPC_STUB IMyCom4_SetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetActive_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pIsActive);


void __RPC_STUB IMyCom4_GetActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetRgn_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pRgn);


void __RPC_STUB IMyCom4_GetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_InOtherRgn_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pRgn,
    unsigned long pFlag);


void __RPC_STUB IMyCom4_InOtherRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_InOtherRect_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pRect,
    unsigned long pFlag);


void __RPC_STUB IMyCom4_InOtherRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_OffsetRgn_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_OffsetRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetTopCenter_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_GetTopCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetBottomCenter_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_GetBottomCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetLeftCenter_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_GetLeftCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetRightCenter_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_GetRightCenter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_SetStartPoint_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_SetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_SetEndPoint_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pPoint);


void __RPC_STUB IMyCom4_SetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetName_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pName);


void __RPC_STUB IMyCom4_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetID_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pID);


void __RPC_STUB IMyCom4_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_GetGrahpInfo_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom4_GetGrahpInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMyCom4_SetGraphInfo_Proxy( 
    IMyCom4 __RPC_FAR * This,
    unsigned long pGraphInfo);


void __RPC_STUB IMyCom4_SetGraphInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyCom4_INTERFACE_DEFINED__ */



#ifndef __MODELLib_LIBRARY_DEFINED__
#define __MODELLib_LIBRARY_DEFINED__

/* library MODELLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MODELLib;

EXTERN_C const CLSID CLSID_MyCom1;

#ifdef __cplusplus

class DECLSPEC_UUID("A919B7F3-BDA5-47B0-ACBE-98BC32B95F3D")
MyCom1;
#endif

EXTERN_C const CLSID CLSID_MyCom2;

#ifdef __cplusplus

class DECLSPEC_UUID("259749C5-9B08-4EBA-8DDC-3421062B7EDD")
MyCom2;
#endif

EXTERN_C const CLSID CLSID_BaseCom;

#ifdef __cplusplus

class DECLSPEC_UUID("C6073E4D-0EB3-4DF5-9EDE-DCD36C016F0D")
BaseCom;
#endif

EXTERN_C const CLSID CLSID_MyLineCom;

#ifdef __cplusplus

class DECLSPEC_UUID("ACAC9EF9-6AFE-474C-BAF8-FD50CA753506")
MyLineCom;
#endif

EXTERN_C const CLSID CLSID_MyCom11;

#ifdef __cplusplus

class DECLSPEC_UUID("6A9F0237-1711-4C01-8FE1-F1D3E4883BF2")
MyCom11;
#endif

EXTERN_C const CLSID CLSID_MyCom12;

#ifdef __cplusplus

class DECLSPEC_UUID("C7C71AD5-6442-4940-935C-043FA9C4B9B2")
MyCom12;
#endif

EXTERN_C const CLSID CLSID_MyCom3;

#ifdef __cplusplus

class DECLSPEC_UUID("ECCA26C4-6050-47ED-AE13-C05977A3EF1F")
MyCom3;
#endif

EXTERN_C const CLSID CLSID_MyCom4;

#ifdef __cplusplus

class DECLSPEC_UUID("54EB1DA3-9783-406C-9B2A-7070F155BAD4")
MyCom4;
#endif
#endif /* __MODELLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

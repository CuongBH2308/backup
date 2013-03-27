/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 26 15:12:34 2004
 */
/* Compiler settings for D:\项目\VC故障诊断专家系统\算法库\Algorithm Com\AlgorithmCOM\AlgorithmCOM.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __AlgorithmCOM_h__
#define __AlgorithmCOM_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IBlurAlgo_FWD_DEFINED__
#define __IBlurAlgo_FWD_DEFINED__
typedef interface IBlurAlgo IBlurAlgo;
#endif 	/* __IBlurAlgo_FWD_DEFINED__ */


#ifndef __AlgorithmCOM_FWD_DEFINED__
#define __AlgorithmCOM_FWD_DEFINED__

#ifdef __cplusplus
typedef class AlgorithmCOM AlgorithmCOM;
#else
typedef struct AlgorithmCOM AlgorithmCOM;
#endif /* __cplusplus */

#endif 	/* __AlgorithmCOM_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBlurAlgo_INTERFACE_DEFINED__
#define __IBlurAlgo_INTERFACE_DEFINED__

/* interface IBlurAlgo */
/* [unique][dual][object][helpstring][uuid] */ 


EXTERN_C const IID IID_IBlurAlgo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("979F45D4-1C55-4dd7-8A6F-11E74B732874")
    IBlurAlgo : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetZhengTaiParameters( 
            /* [in] */ double k,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ZhengTaiFun( 
            /* [in] */ double x,
            /* [retval][out] */ double __RPC_FAR *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetSanJiaoParameters( 
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SanJiaoFun( 
            double x,
            /* [retval][out] */ double __RPC_FAR *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetTiXingParameters( 
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double d,
            /* [in] */ double e,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TiXingFun( 
            double x,
            /* [retval][out] */ double __RPC_FAR *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetAscZhengTaiParameters( 
            /* [in] */ double k,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AscZhengTaiFun( 
            /* [in] */ double x,
            /* [retval][out] */ double __RPC_FAR *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetDescZhengTaiParameters( 
            /* [in] */ double k,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DescZhengTaiFun( 
            /* [in] */ double x,
            /* [retval][out] */ double __RPC_FAR *presult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBlurAlgoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBlurAlgo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBlurAlgo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBlurAlgo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetZhengTaiParameters )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double k,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ZhengTaiFun )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double x,
            /* [retval][out] */ double __RPC_FAR *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSanJiaoParameters )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SanJiaoFun )( 
            IBlurAlgo __RPC_FAR * This,
            double x,
            /* [retval][out] */ double __RPC_FAR *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTiXingParameters )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double d,
            /* [in] */ double e,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TiXingFun )( 
            IBlurAlgo __RPC_FAR * This,
            double x,
            /* [retval][out] */ double __RPC_FAR *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAscZhengTaiParameters )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double k,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AscZhengTaiFun )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double x,
            /* [retval][out] */ double __RPC_FAR *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDescZhengTaiParameters )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double k,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DescZhengTaiFun )( 
            IBlurAlgo __RPC_FAR * This,
            /* [in] */ double x,
            /* [retval][out] */ double __RPC_FAR *presult);
        
        END_INTERFACE
    } IBlurAlgoVtbl;

    interface IBlurAlgo
    {
        CONST_VTBL struct IBlurAlgoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBlurAlgo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBlurAlgo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBlurAlgo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBlurAlgo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBlurAlgo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBlurAlgo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBlurAlgo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBlurAlgo_SetZhengTaiParameters(This,k,a)	\
    (This)->lpVtbl -> SetZhengTaiParameters(This,k,a)

#define IBlurAlgo_ZhengTaiFun(This,x,presult)	\
    (This)->lpVtbl -> ZhengTaiFun(This,x,presult)

#define IBlurAlgo_SetSanJiaoParameters(This,b,c,a)	\
    (This)->lpVtbl -> SetSanJiaoParameters(This,b,c,a)

#define IBlurAlgo_SanJiaoFun(This,x,presult)	\
    (This)->lpVtbl -> SanJiaoFun(This,x,presult)

#define IBlurAlgo_SetTiXingParameters(This,b,c,d,e,a)	\
    (This)->lpVtbl -> SetTiXingParameters(This,b,c,d,e,a)

#define IBlurAlgo_TiXingFun(This,x,presult)	\
    (This)->lpVtbl -> TiXingFun(This,x,presult)

#define IBlurAlgo_SetAscZhengTaiParameters(This,k,a)	\
    (This)->lpVtbl -> SetAscZhengTaiParameters(This,k,a)

#define IBlurAlgo_AscZhengTaiFun(This,x,presult)	\
    (This)->lpVtbl -> AscZhengTaiFun(This,x,presult)

#define IBlurAlgo_SetDescZhengTaiParameters(This,k,a)	\
    (This)->lpVtbl -> SetDescZhengTaiParameters(This,k,a)

#define IBlurAlgo_DescZhengTaiFun(This,x,presult)	\
    (This)->lpVtbl -> DescZhengTaiFun(This,x,presult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_SetZhengTaiParameters_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double k,
    /* [in] */ double a);


void __RPC_STUB IBlurAlgo_SetZhengTaiParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_ZhengTaiFun_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double x,
    /* [retval][out] */ double __RPC_FAR *presult);


void __RPC_STUB IBlurAlgo_ZhengTaiFun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_SetSanJiaoParameters_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double b,
    /* [in] */ double c,
    /* [in] */ double a);


void __RPC_STUB IBlurAlgo_SetSanJiaoParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_SanJiaoFun_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    double x,
    /* [retval][out] */ double __RPC_FAR *presult);


void __RPC_STUB IBlurAlgo_SanJiaoFun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_SetTiXingParameters_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double b,
    /* [in] */ double c,
    /* [in] */ double d,
    /* [in] */ double e,
    /* [in] */ double a);


void __RPC_STUB IBlurAlgo_SetTiXingParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_TiXingFun_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    double x,
    /* [retval][out] */ double __RPC_FAR *presult);


void __RPC_STUB IBlurAlgo_TiXingFun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_SetAscZhengTaiParameters_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double k,
    /* [in] */ double a);


void __RPC_STUB IBlurAlgo_SetAscZhengTaiParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_AscZhengTaiFun_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double x,
    /* [retval][out] */ double __RPC_FAR *presult);


void __RPC_STUB IBlurAlgo_AscZhengTaiFun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_SetDescZhengTaiParameters_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double k,
    /* [in] */ double a);


void __RPC_STUB IBlurAlgo_SetDescZhengTaiParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBlurAlgo_DescZhengTaiFun_Proxy( 
    IBlurAlgo __RPC_FAR * This,
    /* [in] */ double x,
    /* [retval][out] */ double __RPC_FAR *presult);


void __RPC_STUB IBlurAlgo_DescZhengTaiFun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBlurAlgo_INTERFACE_DEFINED__ */



#ifndef __AlgorithmCOMLib_LIBRARY_DEFINED__
#define __AlgorithmCOMLib_LIBRARY_DEFINED__

/* library AlgorithmCOMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AlgorithmCOMLib;

EXTERN_C const CLSID CLSID_AlgorithmCOM;

#ifdef __cplusplus

class DECLSPEC_UUID("495FA11F-036E-4b49-834F-51566E89D00B")
AlgorithmCOM;
#endif
#endif /* __AlgorithmCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

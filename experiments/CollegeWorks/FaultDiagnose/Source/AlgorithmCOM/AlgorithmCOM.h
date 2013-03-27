

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sat Dec 05 12:31:15 2009
 */
/* Compiler settings for .\AlgorithmCOM.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
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

#ifdef __cplusplus
extern "C"{
#endif 


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
            /* [retval][out] */ double *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetSanJiaoParameters( 
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SanJiaoFun( 
            double x,
            /* [retval][out] */ double *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetTiXingParameters( 
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double d,
            /* [in] */ double e,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TiXingFun( 
            double x,
            /* [retval][out] */ double *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetAscZhengTaiParameters( 
            /* [in] */ double k,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AscZhengTaiFun( 
            /* [in] */ double x,
            /* [retval][out] */ double *presult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetDescZhengTaiParameters( 
            /* [in] */ double k,
            /* [in] */ double a) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DescZhengTaiFun( 
            /* [in] */ double x,
            /* [retval][out] */ double *presult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBlurAlgoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBlurAlgo * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBlurAlgo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBlurAlgo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBlurAlgo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBlurAlgo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBlurAlgo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBlurAlgo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetZhengTaiParameters )( 
            IBlurAlgo * This,
            /* [in] */ double k,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ZhengTaiFun )( 
            IBlurAlgo * This,
            /* [in] */ double x,
            /* [retval][out] */ double *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetSanJiaoParameters )( 
            IBlurAlgo * This,
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SanJiaoFun )( 
            IBlurAlgo * This,
            double x,
            /* [retval][out] */ double *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetTiXingParameters )( 
            IBlurAlgo * This,
            /* [in] */ double b,
            /* [in] */ double c,
            /* [in] */ double d,
            /* [in] */ double e,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *TiXingFun )( 
            IBlurAlgo * This,
            double x,
            /* [retval][out] */ double *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetAscZhengTaiParameters )( 
            IBlurAlgo * This,
            /* [in] */ double k,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AscZhengTaiFun )( 
            IBlurAlgo * This,
            /* [in] */ double x,
            /* [retval][out] */ double *presult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetDescZhengTaiParameters )( 
            IBlurAlgo * This,
            /* [in] */ double k,
            /* [in] */ double a);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DescZhengTaiFun )( 
            IBlurAlgo * This,
            /* [in] */ double x,
            /* [retval][out] */ double *presult);
        
        END_INTERFACE
    } IBlurAlgoVtbl;

    interface IBlurAlgo
    {
        CONST_VTBL struct IBlurAlgoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBlurAlgo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBlurAlgo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBlurAlgo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBlurAlgo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBlurAlgo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBlurAlgo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBlurAlgo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBlurAlgo_SetZhengTaiParameters(This,k,a)	\
    ( (This)->lpVtbl -> SetZhengTaiParameters(This,k,a) ) 

#define IBlurAlgo_ZhengTaiFun(This,x,presult)	\
    ( (This)->lpVtbl -> ZhengTaiFun(This,x,presult) ) 

#define IBlurAlgo_SetSanJiaoParameters(This,b,c,a)	\
    ( (This)->lpVtbl -> SetSanJiaoParameters(This,b,c,a) ) 

#define IBlurAlgo_SanJiaoFun(This,x,presult)	\
    ( (This)->lpVtbl -> SanJiaoFun(This,x,presult) ) 

#define IBlurAlgo_SetTiXingParameters(This,b,c,d,e,a)	\
    ( (This)->lpVtbl -> SetTiXingParameters(This,b,c,d,e,a) ) 

#define IBlurAlgo_TiXingFun(This,x,presult)	\
    ( (This)->lpVtbl -> TiXingFun(This,x,presult) ) 

#define IBlurAlgo_SetAscZhengTaiParameters(This,k,a)	\
    ( (This)->lpVtbl -> SetAscZhengTaiParameters(This,k,a) ) 

#define IBlurAlgo_AscZhengTaiFun(This,x,presult)	\
    ( (This)->lpVtbl -> AscZhengTaiFun(This,x,presult) ) 

#define IBlurAlgo_SetDescZhengTaiParameters(This,k,a)	\
    ( (This)->lpVtbl -> SetDescZhengTaiParameters(This,k,a) ) 

#define IBlurAlgo_DescZhengTaiFun(This,x,presult)	\
    ( (This)->lpVtbl -> DescZhengTaiFun(This,x,presult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




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



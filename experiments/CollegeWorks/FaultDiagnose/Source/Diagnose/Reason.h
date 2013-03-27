/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Dec 09 12:05:25 2004
 */
/* Compiler settings for D:\航天部项目\源程序\fqz\Reason\Reason.idl:
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

#ifndef __Reason_h__
#define __Reason_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IReasonCom_FWD_DEFINED__
#define __IReasonCom_FWD_DEFINED__
typedef interface IReasonCom IReasonCom;
#endif 	/* __IReasonCom_FWD_DEFINED__ */


#ifndef __ReasonCom_FWD_DEFINED__
#define __ReasonCom_FWD_DEFINED__

#ifdef __cplusplus
typedef class ReasonCom ReasonCom;
#else
typedef struct ReasonCom ReasonCom;
#endif /* __cplusplus */

#endif 	/* __ReasonCom_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IReasonCom_INTERFACE_DEFINED__
#define __IReasonCom_INTERFACE_DEFINED__

/* interface IReasonCom */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IReasonCom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("18C466F3-87E0-44C6-BAF6-DAE019B16016")
    IReasonCom : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE free_rule( 
            unsigned long r) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE str_to_antecedent( 
            unsigned long str,
            unsigned long antecedent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE calculate_pred_expression( 
            unsigned long antecedent,
            unsigned long dataset,
            unsigned long return_value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE check_rule_error( 
            unsigned long r,
            unsigned long MetaData,
            unsigned long return_value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IReasonComVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IReasonCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IReasonCom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IReasonCom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IReasonCom __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IReasonCom __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IReasonCom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IReasonCom __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *free_rule )( 
            IReasonCom __RPC_FAR * This,
            unsigned long r);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *str_to_antecedent )( 
            IReasonCom __RPC_FAR * This,
            unsigned long str,
            unsigned long antecedent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *calculate_pred_expression )( 
            IReasonCom __RPC_FAR * This,
            unsigned long antecedent,
            unsigned long dataset,
            unsigned long return_value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *check_rule_error )( 
            IReasonCom __RPC_FAR * This,
            unsigned long r,
            unsigned long MetaData,
            unsigned long return_value);
        
        END_INTERFACE
    } IReasonComVtbl;

    interface IReasonCom
    {
        CONST_VTBL struct IReasonComVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReasonCom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReasonCom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReasonCom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReasonCom_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IReasonCom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IReasonCom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IReasonCom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IReasonCom_free_rule(This,r)	\
    (This)->lpVtbl -> free_rule(This,r)

#define IReasonCom_str_to_antecedent(This,str,antecedent)	\
    (This)->lpVtbl -> str_to_antecedent(This,str,antecedent)

#define IReasonCom_calculate_pred_expression(This,antecedent,dataset,return_value)	\
    (This)->lpVtbl -> calculate_pred_expression(This,antecedent,dataset,return_value)

#define IReasonCom_check_rule_error(This,r,MetaData,return_value)	\
    (This)->lpVtbl -> check_rule_error(This,r,MetaData,return_value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReasonCom_free_rule_Proxy( 
    IReasonCom __RPC_FAR * This,
    unsigned long r);


void __RPC_STUB IReasonCom_free_rule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReasonCom_str_to_antecedent_Proxy( 
    IReasonCom __RPC_FAR * This,
    unsigned long str,
    unsigned long antecedent);


void __RPC_STUB IReasonCom_str_to_antecedent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReasonCom_calculate_pred_expression_Proxy( 
    IReasonCom __RPC_FAR * This,
    unsigned long antecedent,
    unsigned long dataset,
    unsigned long return_value);


void __RPC_STUB IReasonCom_calculate_pred_expression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IReasonCom_check_rule_error_Proxy( 
    IReasonCom __RPC_FAR * This,
    unsigned long r,
    unsigned long MetaData,
    unsigned long return_value);


void __RPC_STUB IReasonCom_check_rule_error_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IReasonCom_INTERFACE_DEFINED__ */



#ifndef __REASONLib_LIBRARY_DEFINED__
#define __REASONLib_LIBRARY_DEFINED__

/* library REASONLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_REASONLib;

EXTERN_C const CLSID CLSID_ReasonCom;

#ifdef __cplusplus

class DECLSPEC_UUID("A962099D-EC3B-4327-A34F-FF3EE5ADBCEF")
ReasonCom;
#endif
#endif /* __REASONLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

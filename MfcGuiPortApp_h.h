

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 21:14:07 2038
 */
/* Compiler settings for MfcGuiPortApp.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __MfcGuiPortApp_h_h__
#define __MfcGuiPortApp_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMfcGuiPortApp_FWD_DEFINED__
#define __IMfcGuiPortApp_FWD_DEFINED__
typedef interface IMfcGuiPortApp IMfcGuiPortApp;

#endif 	/* __IMfcGuiPortApp_FWD_DEFINED__ */


#ifndef __MfcGuiPortApp_FWD_DEFINED__
#define __MfcGuiPortApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class MfcGuiPortApp MfcGuiPortApp;
#else
typedef struct MfcGuiPortApp MfcGuiPortApp;
#endif /* __cplusplus */

#endif 	/* __MfcGuiPortApp_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MfcGuiPortApp_LIBRARY_DEFINED__
#define __MfcGuiPortApp_LIBRARY_DEFINED__

/* library MfcGuiPortApp */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MfcGuiPortApp;

#ifndef __IMfcGuiPortApp_DISPINTERFACE_DEFINED__
#define __IMfcGuiPortApp_DISPINTERFACE_DEFINED__

/* dispinterface IMfcGuiPortApp */
/* [uuid] */ 


EXTERN_C const IID DIID_IMfcGuiPortApp;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("07f3d1a8-ead7-40da-a704-91c944f43ceb")
    IMfcGuiPortApp : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMfcGuiPortAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMfcGuiPortApp * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMfcGuiPortApp * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMfcGuiPortApp * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMfcGuiPortApp * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMfcGuiPortApp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMfcGuiPortApp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMfcGuiPortApp * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMfcGuiPortAppVtbl;

    interface IMfcGuiPortApp
    {
        CONST_VTBL struct IMfcGuiPortAppVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMfcGuiPortApp_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMfcGuiPortApp_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMfcGuiPortApp_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMfcGuiPortApp_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMfcGuiPortApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMfcGuiPortApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMfcGuiPortApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMfcGuiPortApp_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MfcGuiPortApp;

#ifdef __cplusplus

class DECLSPEC_UUID("0491098b-81e3-4eef-8af0-0633d2f73476")
MfcGuiPortApp;
#endif
#endif /* __MfcGuiPortApp_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



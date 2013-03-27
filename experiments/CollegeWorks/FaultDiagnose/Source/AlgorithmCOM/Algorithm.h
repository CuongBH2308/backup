// Algorithm.h: interface for the CAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALGORITHM_H__110F077F_BC4E_46D9_999A_470ED632AA70__INCLUDED_)
#define AFX_ALGORITHM_H__110F077F_BC4E_46D9_999A_470ED632AA70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AlgorithmCOM.h" //include the definitions of the interface



class CAlgorithm : public IBlurAlgo  
{
private:
	ULONG m_cRef;

	const double E; // 2.718281828459045
	const double epsilon;//��С����
	//��̬�ֲ������ò���
	double zt_k,zt_a;
	
	
	//���Ƿֲ������ò���
	double sj_b,sj_c,sj_a;
	
	//���ηֲ������ò���
	double tx_b,tx_c,tx_d,tx_e,tx_a;
	
	//������̬�ֲ����ò���
	double azt_k,azt_a;
	
	//������̬�ֲ����ò���
	double dzt_k,dzt_a;
	
public:
	CAlgorithm();
	//virtual ~CAlgorithm();

	//IUnknown Method
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();
	

	//IDispatch Method
	STDMETHOD(GetTypeInfoCount)(UINT * pit){	return E_NOTIMPL;}
	STDMETHOD(GetTypeInfo)(UINT it,LCID lcid,ITypeInfo **ppti){	return E_NOTIMPL;}
	STDMETHOD(GetIDsOfNames)(REFIID riid,OLECHAR ** pNames,UINT nNames,
		LCID lcid,DISPID * pdispids){	return E_NOTIMPL;}
	STDMETHOD(Invoke)(DISPID id,REFIID riid,LCID lcid,
		WORD wFlags,DISPPARAMS *pd,VARIANT * pVarResult,
		EXCEPINFO * pe,UINT *pu);

	
	//////////********	IBlurAlgo Method**********************************
	//��̬�ֲ�
	//k:���ڲ���  a:����ֵ
	STDMETHOD (SetZhengTaiParameters)(double k,double a);
	STDMETHOD (ZhengTaiFun)(double x,double* presult);

    //double
	//b,c:����ƫ��
	STDMETHOD (SetSanJiaoParameters)(double b,double c,double a);
	STDMETHOD (SanJiaoFun)(double x,double* presult);


	//���ηֲ�
	//d,e���ݲ�
	STDMETHOD (SetTiXingParameters)(double b,double c,double d,double e,double a);
	STDMETHOD (TiXingFun)(double x,double* presult);


	//������̬�ֲ�
	STDMETHOD (SetAscZhengTaiParameters)(double k,double a);
	STDMETHOD (AscZhengTaiFun)(double x,double* presult);


	//������̬�ֲ�
	STDMETHOD (SetDescZhengTaiParameters)(double k,double a);
	STDMETHOD (DescZhengTaiFun)(double x,double* presult);
    
	//*************************IBlurAlgo end**************************************************

	


};

#endif // !defined(AFX_ALGORITHM_H__110F077F_BC4E_46D9_999A_470ED632AA70__INCLUDED_)

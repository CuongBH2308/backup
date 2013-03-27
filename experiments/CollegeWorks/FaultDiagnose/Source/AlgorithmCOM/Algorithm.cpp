// Algorithm.cpp: implementation of the CAlgorithm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Algorithm.h"
#include "AlgorithmCOM_i.c"//　include the guids,can only be included once

#include<math.h>



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlgorithm::CAlgorithm():m_cRef(0),E(2.718281828459045),epsilon(0.00001)//极小正数
{

}

//CAlgorithm::~CAlgorithm()
//{

//}

STDMETHODIMP CAlgorithm::QueryInterface(REFIID riid, void **ppv)
{//	这里这是实现dynamic_cast的功能，但由于dynamic_cast与编译器相关。
	if(riid == IID_IBlurAlgo)
		*ppv = static_cast<IBlurAlgo *>(this);
	
	else if(riid == IID_IUnknown)
		*ppv = static_cast<IUnknown *>(this);//默认的
	else if(riid == IID_IDispatch)
		*ppv = static_cast<IDispatch *>(this);//默认的
	else {
		*ppv = 0;
		return E_NOINTERFACE;
	}
	
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();	//这里要这样是因为引用计数是针对组件的
	return S_OK; 
}

STDMETHODIMP_(ULONG) CAlgorithm::AddRef()
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CAlgorithm::Release()
{
	ULONG res = --m_cRef;	//　使用临时变量把修改后的引用计数值缓存起来
	if(res == 0)			//	因为在对象已经销毁后再引用这个对象的数据将是非法的
		delete this;
	return res;
}




//*************************************************************************

STDMETHODIMP CAlgorithm::SetZhengTaiParameters(double k,double a){
	if(k>0){
		zt_k = k;
		zt_a = a;
		return S_OK;
	}
	else 
		return S_FALSE;
		
}

STDMETHODIMP CAlgorithm::ZhengTaiFun(double x,double* presult){
	double y1 = (x-zt_a)*(x-zt_a);
	double y2 = (-1)*zt_k*y1;
	*presult = pow(E,y2);
	
	return S_OK;
}

STDMETHODIMP CAlgorithm::SetSanJiaoParameters(double b,double c,double a){
	if((a-b)>=0&&(c-a)>=0){
		sj_a = a;
		sj_b = b;
		sj_c = c;
		return S_OK;
	}
	else
		return S_FALSE;
}

STDMETHODIMP CAlgorithm::SanJiaoFun(double x,double* presult){
	if(x>sj_c||x<sj_b)//两边
		*presult = 0.0;
	//先处理端点，这两句位置不能调换
	if(fabs(x-sj_a)<epsilon)  
		*presult = 1.0;
	
	if(fabs(x-sj_b)<epsilon||fabs(x-sj_c)<epsilon)
		*presult = 0.0;
	
	
	if(x<sj_a&&x>sj_b)//左三角
		*presult =  (x-sj_b)/(sj_a-sj_b);
	
	if(x<sj_c&&x>sj_a)//右三角
		*presult = (sj_c-x)/(sj_c-sj_a);
	
	//*presult = 0.0;//不会执行

	return S_OK;
}

STDMETHODIMP CAlgorithm::SetTiXingParameters(double b,double c,double d,double e,double a){
	if(d>=b&&a>=d&&e>=a&&c>=e){
		tx_a = a;
		tx_b = b;
		tx_c = c;
		tx_d = d;
		tx_e = e;
		return S_OK;
	}
	else
		return S_FALSE;;

}

STDMETHODIMP CAlgorithm::TiXingFun(double x,double* presult){
	if(x<tx_b||x>tx_c)//两边
		*presult = 0.0;
	
	if(x<tx_e&&x>tx_d)  //中间
		*presult = 1.0;
	
	//顺序不能打乱
	if(fabs(x-tx_a)<epsilon||fabs(x-tx_d)<epsilon||fabs(x-tx_e)<epsilon)//a,d,e三点
		*presult = 1.0;
	
	if(fabs(x-tx_b)<epsilon||fabs(x-tx_c)<epsilon) //b,c两点
		*presult = 0.0;
	
	if(x<tx_d&&x>tx_b)//b,d之间
		*presult =  (x-tx_b)/(tx_d-tx_b);
	
	if(x<tx_c&&x>tx_e)//e,c之间
		*presult = (tx_c-x)/(tx_c-tx_e);
	
//	*presult = 0.0;//不会执行

	return S_OK;

}

STDMETHODIMP CAlgorithm::SetAscZhengTaiParameters(double k,double a){
	if(k>0){
		azt_k = k;
		azt_a = a;
		return S_OK;
	}
	else 
		return S_FALSE;

}

STDMETHODIMP CAlgorithm::AscZhengTaiFun(double x,double* presult){

	if(x<=azt_a&&x>=0)  *presult = 0.0f;
	else if(x>azt_a){
		double y1 = (x-azt_a)*(x-azt_a);
		double y2 = (-1)*azt_k*y1;
		double y3 = pow(E,y2);
		*presult = 1.0-y3;
	}
	else 
		return S_FALSE;
	
	
	return S_OK;

}

STDMETHODIMP CAlgorithm::SetDescZhengTaiParameters(double k,double a){
	if(k>0){
		dzt_k = k;
		dzt_a = a;
		return S_OK;
	}
	else 
		return S_FALSE;

}

STDMETHODIMP CAlgorithm::DescZhengTaiFun(double x,double* presult){
	
	if(x<=dzt_a&&x>=0)  *presult = 1.0f;
	else if(x>dzt_a){
		double y1 = (x-dzt_a)*(x-dzt_a);
		double y2 = (-1)*dzt_k*y1;
		*presult = pow(E,y2);
	}
	else 
		return S_FALSE;
	
	
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/*********************************************************************
* Function Declare : CAlgorithm::Invoke
* Explain : IDispatch接口的Invoke方法
* Parameters : 
* DISPID id -- 方法的序号(请与idl中序号相比较)
* REFIID riid -- 接口IID
* LCID lcid -- 
* WORD wFlags -- 
*  DISPPARAMS * pd -- 传入参数结构(具体结构请参阅MSDN或本质论p294)
* VARIANT * pVarResult -- 出参(VARIANT请参阅MSDN文档或<<深入解析ATL>>p56
* EXCEPINFO * pe -- 异常(一般为NULL)
* UINT * pu -- 
* Return : 
* STDMETHODIMP  -- 
* Author : tulip 
* Time : 2003-10-30 15:56:37 
*********************************************************************/
STDMETHODIMP CAlgorithm::Invoke(DISPID id,REFIID riid,LCID lcid,WORD wFlags,
						   DISPPARAMS * pd,VARIANT * pVarResult,EXCEPINFO * pe,UINT * pu)
{
	if(riid==IID_IBlurAlgo)
	{   
		
		if(1==id)
			return SetZhengTaiParameters(pd->rgvarg[0].dblVal,pd->rgvarg[1].dblVal);
		else if (2==id)
			return ZhengTaiFun(pd->rgvarg[0].dblVal,&pVarResult->dblVal);
		else if (3==id)
			return SetSanJiaoParameters(pd->rgvarg[0].dblVal,pd->rgvarg[1].dblVal,pd->rgvarg[2].dblVal);
		else if (4==id)
			return SanJiaoFun(pd->rgvarg[0].dblVal,&pVarResult->dblVal); 
		else if (5==id)
			return SetTiXingParameters(pd->rgvarg[0].dblVal,pd->rgvarg[1].dblVal,pd->rgvarg[2].dblVal,pd->rgvarg[3].dblVal,pd->rgvarg[4].dblVal);
		else if (6==id)
			return TiXingFun(pd->rgvarg[0].dblVal,&pVarResult->dblVal);
		else if (7==id)
			return SetAscZhengTaiParameters(pd->rgvarg[0].dblVal,pd->rgvarg[1].dblVal);
		else if (8==id)
			return AscZhengTaiFun(pd->rgvarg[0].dblVal,&pVarResult->dblVal);
		else if (9==id)
			return SetDescZhengTaiParameters(pd->rgvarg[0].dblVal,pd->rgvarg[1].dblVal);
		else if (10==id)
			return DescZhengTaiFun(pd->rgvarg[0].dblVal,&pVarResult->dblVal);
		else 
			return E_FAIL;
	}
	
	else 
		return E_NOINTERFACE;
	
}



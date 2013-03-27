#include <windows.h>
#include "../AlgorithmCOM.h" //include the definitions of the interface
#include "../AlgorithmCOM_i.c"//　include the guids
#include <iostream>
#include <atlbase.h>
using namespace std;

void main(void)
{
	//初始化COM库
	HRESULT hr=::CoInitialize(0);
	IBlurAlgo * pBlurAlgo=NULL;
	IDispatch * pDispatch=NULL;

	
	int nReturnValue=0;
	
	//如果还想用CoCreateInstance()得到接口指针，请如下使用先传一个IClassFactory接口
	
	/*************** 这里请注意 *****************/
	// 方法一
//	hr = ::CoCreateInstance(CLSID_AlgorithmCOM, 
//		CLSCTX_INPROC, 
//		NULL, 
//		IID_IBlurAlgo, 
//		(void*)&pBlurAlgo);
	
	///////////////////////////////////////////////////////////////////////
	// 这个方法的好处是不需要太多的代码, 让COM来处理真正的类厂创建对象的过程.
	// 同时这个函数的改进版CoCreateInstanceEx在分布式对象应用中可以一次取回多
	// 个接口指针. 避免过多的在网络上浪费时间关于这个函数的用法我也会在以后的
	// 章节中讲解. 您也可以参考MSDN或相关书藉
	
	//	方法二
	IClassFactory * pClassFactory=NULL;	// 类厂接口指针
	//	获取对象的类厂接口指针
	hr=::CoGetClassObject(CLSID_AlgorithmCOM,
		CLSCTX_INPROC,
		NULL,
		IID_IClassFactory,
		(void**)&pClassFactory);
	
	// 真正创建对象
	hr = pClassFactory->CreateInstance(NULL,IID_IBlurAlgo,(void**)&pBlurAlgo);
	// 此方法的好处在于可以一次创建多个对象, 不需要
	
	// 下面测试 IDispatch 接口
	if(SUCCEEDED(hr))
	{
		//hr=pBlurAlgo->SetZhengTaiParameters(1,0);
		double dres;
		//pBlurAlgo->ZhengTaiFun(0,&dres);

		pBlurAlgo->SetDescZhengTaiParameters(1,0);
		pBlurAlgo->DescZhengTaiFun(0.0,&dres);
		if(SUCCEEDED(hr))
			cout << " 正态分布： " <<dres<< endl;
		nReturnValue=0;
	}
	
	//查询对象实现的接口IAdvancedMath
	hr=pBlurAlgo->QueryInterface(IID_IDispatch, (void **)&pDispatch);
	
	if(SUCCEEDED(hr))
	{
		cout<<"下面进行IDispatch接口"<<endl;
		CComVariant  varResult;
		CComVariant  varResult2;
		CComVariant *pvars=new CComVariant[2];
		CComVariant *pvars2=new CComVariant[1];
		varResult.Clear();
		pvars[1]=0;
		pvars[0]=1;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };//不再按指针，而是按顺序调用函数
		hr=pDispatch->Invoke(0x1, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);


		varResult.Clear();
		pvars2[0] = 0;
		DISPPARAMS disp2 = { pvars2, NULL, 1, 0 };
		hr=pDispatch->Invoke(0x2, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp2, &varResult, NULL, NULL);
	
		if(SUCCEEDED(hr))
			cout << "正态　= " <<varResult.dblVal<< endl;
		varResult2.Clear();
	}
	
	pBlurAlgo->Release();
	pDispatch->Release();
	
	::CoUninitialize();
	return ;
}

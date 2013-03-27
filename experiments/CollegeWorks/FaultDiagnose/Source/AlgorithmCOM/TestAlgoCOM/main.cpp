#include <windows.h>
#include "../AlgorithmCOM.h" //include the definitions of the interface
#include "../AlgorithmCOM_i.c"//��include the guids
#include <iostream>
#include <atlbase.h>
using namespace std;

void main(void)
{
	//��ʼ��COM��
	HRESULT hr=::CoInitialize(0);
	IBlurAlgo * pBlurAlgo=NULL;
	IDispatch * pDispatch=NULL;

	
	int nReturnValue=0;
	
	//���������CoCreateInstance()�õ��ӿ�ָ�룬������ʹ���ȴ�һ��IClassFactory�ӿ�
	
	/*************** ������ע�� *****************/
	// ����һ
//	hr = ::CoCreateInstance(CLSID_AlgorithmCOM, 
//		CLSCTX_INPROC, 
//		NULL, 
//		IID_IBlurAlgo, 
//		(void*)&pBlurAlgo);
	
	///////////////////////////////////////////////////////////////////////
	// ��������ĺô��ǲ���Ҫ̫��Ĵ���, ��COM�������������೧��������Ĺ���.
	// ͬʱ��������ĸĽ���CoCreateInstanceEx�ڷֲ�ʽ����Ӧ���п���һ��ȡ�ض�
	// ���ӿ�ָ��. �����������������˷�ʱ���������������÷���Ҳ�����Ժ��
	// �½��н���. ��Ҳ���Բο�MSDN��������
	
	//	������
	IClassFactory * pClassFactory=NULL;	// �೧�ӿ�ָ��
	//	��ȡ������೧�ӿ�ָ��
	hr=::CoGetClassObject(CLSID_AlgorithmCOM,
		CLSCTX_INPROC,
		NULL,
		IID_IClassFactory,
		(void**)&pClassFactory);
	
	// ������������
	hr = pClassFactory->CreateInstance(NULL,IID_IBlurAlgo,(void**)&pBlurAlgo);
	// �˷����ĺô����ڿ���һ�δ����������, ����Ҫ
	
	// ������� IDispatch �ӿ�
	if(SUCCEEDED(hr))
	{
		//hr=pBlurAlgo->SetZhengTaiParameters(1,0);
		double dres;
		//pBlurAlgo->ZhengTaiFun(0,&dres);

		pBlurAlgo->SetDescZhengTaiParameters(1,0);
		pBlurAlgo->DescZhengTaiFun(0.0,&dres);
		if(SUCCEEDED(hr))
			cout << " ��̬�ֲ��� " <<dres<< endl;
		nReturnValue=0;
	}
	
	//��ѯ����ʵ�ֵĽӿ�IAdvancedMath
	hr=pBlurAlgo->QueryInterface(IID_IDispatch, (void **)&pDispatch);
	
	if(SUCCEEDED(hr))
	{
		cout<<"�������IDispatch�ӿ�"<<endl;
		CComVariant  varResult;
		CComVariant  varResult2;
		CComVariant *pvars=new CComVariant[2];
		CComVariant *pvars2=new CComVariant[1];
		varResult.Clear();
		pvars[1]=0;
		pvars[0]=1;
		DISPPARAMS disp = { pvars, NULL, 2, 0 };//���ٰ�ָ�룬���ǰ�˳����ú���
		hr=pDispatch->Invoke(0x1, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp, &varResult, NULL, NULL);


		varResult.Clear();
		pvars2[0] = 0;
		DISPPARAMS disp2 = { pvars2, NULL, 1, 0 };
		hr=pDispatch->Invoke(0x2, IID_IBlurAlgo, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &disp2, &varResult, NULL, NULL);
	
		if(SUCCEEDED(hr))
			cout << "��̬��= " <<varResult.dblVal<< endl;
		varResult2.Clear();
	}
	
	pBlurAlgo->Release();
	pDispatch->Release();
	
	::CoUninitialize();
	return ;
}

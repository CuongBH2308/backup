/**
 * @file Singleton.h The interface of Singleton and SingletonPtr class.
 *
 * Description: Singleton base class, it is better than implement singleton in specific class in :
 * 1) reduce redundant code 
 * 2) All single class share the same implementation, so it is easy to alter the implementation. 
 * 3) Make sure all singleton class accessed through the same interface, convenient for using.
 *

 *
 * @author Baiyan Huang
 *
 * @date 05/27/2008
 */
#pragma once

namespace FW
{
	// singleton base class, delete automatically
	template <class T> class  Singleton
	{
	protected:
		Singleton(){}
	public:
		// there instance function 
		static T* GetInstance()
		{
			static T instance;
			return &instance;
		}
	};

	//// Concrete singleton class, derived from Singleton<T>
	//class ExampleSingleton: public Singleton<ExampleSingleton>
	//{
	//	// so that Singleton<ExampleSingleton> can access the 
	//	// protected constructor
	//	friend class Singleton<ExampleSingleton>;
	//
	//protected:
	//	ExampleSingleton(){}
	//  ~ExampleSingleton(){}
	//public:
	//	// This class's real functionalities
	//	void Write(){printf("Hello, World!");}
	//};
	//
	//// use this singleton class
	//ExampleSingleton::Instance()->Write();


	// singleton base class, delete manually
	// note: use this base class if you want to control the creation and destroy of a singleton
	template <class T> class  SingletonPtr
	{
	protected:
		SingletonPtr(){}
	public:
		// there instance function 
		static T* GetInstance()
		{
			if (NULL == m_pInstance)
			{
				m_pInstance = new T();
			}
			return m_pInstance;
		}
		static void DeleteInstance()
		{
			if (NULL != m_pInstance)
			{
				delete m_pInstance;
				m_pInstance = NULL;
			}
		}
	private:
		static T* m_pInstance;
	};

	// instantiated static member.
	template<class T> T* SingletonPtr<T>::m_pInstance = NULL;

	//// Concrete singleton class, derived from SingletonPtr<T>
	//class ExampleSingleton: public SingletonPtr<ExampleSingleton>
	//{
	//	// so that SingletonPtr<ExampleSingleton> can access the 
	//	// protected constructor
	//	friend class SingletonPtr<ExampleSingleton>;
	//
	//protected:
	//	ExampleSingleton(){}
	//  ~ExampleSingleton(){}
	//public:
	//	// This class's real functionalities
	//	void Write(){printf("Hello, World!");}
	//};
	// 
	//// use this singleton class
	//ExampleSingleton::Instance()->Write();
	//ExampleSingleton::DeleteInstance();

}
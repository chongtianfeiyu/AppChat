#ifndef CLASS_FACTORY_H
#define CLASS_FACTORY_H

#include <string>
#include <iostream>
#include <map>

using namespace std;

namespace classFactory
{
	typedef void* (*CreateFunction)(void);
	
	class ClassFactory
	{
	public:
			ClassFactory(void);
			virtual ~ClassFactory(void);
			static void registerClass(string& className,CreateFunction createInstanceFunc);
			static void* getClassByName(string clsName);

	private:
		static map<string,CreateFunction> m_clsMap;
	};

	
	class Factory
	{
	public:
		Factory(string& className,CreateFunction func)
		{
			ClassFactory::registerClass(className,func);
		}
		virtual ~Factory(void);
	};

	//宏定义返射
	#define DEFINE_REFLECTION_CLASS(class_name) \
	class class_name##Factory \
	{\
	public:\
		static void* createInstance() {\
			return new class_name \
		}\
	private:\
		static const Factory mInstance; \
	};\
	const Factory class_name##Factory::mInstance(#class_name,class_name##Factory::createInstance);
}
#endif

	

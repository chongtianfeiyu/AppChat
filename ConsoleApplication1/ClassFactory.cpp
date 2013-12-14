#include "ClassFactory.h"

#include "protocbuff/chatMsg.pb.h";

using namespace classFactory;

map<string,CreateFunction> ClassFactory::m_clsMap;

ClassFactory::ClassFactory(void)
{

}


ClassFactory::~ClassFactory(void)
{

}

void* ClassFactory::getClassByName(string clsName)
{
	map<string,CreateFunction>::const_iterator find;
	find = m_clsMap.find(clsName);
	if(find != m_clsMap.end())
	{
		return find->second();
	}
	return NULL;
}

void ClassFactory::registerClass(string& className,CreateFunction createInstanceFunc)
{
	m_clsMap.insert(make_pair(className,createInstanceFunc));
}


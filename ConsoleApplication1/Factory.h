#ifndef FACTORY_H
#define FACTORY_H

#include "protocbuff/chatMsg.pb.h"

namespace classFactory
{
class Factory
{
	public:
		Factory(void);
		virtual ~Factory(void);
		virtual void* createInstance() = 0;
	};
}
#endif


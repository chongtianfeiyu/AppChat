#ifndef NET_RESPONSE_H
#define NET_RESPONSE_H

#include <map>
#include "ClientSession.h"
#include "protocbuff/chatMsg.pb.h"


using namespace std;
using namespace google::protobuf;

namespace response
{

	//回调函数指针
	typedef void (*callBack)(nshead_t& nshead);

	//协议里的回调处理函数
	static map<int,callBack> callBackMap;

	//登录聊天后处理
	void loginServer_response(nshead_t& nshead);
    
    //接收到聊天内容处理
    void chat_progress(nshead_t& nshead);

    //登出处理  
    void logout(nshead_t& nshead);
}
#endif


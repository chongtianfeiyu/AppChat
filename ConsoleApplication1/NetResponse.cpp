#include "NetResponse.h"
#include "protocbuff/chatMsg.pb.h"
#include <iostream>
#include "ClientSession.h"
#include "ChatServer.h"
#include "SERVER_IO.h"
#include "Utils.h"
#include <string.h>

using namespace std;
using namespace response;

CodeConvert utf8ToGb2312("utf-8","gb2312");
CodeConvert gb2312ToUtf8("gb2312","utf-8");

//登录聊天后回调处理函数
void response::loginServer_response(nshead_t& nshead)
{
	protocol::loginServer* logSvr = new protocol::loginServer();
    
    char buffs[MAX_NET_LEN];
    memset(buffs,'\0',MAX_NET_LEN);
    strcpy(buffs,nshead.body_content);
    
	logSvr->ParseFromArray(buffs,MAX_NET_LEN);
    const string& userID = logSvr->userid();
    
    cout << "userID is " << userID << endl;
    
    ClientSession* pSession = (ClientSession*)nshead.clientSession;
    
    if(chatServer.validateExistSession(userID))
	{
		//把原来的连接挤下线
		chatServer.disableSession(userID);
	}
	((ClientSession*)nshead.clientSession)->sessionID = logSvr->userid();

}
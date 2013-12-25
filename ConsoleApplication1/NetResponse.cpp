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
	logSvr->ParseFromArray(nshead.body_content,nshead.body_len);

    char userIDOut[256];
    memset(&userIDOut,'\0',sizeof(userIDOut));
    
    char tempUserID[256];
    memset(&tempUserID,'\0',sizeof(tempUserID));
    
    strcpy(tempUserID,logSvr->userid().c_str());
    
    utf8ToGb2312.convert(tempUserID,sizeof(tempUserID) + 1,userIDOut,sizeof(userIDOut));
    
    cout << "gb2312 -> :" << userIDOut << endl;
    //cout << "old -> : " << logSvr->userid() << endl;
    
	//const string userID = logSvr->userid();
    
    //utf8ToGb2312.convert(userID.c_str(),strlen(userID.c_str()),userIDOut,sizeof(userIDOut));

	
//    if(chatServer.validateExistSession(userID))
//	{
//		//把原来的连接挤下线
//		chatServer.disableSession(userID);
//	}
//
//	((ClientSession*)nshead.clientSession)->sessionID = logSvr->userid();
//
}
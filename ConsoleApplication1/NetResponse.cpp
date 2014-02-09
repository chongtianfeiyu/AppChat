//消息协议解偶处理

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

//buff 收到的buff内容
char buffs[MAX_NET_LEN];

//登录聊天后回调处理函数
void response::loginServer_response(nshead_t& nshead)
{
	protocol::loginServer* logSvr = new protocol::loginServer();
    
    //char buffs[MAX_NET_LEN];
    memset(buffs,'\0',MAX_NET_LEN);
    memcpy(buffs,nshead.body_content,nshead.body_len);
    
	logSvr->ParseFromArray(buffs,nshead.body_len);
    const string& userID = logSvr->userid();
    
    cout << "userID is " << userID << endl;
    
    ClientSession* pSession = static_cast<ClientSession*>(nshead.clientSession);
    
    if(chatServer.validateExistSession(userID))
	{
        //发送消怎提示
        protocol::errorMsg* pErrorMsg = new protocol::errorMsg();
        
        pErrorMsg->set_error_code(10001);
        pErrorMsg->set_error_msg("你的账号已在别处登录");
        
        pSession->sendMsgBySid(pErrorMsg,protocol::XIYD_THREE_EEROR);
        
		//把原来的连接挤下线
		chatServer.disableSession(userID);
	}
    pSession->sessionID = logSvr->userid();
}


//收到聊天信息后处理,将聊天广播给其他人。
void response::chat_progress(nshead_t& nshead)
{
    ClientSession* pSession = static_cast<ClientSession*>(nshead.clientSession);
    
    memset(buffs,'\0',MAX_NET_LEN);
    memcpy(buffs,nshead.body_content,nshead.body_len);
        
    protocol::dialogMsg* dialogMsg = new protocol::dialogMsg();
    dialogMsg->ParseFromArray(buffs,nshead.body_len);
    
    cout << dialogMsg->dialogstr() << endl;
    
    cout << "parseFromArray" << endl;
    string& ssid = pSession->sessionID;
    
    vector<ChatServer::session_ptr> ssList = chatServer.getSessionList();
    vector<ChatServer::session_ptr>::const_iterator it;
    
    for(it = ssList.begin(); it != ssList.end(); it++)
    {
        ClientSession* pClient = static_cast<ClientSession*>(it->get());
        if(pClient->sessionID != ssid && pClient -> sessionID != "")
        {
            pClient->sendMsgBySid(dialogMsg,protocol::XYID_DIALOG);
        }
    }
}

//登出处理
void response::logout(nshead_t& nshead)
{
    ClientSession* pSession = static_cast<ClientSession*> (nshead.clientSession);
    
    memset(buffs,'\0',MAX_NET_LEN);
    strcpy(buffs,nshead.body_content);
    
    protocol::logOut* logoutMsg = new protocol::logOut();
    pSession->sendMsgBySid(logoutMsg,protocol::XYID_LOGOUT);
    
    string& ssid = pSession->sessionID;
    chatServer.disableSession(ssid);
}

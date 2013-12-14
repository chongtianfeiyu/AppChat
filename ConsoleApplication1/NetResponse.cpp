#include "NetResponse.h"
#include "protocbuff/chatMsg.pb.h"
#include <iostream>;
#include "ClientSession.h"
#include "ChatServer.h"
#include "SERVER_IO.h"

using namespace std;
using namespace response;

//登录聊天后回调处理函数
void response::loginServer_response(nshead_t& nshead)
{
	protocol::loginServer* logSvr = new protocol::loginServer();
	logSvr->ParseFromArray(nshead.body_content,nshead.body_len);


	const string& userID = logSvr->userid();

	if(chatServer.validateExistSession(userID))
	{
		//把原来的连接挤下线
		chatServer.disableSession(userID);
	}

	((ClientSession*)nshead.clientSession)->sessionID = logSvr->userid();

}
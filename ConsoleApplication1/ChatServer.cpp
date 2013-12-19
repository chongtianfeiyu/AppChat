#include "ChatServer.h"
#include "NetResponse.h"
#include "SERVER_IO.h"
#include "ClientSession.h"
#include <boost/lexical_cast.hpp>

using namespace response;

//聊天服务程序，这里有一个异步计时器功能，每隔5秒会检测一次失去心跳的连接，然后记录做剔除处理.
ChatServer::ChatServer(void):tm(time_io_service)
{
	//观察客户端登录数据
	response::callBackMap.insert(make_pair(protocol::XYID_LOGIN,&response::loginServer_response));
}

ChatServer::~ChatServer(void)
{
	sessionList.clear();
}

//开启聊天服务
void ChatServer::start()
{
	beginAccept();

	//开始心跳计时
	tm.expires_from_now(boost::posix_time::seconds(5));
	tm.async_wait(boost::bind(&ChatServer::intervalHandler,this,boost::asio::placeholders::error));
	//time_io_service.run();
}

//停止聊天服务
void ChatServer::stop()
{
	vector<session_ptr>::iterator iter = sessionList.begin();
	vector<session_ptr>::iterator eiter = sessionList.end();
	while(iter != eiter)
	{
		iter++;
		((session_ptr)*iter)->disconnect();
	}
	sessionList.clear();

	//停止心跳计时
	tm.cancel();
	time_io_service.stop();

}

//开始监听客户端连接进入
void ChatServer::beginAccept()
{
	session_ptr session(new ClientSession());
	svrAccept.async_accept(session->getSocket(),boost::bind(&ChatServer::acceptHandler,this,boost::asio::placeholders::error,session));
}

//接收到有连接进入后回调处理
void ChatServer::acceptHandler(const boost::system::error_code& error,session_ptr& session)
{
	cout << "accept a new client." << endl;

	//启动Session
	session->start();

	//添加有session队列中
	sessionList.push_back(session);

	//接收下个连接处理
	beginAccept();
}

//接收到数据包后，多态解耦回调处理
void ChatServer::appendToSerializeList(nshead_t netBody)
{
	map<int,response::callBack>::iterator find;
	find =response::callBackMap.find(netBody.body_id);
	if(find != response::callBackMap.end())
	{
		cout << "response handler " << netBody.body_id << endl;
		find->second(netBody);
	}
	else
	{
		cout << "response fault" << netBody.body_id << endl;
	}
}

//异步计时调回处理。每隔5秒回调一次
void ChatServer::intervalHandler(const boost::system::error_code& error)
{
	if(error)
	{
		cout << error.message() << endl;
		return;
	}

	vector<session_ptr>::iterator it;
	for(it = sessionList.begin(); it != sessionList.end();)
	{
		session_ptr tmp_ptr = (session_ptr)*it;
		if(!tmp_ptr->heartValid)
		{
			tmp_ptr->loseHeartHandler();
			int max_out = MAX_HEART_OUT;
			if(tmp_ptr->loseheart >= max_out)
			{
				it = sessionList.erase(it);
				cout << "clear session" << endl;
			}
			else
			{
				it++;
			}
		}
	}

	//每隔5秒回调一次
	tm.expires_from_now(boost::posix_time::seconds(5));
	tm.async_wait(boost::bind(&ChatServer::intervalHandler,this,boost::asio::placeholders::error));
}


//检查是否有相同的会话建立联接，比如同样的账号进行登录检查
bool ChatServer::validateExistSession(const string& sid)
{
	bool res = false;
	vector<session_ptr>::iterator it;
	for(it = sessionList.begin(); it != sessionList.end(); it++)
	{
		session_ptr tmp_ptr = (session_ptr)*it;
		if(tmp_ptr->sessionID == sid)
		{
			res = true;
			break;
		}
	}
	return res;
}

//根据sessionID断开一个会话
bool ChatServer::disableSession(const string& sid)
{
	bool res = false;
	vector<session_ptr>::iterator it;
	for(it = sessionList.begin(); it != sessionList.end();)
	{
		session_ptr tmp_ptr = (session_ptr)*it;
		if(tmp_ptr -> sessionID == sid)
		{
			//断开会话
			tmp_ptr->disconnect();
			//从会话列表中剔除
			it = sessionList.erase(it);

			return true;

		}
		else
		{
			it++;
		}
	}
	return false;
}

#include "ChatServer.h"
#include "NetResponse.h"
#include "SERVER_IO.h"
#include "ClientSession.h"
#include "protocbuff/chatMsg.pb.h"
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>


using namespace response;

boost::mutex mu;
boost::thread intervalThread;



//聊天服务程序，这里有一个异步计时器功能，每隔5秒会检测一次失去心跳的连接，然后记录做剔除处理.
ChatServer::ChatServer(void)
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

    if(!APP_IS_DEBUG)
    {
        //启动线程计时器异步处理
        intervalThread = boost::thread(boost::bind(&ChatServer::intervalHandler,this));
    }
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

    if(!APP_IS_DEBUG)
    {
        //中断计时器线程
        intervalThread.interrupt();
    }
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
    
    protocol::dialogMsg* pDialog = new protocol::dialogMsg();
    pDialog->set_dialogstr("hello welcomplete");
    
    //接收到联接请求后发送的一个聊天包给客户端通知联接成功
    session->sendMsgBySid(pDialog,protocol::XYID_DIALOG);

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
		cout << "response fault " << netBody.body_id << endl;
	}
}

//异步计时调回处理。每隔5秒回调一次
void ChatServer::intervalHandler()
{
    
    while(true)
    {
        sleep(5);
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
        mu.lock();
        cout << "run heart hand" << endl;
        mu.unlock();
    }
}


//检查是否有相同的会话建立联接，比如同样的账号进行登录检查
bool ChatServer::validateExistSession(const string& sid)
{
    
    int user_size = static_cast<int>(sid.length());
    if(user_size == 0) return false;
    
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


//根据session返回一个session对像
ClientSession* ChatServer::findSessionByID(const string& sid)
{
    vector<session_ptr>::iterator it;
    for(it = sessionList.begin(); it != sessionList.end(); it++)
    {
        const ClientSession* pcs = it->get();
        if(pcs->sessionID == sid)
        {
            return it->get();
        }
    }
    return NULL;
}

//根据sessiondID 发送相关的数据协议
void ChatServer::sendMsgBySid(const string& sid,google::protobuf::Message* msg,unsigned short cmd)
{
    ClientSession* pclientSession = findSessionByID(sid);
    if(pclientSession != NULL)
    {
        pclientSession->sendMsgBySid(msg,cmd);
    }
}




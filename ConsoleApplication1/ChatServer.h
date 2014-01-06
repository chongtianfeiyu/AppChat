#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <vector>
#include "ClientSession.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/coded_stream.h>

using namespace google::protobuf::io;

using namespace std;
using namespace boost;

class ChatServer
{

public:
	typedef boost::shared_ptr<ClientSession> session_ptr;

public:
	ChatServer(void);
	~ChatServer(void);
	void start();									//启动服务
	void stop();									//停止服务
	void beginAccept();								//接收客户端
	void appendToSerializeList(nshead_t netBody);	//接收到网络数据到缓存队列
	void threadSerializedBody();					//线程中解析包体

	//计时器处理回调函数
	void intervalHandler(const boost::system::error_code& error);

	//验证session是否存在
	bool validateExistSession(const string& sid);

	//关闭一个session
	bool disableSession(const string& sid);
    
    //根据sid发送一条信息
    void sendMsgBySid(const string& sid,google::protobuf::Message* msg,unsigned short cmd);
    
    //根据sid获取返回一个 session指针对像
    ClientSession* findSessionByID(const string& sid);
    
    
    //返回当前连接上的客户端列表
    inline vector<session_ptr> getSessionList() const
    {
        return sessionList;
    }
    
    
private:
	void acceptHandler(const boost::system::error_code& error,session_ptr& session);		//开始接收客户端
private :
	vector<session_ptr> sessionList;				//客户端连接
	//计时器IO,用于定时检测心跳连接处理，将失去心跳的session做剔除处理。
	boost::asio::io_service time_io_service;
	asio::deadline_timer tm;
};

#endif


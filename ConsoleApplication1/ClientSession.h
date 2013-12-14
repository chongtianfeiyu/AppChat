﻿#ifndef CLIENT_SESSION_H
#define CLIENT_SESSION_H

//定义包长
#define MAX_NET_LEN 4096

//心跳丢失的最大次数限制
#define MAX_HEART_OUT 3;

#include <iostream>
#include <fstream>
#include <string.h>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>

using std::string;
using std::fstream;

namespace boostNet = boost::asio::ip;

struct nshead_t
{
	unsigned short body_len;    //网络包长
	unsigned short body_id;     //网络包ID
	char* body_content;			//包体
	void *clientSession;		//收包的session
};


class ClientSession:public boost::enable_shared_from_this<ClientSession>
{
public:
	
	ClientSession(void);
	virtual ~ClientSession(void);
	string& getIp();			//包ID				
	void start();				//开始				
	void disconnect();			//断开				
	bool isOpen();				//验证是否是连接状态				
	void sendMsg();				//发送消体				
	void receiverMsg();			//接收消息				
	void receiverHandler(const boost::system::error_code& error,char* headBuff);					//读取包头成功
	/*获取当前的通信管道Socket*/
	boostNet::tcp::socket& getSocket();			
	/*重置心跳，用来验证下次是否接收到心跳处理*/
	void restHeartbeat();
	/*确认心跳丢失后的处理*/
	void loseHeartHandler();
	//收到心跳后处理
	void heartHandler();	

public :
	/*是否有存在心跳标记*/
	bool heartValid;			
	/*心跳的次数*/
	unsigned int heartbeat;		
	/*丢失心跳次数*/
	unsigned int loseheart;		
	//会话ID == userID
	string sessionID;

private:
	/*socket通信句柄管道*/
	boostNet::tcp::socket mSocket;				
	/*buff偏移值*/
	int OFF_SET;			
};

#endif

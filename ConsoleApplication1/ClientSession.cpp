﻿#include <iostream>

#include "ClientSession.h"
#include "ChatServer.h"

#include "protocbuff/chatMsg.pb.h"
#include "NetResponse.h"

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

#include "SERVER_IO.h"

using namespace std;
using namespace google::protobuf::io;

ClientSession::ClientSession(void):mSocket(globalIoSvr),OFF_SET(2)
{
	
}

ClientSession::~ClientSession(void)
{

}


//获取客户端的连接ip
string& ClientSession::getIp()
{
    string ipAddress = mSocket.remote_endpoint().address().to_string();
	return ipAddress;
}


//启动当前连接
void ClientSession::start()
{
	if(isOpen())
	{
		//接收下条数据
		receiverMsg();
	}
}

//断开联接
void ClientSession::disconnect()
{
	if(isOpen())
	{
		//接收下条数据
		mSocket.close();
	}
}

//验证是否与终端连上的
bool ClientSession::isOpen()
{
	return mSocket.is_open();
}


//监听接收socket的数据信息
void ClientSession::receiverMsg()
{
	char pHeadBuf[MAX_NET_LEN];
	memset(&pHeadBuf,0,MAX_NET_LEN);
	mSocket.async_read_some(boost::asio::buffer(&pHeadBuf,MAX_NET_LEN),boost::bind(&ClientSession::receiverHandler,shared_from_this(),boost::asio::placeholders::error,(char*)&pHeadBuf));
}

//接收到数据包后的回调处理
//
void ClientSession::receiverHandler(const boost::system::error_code& error,char* headBuff)
{
	if(error)
	{
		//收到异常处理
		cout << "receiver error: " << error.message() << endl;
		//接收下条数据
		//receiverMsg();
        mSocket.close();
		return;
	}
    
    //包长
	short body_len = *(unsigned short*)headBuff;
	headBuff += sizeof(short);

	//包ID
	short body_id = *(unsigned short*)headBuff;
	headBuff += sizeof(short);
    
    //数据包内容
    char bodyContent[MAX_NET_LEN];
    memset(bodyContent,'\0',MAX_NET_LEN);
    memcpy(bodyContent, headBuff, sizeof(headBuff) + 1);
    //复位字节流的指针
    char* bodybuff = bodyContent;
        
    if(body_id == protocol::XYID_HEART)
	{
		//标记当前心跳有效
		heartHandler();
	}
	else
	{
		//包头
		nshead_t nsHead = {static_cast<unsigned short>(body_len - OFF_SET),static_cast<unsigned short>(body_id),(char*)bodybuff,this};

		//收到数据后多态处理
		chatServer.appendToSerializeList(nsHead);
	}

	if(isOpen())
	{
		//接收下条数据
		receiverMsg();
	}
}


//收到心跳包后处理
void ClientSession::heartHandler()
{
	heartValid = true;
	heartbeat++;

	//请除丢失的记录次数
	loseheart = 0;
}

//确认心跳丢失后的处理
void ClientSession::loseHeartHandler()
{
	loseheart++;
	int max_heart_out = MAX_HEART_OUT;
	if(loseheart >= max_heart_out)
	{
		//断开连接
		disconnect();
	}
}

//重置心跳,用来验证下次是否接收到心跳处理
void ClientSession::restHeartbeat()
{
	heartValid = false;
}

//获取当前的通信管道Socket
boostNet::tcp::socket& ClientSession::getSocket()
{
	return mSocket;
}

//发送消息
void ClientSession::sendMsgBySid(google::protobuf::Message *msg,unsigned short cmd)
{
    
    if(msg == NULL) return;
    
    int bodyLen = msg->ByteSize();
    
    //消息体
    char byteArray[bodyLen];
    memset(&byteArray,'\0',bodyLen);
    
    ZeroCopyOutputStream* raw_output = new ArrayOutputStream(byteArray, msg->ByteSize() + 1);
    CodedOutputStream* code_output = new CodedOutputStream(raw_output);
    
    if(!msg->SerializeToCodedStream(code_output))
    {
        cout << "Fault to Serialize msg data" << endl;
        return;
    }
    
    //消息长度
    unsigned short packetLen = msg->ByteSize() + OFF_SET;
    
    //网络传输包
    char netBuffs[MAX_NET_LEN];
    memset(netBuffs,'\0',sizeof(netBuffs));
    
    //包指针
    char* pBuffs = netBuffs;
    
    //写入包长
    memcpy(pBuffs, &packetLen, sizeof(short));
    
    //偏移指针
    pBuffs += sizeof(short);
    
    //写包ID
    memcpy(pBuffs,&cmd,sizeof(cmd));
    
    //偏移指针
    pBuffs += sizeof(short);
    
    //写入包体
    memcpy(pBuffs,byteArray,msg->ByteSize() + 1);
    
    mSocket.async_write_some(boost::asio::buffer(&netBuffs,sizeof(netBuffs)),
                             boost::bind(&ClientSession::sendComplete,shared_from_this(),boost::asio::placeholders::error,byteArray));
    
    //cout << "send buff size :" << msg->ByteSize() << endl;
}

void ClientSession::sendComplete(const boost::system::error_code& error,char* buffs)
{
    cout << "send: " << buffs << endl;
}
#ifndef SERVER_IO_H
#define SERVER_IO_H

#include "ChatServer.h"
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>

//聊天服务
extern ChatServer chatServer;
//端点
extern short domainPort;
//服务句柄
extern boost::asio::io_service globalIoSvr;
extern boost::asio::ip::tcp::endpoint endPoint;
extern boost::asio::ip::tcp::acceptor svrAccept;
//是否是调试模式
extern bool APP_IS_DEBUG;
#endif
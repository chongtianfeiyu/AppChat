#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/buffered_stream.hpp>

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>


#include "protocbuff/chatMsg.pb.h"
#include "ChatServer.h"
#include "ClassFactory.h"

using std::cout;
using std::endl;

using namespace boost;
using namespace google::protobuf::io;
using namespace classFactory;

//端口号
short domainPort = 8100;

//物理服务句柄
boost::asio::io_service globalIoSvr;

//服务端点
boost::asio::ip::tcp::endpoint endPoint(boost::asio::ip::tcp::v4(),domainPort);

//接收连接句柄
boost::asio::ip::tcp::acceptor svrAccept(globalIoSvr,endPoint);

//聊天服务
ChatServer chatServer;

//是否是调试模式
bool APP_IS_DEBUG = true;

int main(int argc,char* argv[])
{
	cout << "chat server start." << endl;
	chatServer.start();
	//接收到数据包处理线程
	//thread serializeThread(boost::bind(&ChatServer::threadSerializedBody,&chatServer));
	globalIoSvr.run();
    return 0;
}

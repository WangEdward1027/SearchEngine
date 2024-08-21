#include "EchoServer.h"
#include <functional>
#include <iostream>
using std::bind;
using std::cout;
using std::endl;
 

MyTask::MyTask(const string &msg, const TcpConnectionPtr &con)
: _msg(msg)
, _con(con)
{

}
 
void MyTask::process()
{
    //可以在process函数中进行业务逻辑的处理
    _msg = "helloReactorV5\n";
    

    _con->sendInLoop(_msg);
}

EchoServer::EchoServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port)
: _pool(threadNum, queSize)
, _server(ip, port)
{

}

EchoServer::~EchoServer()
{

}

void EchoServer::start()
{
    _pool.start();
    cout << "EchoServer:线程池启动" << endl;
    //注册所有回调函数
    using namespace std::placeholders;
    _server.setAllCallback(bind(&EchoServer::onNewConnection, this, _1),
                           bind(&EchoServer::onMessage, this, _1),
                           bind(&EchoServer::onClose, this, _1));
 
    cout << "EchoServer:Tcp服务器启动" << endl;
    _server.start();
}

void EchoServer::stop()
{
    _pool.stop();
    _server.stop();
}

//三个回调函数
//1.连接建立
void EchoServer::onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << "has connected!!!" << endl;
}

//2.消息到达
void EchoServer::onMessage(const TcpConnectionPtr &con)
{
    //接收客户端的数据
    string msg = con->receive();
    cout << ">>recv msg from client: " << msg;

    MyTask task(msg, con);

    _pool.addTask(bind(&MyTask::process, task));
}

//3.连接断开
void EchoServer::onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << "has closed!!!" << endl;
}

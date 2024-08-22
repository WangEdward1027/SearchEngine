#include "EchoServer.h"
#include <functional>
#include <iostream>
#include "../nlohmann/json.hpp"
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
    //在process函数中进行业务逻辑的处理
    nlohmann::json json_object = nlohmann::json::parse(_msg);      
    
    string type, context;
    for(auto &p: json_object.items()){
        type = p.key();
        context = p.value();
    }

    if(type == "1"){
        _msg = "客官要候选词推荐\n";    
        


    }else if(type == "2"){
        _msg = "客官要网页查询\n";

    }else{ //预防手段。实际上非1、2的type,已经在客户端进行拦截,不会发送到服务器
        cout << "type == " << type << "\n";
        _msg = "请输入正确的type\n";
    }

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

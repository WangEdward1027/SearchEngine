#include "TcpConnection.h"
#include "EventLoop.h"
#include <sstream>
#include <iostream>
using std::ostringstream;
using std::cout;
using std::endl;

TcpConnection::TcpConnection(int fd, EventLoop * loop)
: _loop(loop)
, _sock(fd)
, _sockIO(fd)
, _localAddr(getLocalAddr())
, _peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection()
{

}

string TcpConnection::receive()
{
    char buff[65535] = {0};
    _sockIO.readLine(buff, sizeof(buff));
    return string(buff);
}

void TcpConnection::send(const string & msg)
{
    _sockIO.writen(msg.c_str(), msg.size());
}

string TcpConnection::toString()
{
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();
    return oss.str();
}

//获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取本端的ip地址：getsockname
    int ret = getsockname(_sock.getFd(), (struct sockaddr *)&addr, &len);
    if(ret == -1){
        perror("getsockname");
    }
    return InetAddress(addr);
}

//获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    //获取对端地址的函数:getpeername
    int ret = getpeername(_sock.getFd(), (struct sockaddr *)&addr, &len);
    if(ret == -1){
        perror("getpeername");
    }
    return InetAddress(addr);
}


//回调函数的注册
void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback &cb)
{
    _onNewConnection = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback &cb)
{
    _onMessage = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback &cb)
{
    _onClose = cb;
}

//回调函数的执行
void TcpConnection::handleNewConnectionCallback()
{
    //该function对象是 function<void(const shared_ptr<TcpConnection> &)> 类型
    //故回调函数的参数应该是 const shared_ptr<TcpConnection> &
    if(_onNewConnection){
        /* _onNewConnection(shared_ptr<TcpConnection>(this));  //智能指针的误用 */
        _onNewConnection(shared_from_this());  //智能指针的误用
    }else{
        cout << "_onNewConnection == nullptr" << endl;
    }
}

void TcpConnection::handleMessageCallback()
{
    if(_onMessage){
        _onMessage(shared_from_this());  
    }else{
        cout << "_onMessage == nullptr" << endl;
    }
}

void TcpConnection::handleCloseCallback()
{
    if(_onClose){
        _onClose(shared_from_this());  
    }else{
        cout << "_onClose == nullptr" << endl;
    }
}


bool TcpConnection::isClosed() const
{
    char buf[10] = {0};
    int ret = ::recv(_sock.getFd(), buf, sizeof(buf), MSG_PEEK);
    return ret == 0;
}


//将有数据发送能力的TcpConnection对象、send函数、msg一起打包发给EventLoop
void TcpConnection::sendInLoop(const string &msg) //msg是线程池处理后的msg
{
    if(_loop){
        _loop->runInLoop(std::bind(&TcpConnection::send, this ,msg));
    }
}

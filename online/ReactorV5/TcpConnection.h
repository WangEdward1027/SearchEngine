#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include <memory>
#include <functional>
using std::shared_ptr;
using std::function;

class EventLoop;

class TcpConnection
: public std::enable_shared_from_this<TcpConnection>
{
    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr &)>;
public:
    explicit TcpConnection(int fd, EventLoop * loop); //加入了EventLoop的指针
    ~TcpConnection();
    string receive();
    void send(const string & msg);
    string toString();
    //回调函数的注册
    void setNewConnectionCallback(const TcpConnectionCallback &);
    void setMessageCallback(const TcpConnectionCallback &);
    void setCloseCallback(const TcpConnectionCallback &);
    //回调函数的执行
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
    //查看连接是否已经断开
    bool isClosed() const;

    void sendInLoop(const string &);
private:
    //获取本端地址与对端地址
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    EventLoop * _loop;  //让TcpConnection知道EventLoop的存在
    
    Socket _sock;
    
    //为了调试而加入的三个数据成员
    SocketIO _sockIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    //回调
    TcpConnectionCallback _onNewConnection; //连接建立
    TcpConnectionCallback _onMessage;  //消息到达(文件描述符可读)
    TcpConnectionCallback _onClose;    //连接断开
};

#endif

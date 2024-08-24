///
/// @file    TcpConnection.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-06-16 16:03:56
///

#ifndef __WD_TCPCONNECTION_HPP__
#define __WD_TCPCONNECTION_HPP__

#include "Noncopyable.hpp"

#include "InetAddress.hpp"
#include "Socket.hpp"
#include "SocketIO.hpp"

#include <functional>
#include <memory>

namespace se {

class EventLoop;
class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;

class TcpConnection : Noncopyable, public std::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(int fd, EventLoop* loop);
    ~TcpConnection();

    string receive();
    void send(const string& msg);
    void sendInLoop(const string& msg); //唤醒IO线程发送

    string toString() const;

    void setAllCallbacks(const TcpConnectionCallback& cb1,
        const TcpConnectionCallback& cb2,
        const TcpConnectionCallback& cb3)
    {
        _onConnection = cb1;
        _onMessage = cb2;
        _onClose = cb3;
    }

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
    bool isClosed() const;

private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    Socket _sock;
    SocketIO _sockIO;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    EventLoop* _loop;
    bool _shutdownWrite;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};

} //end of namespace se

#endif

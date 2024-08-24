///
/// @file    TcpServer.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-12-03 21:28:53
///

#ifndef __WD_TCPSERVER_HPP__
#define __WD_TCPSERVER_HPP__

#include "Acceptor.hpp"
#include "EventLoop.hpp"
#include "TcpConnection.hpp"

namespace se {

class TcpServer {
public:
    TcpServer(unsigned short port, const string& ip = "127.0.0.1")
        : _acceptor(port, ip)
        , _loop(_acceptor)
    {
    }

    void setAllCallbacks(TcpConnectionCallback&& cb1,
        TcpConnectionCallback&& cb2,
        TcpConnectionCallback&& cb3)
    {
        _loop.setAllCallbacks(std::move(cb1), std::move(cb2), std::move(cb3));
    }

    void start()
    {
        _acceptor.ready();
        _loop.loop();
    }

    void stop()
    {
        _loop.unloop();
    }

private:
    Acceptor _acceptor;
    EventLoop _loop;
};

} //end of namespace se

#endif

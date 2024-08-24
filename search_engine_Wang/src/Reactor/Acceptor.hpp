///
/// @file    Acceptor.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-06-16 15:14:55
///

#ifndef __WD_ACCEPTOR_HPP__
#define __WD_ACCEPTOR_HPP__

#include "InetAddress.hpp"
#include "Socket.hpp"

namespace se {

class Acceptor {
public:
    Acceptor(unsigned short port, const string& ip = "127.0.0.1")
        : _listensock()
        , _addr(port, ip)
    {
    }

    void ready();
    int accept();

    int fd() const { return _listensock.fd(); }

private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();

private:
    Socket _listensock;
    InetAddress _addr;
};

} //end of namespace se

#endif

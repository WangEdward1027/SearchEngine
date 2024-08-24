///
/// @file    TcpConnection.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-06-16 16:10:24
///

#include "TcpConnection.hpp"
#include "EventLoop.hpp"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <sstream>
#include <string.h>

namespace se {

TcpConnection::TcpConnection(int fd, EventLoop* loop)
    : _sock(fd)
    , _sockIO(fd)
    , _localAddr(getLocalAddr())
    , _peerAddr(getPeerAddr())
    , _loop(loop)
    , _shutdownWrite(false)
{
}

TcpConnection::~TcpConnection()
{
    //...
}

string TcpConnection::receive()
{
    char buff[65536] = { 0 };
    _sockIO.readline(buff, sizeof(buff));
    return string(buff);
}

void TcpConnection::send(const string& msg)
{
    _sockIO.writen(msg.c_str(), msg.size());
}

void TcpConnection::sendInLoop(const string& msg)
{
    if (_loop) {
        _loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
    }
}

bool TcpConnection::isClosed() const
{
    int ret = -1;
    char buff[64] = { 0 };
    do {
        ret = ::recv(_sock.fd(), buff, sizeof(buff), MSG_PEEK);
    } while (ret == -1 && errno == EINTR);
    return ret == 0;
}

InetAddress TcpConnection::getLocalAddr()
{
    struct sockaddr_in localaddr;
    socklen_t len = sizeof(localaddr);
    ::memset(&localaddr, 0, sizeof(localaddr));
    if (getsockname(_sock.fd(), (struct sockaddr*)&localaddr, &len) < 0) {
        perror("getsockname");
    }
    return InetAddress(localaddr);
}

InetAddress TcpConnection::getPeerAddr()
{
    struct sockaddr_in localaddr;
    socklen_t len = sizeof(localaddr);
    ::memset(&localaddr, 0, sizeof(localaddr));
    if (getpeername(_sock.fd(), (struct sockaddr*)&localaddr, &len) < 0) {
        perror("getsockname");
    }
    return InetAddress(localaddr);
}

string TcpConnection::toString() const
{
    std::ostringstream oss;
    oss << "tcp "
        << _localAddr.ip() << ":" << _localAddr.port() << " --> "
        << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
}

void TcpConnection::handleConnectionCallback()
{
    if (_onConnection) {
        _onConnection(shared_from_this());
    }
}

void TcpConnection::handleMessageCallback()
{
    if (_onMessage) {
        _onMessage(shared_from_this());
    }
}

void TcpConnection::handleCloseCallback()
{
    if (_onClose) {
        _onClose(shared_from_this());
    }
}

} //end of namespace se

///
/// @file    Acceptor.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-06-16 15:19:09
///

#include "Acceptor.hpp"

namespace se {
void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}
int accept();

void Acceptor::setReuseAddr()
{
    int on = 1;
    if (setsockopt(fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
        perror("setsockopt");
    }
}

void Acceptor::setReusePort()
{
    int on = 1;
    if (setsockopt(fd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) < 0) {
        perror("setsockopt");
    }
}

void Acceptor::bind()
{
    if (::bind(fd(), (struct sockaddr*)_addr.getInetAddressPtr(), sizeof(_addr)) < 0) {
        perror("bind");
    }
}

void Acceptor::listen()
{
    if (::listen(fd(), 128) < 0) {
        perror("listen");
    }
}

int Acceptor::accept()
{
    int peerfd = ::accept(fd(), nullptr, nullptr);
    if (peerfd < 0) {
        perror("accept");
    }
    return peerfd;
}

} //end of namespace se

#include "Acceptor.h"


Acceptor::Acceptor(const string & ip, unsigned short port)
: _sock()
, _addr(ip, port)
{

}

Acceptor::~Acceptor()
{
    
}

void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddr()
{
    int on = 1;
    int ret = setsockopt(_sock.getFd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if(ret == -1){
        perror("setsockopt");
        return;
    }
}

void Acceptor::setReusePort()
{
    int on = 1;
    int ret = setsockopt(_sock.getFd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
    if(-1 == ret){
        perror("setsockopt");
        return;
    }
}

void Acceptor::bind()
{
    int ret = ::bind(_sock.getFd(), (struct sockaddr*)_addr.getInetAddressPtr(), sizeof(struct sockaddr));
    if(ret == -1){
        perror("bind");
        return;
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_sock.getFd(), 128);
    if(ret == -1){
        perror("listen");
        return;
    }
}

int Acceptor::accept()
{
    int connfd = ::accept(_sock.getFd(), nullptr, nullptr);
    if(connfd == -1){
        perror("accept");
        return -1;
    }
    return connfd;
}

int Acceptor::getfd() const
{
   return _sock.getFd();
}

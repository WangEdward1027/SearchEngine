 ///
 /// @file    Socket.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-06-16 15:01:45
 ///
 
#include "Socket.hpp"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>

namespace se
{

Socket::Socket()
{
	_fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if(_fd < 0) {
		::perror("socket");
	}
}

Socket::Socket(int fd)
: _fd(fd)
{}

Socket::~Socket()
{
	::close(_fd);
}

void Socket::shutdownWrite()
{
	::shutdown(_fd, SHUT_WR);
}

void Socket::setNonblock()
{
	int flags = ::fcntl(_fd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	::fcntl(_fd, F_SETFL, flags);
}

}//end of namespace se

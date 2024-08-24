 ///
 /// @file    InetAddress.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-06-16 14:35:49
 ///
 
#include "InetAddress.hpp"

#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

namespace se
{

InetAddress::InetAddress(unsigned short port, const string & ip)
{
	::memset(&_addr, 0, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const struct sockaddr_in & addr)
: _addr(addr)
{}

string InetAddress::ip() const
{
	return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const
{
	return ntohs(_addr.sin_port);
}


}//end of namespace se

 ///
 /// @file    InetAddress.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-06-16 14:29:18
 ///
 
#ifndef __WD_INETADDRESS_HPP__
#define __WD_INETADDRESS_HPP__

#include <netinet/in.h>
#include <string>
using std::string;

namespace se
{

class InetAddress
{
public:
	InetAddress(unsigned short port, const string & ip = "127.0.0.1");
	InetAddress(const struct sockaddr_in & addr);
	string ip() const;
	unsigned short port() const;

	struct sockaddr_in * getInetAddressPtr() {	return &_addr;	}

private:
	struct sockaddr_in _addr;
};

}//end of namespace se
 
 
 
#endif

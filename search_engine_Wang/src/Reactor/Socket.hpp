 ///
 /// @file    Socket.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-06-16 14:55:01
 ///
 
#ifndef __WD_SOCKET_HPP__
#define __WD_SOCKET_HPP__

#include "Noncopyable.hpp"

namespace se
{

class Socket : Noncopyable
{
public:
	Socket();
	explicit Socket(int fd);
	~Socket();

	int fd() const {	return _fd;	}
	void shutdownWrite();
	void setNonblock();

private:
	int _fd;
};

}//end of namespace se
 
 
 
#endif

///
/// @file    SocketIO.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-06-16 16:07:36
///

#ifndef __WD_SOCKETIO_HPP__
#define __WD_SOCKETIO_HPP__

namespace se {

class SocketIO {
public:
    SocketIO(int fd)
        : _fd(fd)
    {
    }

    int readn(char* buff, int len);
    int readline(char* buff, int maxlen);
    int writen(const char* buff, int len);
    int getFd() { return _fd; };

private:
    int _fd;
};

} //end of namespace se

#endif

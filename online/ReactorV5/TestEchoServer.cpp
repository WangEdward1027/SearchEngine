//启动服务器:  g++ *.cpp -pthread    ./a.out
//启动客户端:  nc 127.0.0.1 8888 

#include "EchoServer.h"

int main()
{
    EchoServer server(4, 10, "127.0.0.1", 8888);
    server.start();
    return 0;
}

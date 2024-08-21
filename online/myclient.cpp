#include <sys/types.h>   //对<sys/socket.h>的补充,确保某些旧系统移植性。非必需
#include <sys/socket.h>  //socket()、connect()
#include <stdio.h>       //perror()
#include <arpa/inet.h>   //struct sockaddr_in
#include <string.h>      //memset()
#include <stdlib.h>      //atoi()
#include <unistd.h>      //close()
#include <iostream>      
#include <string>
using std::cout;
using std::cin;
using std::cerr;
using std::string;

int main(int argc, char *argv[])
{
    //0.命令行参数判断
    if(argc != 3){
        cerr << "Usage : ./client IP port\n";
        cout << "请重新输入\n";
        return 1;
    }

    //1.创建套接字
    int listenfd =socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("socket");
        return -1;
    }

    //2.初始化服务器地址结构体
    struct sockaddr_in server_addr;
    memset(&server_addr, 0 ,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]); //要连接的服务器的IP地址
    server_addr.sin_port = htons(atoi(argv[2]));      //要连接的服务器的端口号
    
    //3.连接服务器
    int ret = connect(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret == -1){
        perror("connect");
        close(listenfd);
        return -1;
    }
    
    //4.数据传输
    while(1){
        //读取用户输入
        cout << "Input: ";
        string line;
        getline(cin, line);       
        line += "\n";

        //发送数据到服务器
        int len = send(listenfd, line.c_str(), line.size(), 0); //send()默认是阻塞式的
        if(len == -1){
            cerr << "len == -1, 发送失败\n";
        }else if(len == 0){
            cout << "len == 0\n";
        }else{
            cout << "len = " << len << ", 客户端发送正常。\n";
        }
        
        //读取服务器返回的数据
        char buffer[256] = {};
        len = recv(listenfd, buffer, sizeof(buffer), 0);
        if(len == -1){
            perror("recv() error");
            break;
        }else if(len == 0){
            cout << "len == 0\n";
        }else{
            cout << "recv msg from server: " << buffer << "\n";
        }
    }
    
    //5.关闭套接字
    close(listenfd);
    return 0;
}

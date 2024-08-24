#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include "ThreadPool.h"
#include "TcpServer.h"
#include "../Dictionary.h"
#include <set>
using std::set;

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con);
    void process();
private:
    string _msg;
    TcpConnectionPtr _con;

    //关键词分解成一个个字符
    vector<string> _character;
    //每个字符对应的候选词集合
    map<string,set<string>> _candidetaWordSet;
    //字典类(预热,加载到内存)        
    Dictionary _dict;                        
};

class EchoServer
{
public:
    EchoServer(size_t threadNum, size_t queSize, const string & ip, unsigned short port);
    ~EchoServer();

    void start();
    void stop();

    void onNewConnection(const TcpConnectionPtr &con);
    void onMessage(const TcpConnectionPtr &con);
    void onClose(const TcpConnectionPtr &con);

private:
    ThreadPool _pool;
    TcpServer _server;
};

#endif


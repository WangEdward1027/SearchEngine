#ifndef __MAINLOOPSERVER_H__
#define __MAINLOOPSERVER_H__

#include "../../src/Reactor/MyLogger.hpp"
#include "../../src/Reactor/TcpServer.hpp"
#include "../../src/Reactor/Threadpool.hpp"

#include "Configuration.hpp"
#include "SearchTask.hpp"

#include <unistd.h>

#include <iostream>

using namespace std;
using std::placeholders::_1;

class EchoServer {
public:
    EchoServer(unsigned short port, const string ip = "127.0.0.1")
        : _threadpool(std::stoi(se::Configuration::getInstance()->getConfigValue("num_of_thread")))
        , _server(port, ip)
    {
        using namespace std::placeholders;
        _server.setAllCallbacks(
            std::bind(&EchoServer::onConnection, this, _1),
            std::bind(&EchoServer::onMessage, this, _1),
            std::bind(&EchoServer::onClose, this, _1));
    }

    void onConnection(const se::TcpConnectionPtr& conn)
    {
        log_i("\n%s has connected!\n", conn->toString().c_str());
    }

    void onMessage(const se::TcpConnectionPtr& conn)
    {
        //1.接收数据
        string msg = conn->receive();
        if (msg.empty()) {
            cout << "client drop" << endl;
            return;
        }
        //2.将数据封装成一个任务，交给线程池处理
        ::SearchTask task(msg, conn);
        _threadpool.addTask(
            std::bind(&SearchTask::process, task));
    }

    void onClose(const se::TcpConnectionPtr& conn)
    {
        log_i("\n%s has closed.\n", conn->toString().c_str());
    }

    void start()
    {
        _threadpool.start();
        _server.start();
    }

private:
    se::Threadpool _threadpool;
    se::TcpServer _server;
};

#endif
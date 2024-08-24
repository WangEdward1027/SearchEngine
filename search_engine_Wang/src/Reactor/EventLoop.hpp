///
/// @file    EventLoop.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-12-03 20:24:00
///

#ifndef __WD_EVENTLOOP_HPP__
#define __WD_EVENTLOOP_HPP__

#include "MutexLock.hpp"

#include <sys/epoll.h>

#include <functional>
#include <map>
#include <memory>
#include <vector>
using std::map;
using std::vector;

namespace se {

class Acceptor;

class TcpConnection;
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
using Functor = std::function<void()>;

class EventLoop {
public:
    EventLoop(Acceptor& acceptor);
    ~EventLoop();

    void loop();
    void unloop();
    void runInLoop(Functor&& cb);

    void setAllCallbacks(TcpConnectionCallback&& cb1,
        TcpConnectionCallback&& cb2,
        TcpConnectionCallback&& cb3)
    {
        _onConnection = std::move(cb1);
        _onMessage = std::move(cb2);
        _onClose = std::move(cb3);
    }

private:
    void waitEpollFd();
    void handleNewConnection();
    void handleMessage(int);

    int createEpollfd();
    void addEpollReadfd(int fd);
    void delEpollReadfd(int fd);

    int createEventfd();
    void handleRead();
    void wakeup();
    void doPendingFunctors();

private:
    int _efd;
    int _eventfd;
    Acceptor& _acceptor;
    bool _isLooping;
    vector<struct epoll_event> _evtList;
    map<int, TcpConnectionPtr> _conns;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;

    //存储的是计算线程交给IO线程要执行的任务
    vector<Functor> _pendingFunctors;
    MutexLock _mutex;
};

} //end of namespace se

#endif

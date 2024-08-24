///
/// @file    EventLoop.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-12-03 20:27:01
///
#include "MyLogger.hpp"

#include "EventLoop.hpp"
#include "Acceptor.hpp"
#include "TcpConnection.hpp"

#include <sys/eventfd.h>
#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace se {

EventLoop::EventLoop(Acceptor& acceptor)
    : _efd(createEpollfd())
    , _eventfd(createEventfd())
    , _acceptor(acceptor)
    , _isLooping(false)
    , _evtList(1024)
{
    addEpollReadfd(_acceptor.fd());
    addEpollReadfd(_eventfd);
}

EventLoop::~EventLoop()
{
    close(_efd);
}

//loop方法代表的是IO线程
void EventLoop::loop()
{
    _isLooping = true;
    while (_isLooping) {
        waitEpollFd();
    }
}

//runInLoop要与loop方法运行在不同的线程
void EventLoop::runInLoop(Functor&& cb)
{
    //先注册
    {
        MutexLockGuard autolock(_mutex);
        _pendingFunctors.push_back(std::move(cb));
    }
    //再通知（唤醒）
    wakeup();
    // log_d(">> wakeup IO thread");
    // cout << ">> wakeup IO thread" << endl;
}
//unloop要与loop运行在不同的线程
void EventLoop::unloop() { _isLooping = false; }

void EventLoop::waitEpollFd()
{
    int nready = 0;
    do {
        //nready = epoll_wait(_efd, &_evtList[0], _evtList.size(), 5000);
        nready = epoll_wait(_efd, &*_evtList.begin(), _evtList.size(), 10000);
    } while (nready == -1 && errno == EINTR);

    if (nready == -1) {
        log_e("epoll_wait");
        perror("epoll_wait");
        return;
    } else if (nready == 0) {
        log_v("epoll_wait timeout");
        // printf("epoll_wait timeout\n");
    } else { //nready > 0
        if ((size_t)nready == _evtList.size()) {
            _evtList.resize(2 * nready);
        }

        //对就绪的文件描述符进行遍历
        for (int idx = 0; idx != nready; ++idx) {
            int fd = _evtList[idx].data.fd;
            if (fd == _acceptor.fd()) {
                if (_evtList[idx].events & EPOLLIN) {
                    handleNewConnection();
                }
            } else if (fd == _eventfd) {
                if (_evtList[idx].events & EPOLLIN) {
                    handleRead();
                    // log_d("doPendingFunctors()");
                    // cout << "doPendingFunctors()" << endl;
                    doPendingFunctors();
                }

            } else { //已经建立好的连接
                if (_evtList[idx].events & EPOLLIN) {
                    handleMessage(fd);
                }
            }
        }
    }
}

void EventLoop::handleNewConnection()
{
    int peerfd = _acceptor.accept();
    addEpollReadfd(peerfd); //添加监听

    TcpConnectionPtr conn(new TcpConnection(peerfd, this));
    conn->setAllCallbacks(_onConnection, _onMessage, _onClose);
    _conns.insert(std::make_pair(peerfd, conn));

    //执行连接建立时的回调函数
    conn->handleConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
    //0. 查找到相应的TcpConnection对象
    auto iter = _conns.find(fd);
    if (iter != _conns.end()) {
        //1. 先判断一下连接是否断开
        bool isClosed = iter->second->isClosed();
        if (isClosed) {
            //2. 如果连接断开
            iter->second->handleCloseCallback();
            delEpollReadfd(fd);
            _conns.erase(iter);
        } else {
            //3. 没有断开时，处理消息
            iter->second->handleMessageCallback();
        }
    }
}

int EventLoop::createEpollfd()
{
    int ret = ::epoll_create1(0);
    if (ret < 0) {
        perror("epoll_create1");
    }
    return ret;
}

void EventLoop::addEpollReadfd(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_efd, EPOLL_CTL_ADD, fd, &evt);
    if (ret < 0) {
        perror("epoll_ctl");
    }
}

void EventLoop::delEpollReadfd(int fd)
{
    struct epoll_event evt;
    evt.data.fd = fd;
    evt.events = EPOLLIN;

    int ret = epoll_ctl(_efd, EPOLL_CTL_DEL, fd, &evt);
    if (ret < 0) {
        perror("epoll_ctl");
    }
}

int EventLoop::createEventfd()
{
    int fd = eventfd(0, 0);
    if (fd < 0) {
        perror("eventfd");
    }
    return fd;
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    int ret = write(_eventfd, &one, sizeof(one));
    if (ret != sizeof(one)) {
        perror("write");
    }
}

void EventLoop::handleRead()
{
    uint64_t howmany = 0;
    int ret = read(_eventfd, &howmany, sizeof(howmany));
    if (ret != sizeof(howmany)) {
        perror("read");
    }
}

void EventLoop::doPendingFunctors()
{
    vector<Functor> tmp;
    {
        MutexLockGuard autolock(_mutex);
        tmp.swap(_pendingFunctors); //O(1)
    }

    //执行回调函数
    for (auto& f : tmp) {
        // log_d("IO send\n");
        f();
    }
}

} //end of namespace se

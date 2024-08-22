#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <iostream>
#include <string>
#include <utility> //std::move()
using std::cerr;
using std::cout;
using std::endl;
using std::string;

EventLoop::EventLoop(Acceptor &acceptor)
: _epfd(createEpollFd())
, _evtfd(createEventFd())
, _evtList(1024)
, _isLooping(false)
, _acceptor(acceptor) //引用数据成员,必须在构造函数的初始化列表中进行初始化
{
    //需要将listenfd放在红黑树上进行监听
    int listenfd = acceptor.getfd();
    addEpollReadFd(listenfd);
    addEpollReadFd(_evtfd);
}

EventLoop::~EventLoop()
{
    close(_epfd);
}

//是否在循环
void EventLoop::loop()
{
    _isLooping = true;
    while(_isLooping){
        waitEpollFd();
    }
}

void EventLoop::unloop()
{
    _isLooping = false;
}

//封装epoll_wait
void EventLoop::waitEpollFd()
{   
    //获取vector第一个元素的首地址
    int nready = 0;
    do{
        nready = ::epoll_wait(_epfd, &_evtList[0], _evtList.size(), 10000); //10秒超时
    }while(-1 == nready && errno == EINTR);
    
    if(-1 == nready){
        cerr << "" << endl;
        return;
    }else if(0 == nready){
        cout << ">>epoll_wait timeout!!" << endl;
    }else{
        //为了防止文件描述符的数目超过1024,可以手动扩容
        if(nready == (int)_evtList.size()){
            _evtList.resize(2 * nready);
        }

        for(int idx = 0; idx < nready; ++idx){
            int fd = _evtList[idx].data.fd;
            int listenfd = _acceptor.getfd();
            
            //1.新连接
            if(fd == listenfd)
            {   
                cout << "新连接" << endl;
                handleNewConnection(); 
            }
            //2.线程池发来处理后的msg
            else if(fd == _evtfd)
            {
                cout <<  "epoll_wait监测到_evtfd,线程池完成业务处理\n\n";
                handleRead();
                //做任务,遍历vector,即用TcpConnection对象send() msg
                doPendingFunctors();
            }
            //3.客户端发来消息
            else
            {
                cout << "客户端发来消息" << endl;
                handleMessage(fd); 
            }
        }
    }
}

//处理新连接
void EventLoop::handleNewConnection()
{
    //如果connfd是正常的,表明三次握手成功
    int connfd = _acceptor.accept();
    if(connfd < 0){
        perror("handleNewConnection");
        return;
    }

    //将文件描述符connfd放在红黑树上进行监听
    addEpollReadFd(connfd);

    //三次握手成功,创建TcpConnection连接
    //用connfd创建TcpConnection对象,并交由智能指针con进行管理
    TcpConnectionPtr con(new TcpConnection(connfd, this));
 
    //可以在此处将EventLoop中的三个数据成员传递给TcpConnection对象
    con->setNewConnectionCallback(_onNewConnectionCb);
    con->setMessageCallback(_onMessageCb);
    con->setCloseCallback(_onCloseCb);

    //存储文件描述符与连接TcpConnection键值对
    /* _conns.insert({connfd,con}); */
    _conns[connfd] = con;

    //连接已经建立了,就可以执行连接建立的事件
    con->handleNewConnectionCallback();
}

void EventLoop::handleMessage(int fd)
{
    auto it = _conns.find(fd);
    if(it != _conns.end())
    {
        bool flag = it->second->isClosed();  //TcpConnection的成员函数
        if(flag) //连接已经断开
        {
            it->second->handleCloseCallback(); //处理连接断开的事件
            delEpollReadFd(fd); //连接断开需要将文件描述符从红黑树上摘除
            _conns.erase(it); //再将文件描述符与连接的键值对从map中删除
        }
        else //连接未断开,处理消息
        {
            it->second->handleMessageCallback(); 
        }
    }
    else
    {
        cout << "连接不存在" << endl;
        return;
    }
}

//封装epoll_create函数
int EventLoop::createEpollFd()
{
    int fd = ::epoll_create(1);
    if(fd < 0){
        perror("createEpollFd");
        return -1;
    }
    return fd;
}

//将文件描述符放在红黑树上进行监听
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if(ret < 0){
        perror("addEpoolReadFd");
        return;
    }
}

//将文件描述符从红黑树上取消监听
void EventLoop::delEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = ::epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &evt);
    if(ret < 0){
        perror("delEpoolReadFd");
        return;
    }
}


//处理三个回调函数
void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb)
{
    _onNewConnectionCb = std::move(cb); 
}

void EventLoop::setMessageCallback(TcpConnectionCallback &&cb)
{
    _onMessageCb = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback &&cb)
{
    _onCloseCb = std::move(cb);
}


//eventfd相关的三个函数
//1.创建用于ThreadPool和Reactor进行通信的文件描述符
int EventLoop::createEventFd()
{
    int evtfd = eventfd(0,0);
    if(evtfd < 0){
        perror("createEventfd");
        return -1;
    }
    return evtfd;
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t)){
        perror("wakeup");
        return;
    }
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t ret = read(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t)){
        perror("handleRead");
        return;
    }
}


//Reactor处理ThreadPool发来的数据:遍历vector<Functors>
void EventLoop::doPendingFunctors()
{
    vector<Functors> tmp;
    {
        lock_guard<mutex> lg(_mutex);
        tmp.swap(_pendings);
    }

    for(auto &cb : tmp)
    {
        //此处的"任务"就是线程池处理好之后的msg
        //以及发送msg的链接TcpConnection的对象
        //以及有发送数据能力的send函数
        cb();  //执行的"任务",即是TcpConnection对象执行send()
    }
}

void EventLoop::runInLoop(Functors && cb)
{
    //控制锁的粒度(范围)
    {
        lock_guard<mutex> lg(_mutex);
        _pendings.push_back(std::move(cb));
    }

    wakeup();  //write eventfd
}

///
/// @file    Thread.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-11-29 17:39:28
///

#include "Thread.hpp"
// #include "../Cache/LRUCache.h"

namespace se {

static __thread int thread_id;

Thread::Thread(ThreadCallback&& cb, std::string name, int id)
    : _isRunning(false)
    , _id(id)
    , _name(name)
    , _cb(std::move(cb))
{
    thread_id = _id;
}

Thread::~Thread()
{
    if (_isRunning) {
        pthread_detach(_pthid);
        _isRunning = false;
    }
}

void Thread::start()
{
    //第四个参数要传递本对象过去
    pthread_create(&_pthid, nullptr, threadFunc, this);
    _isRunning = true;
}

void* Thread::threadFunc(void* arg)
{ //子线程的入口函数，在这里应该调用run方法
    // 执行任务, 由于静态函数没有this指针，因此
    // 需要通过参数传递
    Thread* pthread = static_cast<Thread*>(arg);
    if (pthread) {
        pthread->_cb();
    }
    return nullptr;
}

void Thread::join()
{
    if (_isRunning) {
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
}

} //end of namesapce se

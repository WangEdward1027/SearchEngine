#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
using std::queue;
using std::mutex;
using std::condition_variable;
using std::function;

using ElemType = function<void()>; //基于对象

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    
    void push(ElemType &&task);
    ElemType pop();
    bool empty();
    bool full();
    void wakeup();

private:
    size_t _queSize;
    queue<ElemType> _que;
    mutex _mutex;
    condition_variable _notEmpty;
    condition_variable _notFull;
    bool _flag; //判断
};

#endif

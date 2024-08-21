#include "TaskQueue.h"
#include <iostream> 
#include <mutex>
using std::cout;
using std::endl;
using std::unique_lock;

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty()
, _notFull()
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

void TaskQueue::push(ElemType &&task)
{
    unique_lock<mutex> ul(_mutex);
    while(full()){
        _notFull.wait(ul);
    }
    _que.push(std::move(task));
    ul.unlock();
    _notEmpty.notify_one();
}

ElemType TaskQueue::pop()
{
    unique_lock<mutex> ul(_mutex); //1.上锁
    //2.判空:如果任务队列为空.则阻塞等待(睡眠)
    while(empty() && _flag)
    {   
        _notEmpty.wait(ul);
    }
    
    if(_flag){ //empty()==false,队列非空导致跳出while
        ElemType tmp = _que.front(); //3.非空,获取数据,唤醒消费者
        _que.pop();
        _notFull.notify_one();
        return tmp;
    }else{ //如果在等待期间_flag变为false，直接返回一个空任务
        return nullptr;
    }
}

bool TaskQueue::empty() //const
{
    return 0 == _que.size();
}

bool TaskQueue::full() //const
{
    return _queSize == _que.size();
}

//将所有等待在_notEmpty条件变量上的线程全部唤醒
void TaskQueue::wakeup()
{
    _flag = false; //全部唤醒,为了使得pop能跳出while
    _notEmpty.notify_all();
}

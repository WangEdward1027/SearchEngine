#include "ThreadPool.h"
#include <iostream> 
#include <thread>
using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _threads()
, _queSize(queSize)
, _taskQue(queSize) 
, _isExit(false)
{
    
}

ThreadPool::~ThreadPool()
{

}

void ThreadPool::start()
{
    //需要创建出线程:线程创建出来之后需要执行线程入口函数
    for(size_t i = 0; i < _threadNum; ++i){
        //创建线程,并存进容器
        /* thread th(&ThreadPool::doTask, this); */
        /* _threads.push_back(std::move(th)); */
        _threads.push_back(thread(&ThreadPool::doTask,this)); //相当于上面两行
    }
}

//主线程4:线程池退出
void ThreadPool::stop()
{
    //需要保证子线程将任务执行完毕之后,主线程才能继续向下执行
    //关闭线程池,否则卡在此处
    while(!_taskQue.empty()){ //若任务队列没有被取空,就睡眠
        //卡在这里
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    //需要将所有可能在_notEmpty条件变量上的线程唤醒
    /* _notEmpty.notify_all(); */
    _taskQue.wakeup();

    //线程池要退出来了，可以将标志位设为true。然后回收工作线程
    _isExit = true;

    for(auto &th : _threads){
        th.join(); //回收子线程
    }
}

//添加任务 
void ThreadPool::addTask(Task &&task){
    if(task){
        _taskQue.push(std::move(task));
    }
}

//获取任务
Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

//线程池交给工作线程执行的任务
//子线程:入口函数
void ThreadPool::doTask()
{
    //只要任务队列不为空,就让线程池的工作子线程循环获取任务并执行任务
    //第一种:这样不对。若任务执行完了,任务队列为空,就跳出while循环了,子线程就退出了。若又来任务就不对了。
    while(!_isExit){
        Task taskcb = getTask(); //1.获取任务
        if(taskcb){
            taskcb(); //函数对象,执行任务,回调了注册的函数process
        }else{
            cout << "ptask == nullptr" << endl;
        }
    }
}

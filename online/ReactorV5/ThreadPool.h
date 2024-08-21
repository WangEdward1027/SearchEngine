#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
using std::vector;
using std::thread;
using std::function;

using Task = function<void()>; //基于对象

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task &&task); //添加任务
    Task getTask();           //获取任务
    void doTask();   //线程池交给工作线程执行的任务

private:
    size_t _threadNum;       //子线程的数目
    vector<thread> _threads; //存放子线程的容器
    size_t _queSize;         //任务队列的大小
    TaskQueue _taskQue;      //存放任务的任务队列。成员子对象,只能写头文件,不能写前向声明
    bool _isExit;            //表示线程池是否退出   
};

#endif

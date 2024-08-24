///
/// @file    Threadpool.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-12-01 11:14:18
///

#include "MyLogger.hpp"

#include "Thread.hpp"
#include "Threadpool.hpp"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::to_string;

namespace se {

Threadpool::Threadpool(size_t threadNum, size_t capacity)
    : _threadNum(threadNum)
    , _capacity(capacity)
    , _que(_capacity)
    , _isExit(false)
{
    _threads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
    if (!_isExit) {
        stop();
    }
}

void Threadpool::addTask(Task&& task)
{
    if (task)
        _que.push(std::move(task));
}

void Threadpool::start()
{
    //让每一个子线程运行起来
    using std::placeholders::_1;
    for (size_t idx = 0; idx != _threadNum; ++idx) {
        unique_ptr<Thread> up(new Thread(
            std::bind(&Threadpool::workerDoTask, this),
            std::string("Worker thread ") + to_string(thread_id_cnt), thread_id_cnt++));
        _threads.push_back(std::move(up));
    }

    for (auto& pthread : _threads) {
        pthread->start();
    }
}

Task Threadpool::getTask()
{
    return _que.pop();
}

//停止线程池的运行
void Threadpool::stop()
{
    if (!_isExit) {
        //1. 判读任务队列之中是否还有任务
        while (!_que.empty()) {
            sleep(1);
        }

        //2. 任务队列为空之后，再退出
        _isExit = true;
        _que.wakeup();

        for (auto& pthread : _threads) {
            pthread->join();
        }
    }
}

//每一个工作线程的任务
void Threadpool::workerDoTask()
{
    while (!_isExit) {
        //从任务队列中获取任务，并执行
        //
        //当任务执行的速度过快时，在stop还没有来得及
        //将_isExit设置为true，子线程就已经在getTask
        //方法之上阻塞了, 就会导致线程池无法正常退出
        Task task = getTask();
        if (task) {
            // log_d("do task");
            task();
        }
    }
}

} //end of namespace se

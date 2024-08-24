///
/// @file    Threadpool.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-12-01 11:09:45
///

#ifndef __WD_THREADPOOL_HPP__
#define __WD_THREADPOOL_HPP__

#include "Task.hpp"
#include "TaskQueue.hpp"

#include <memory>
#include <vector>
using std::unique_ptr;
using std::vector;

namespace se {

class Thread;
class Threadpool {
public:
    // friend class WorkerThread;
    Threadpool(size_t threadNum = 3, size_t que_capa = 10000);
    ~Threadpool();

    void addTask(Task&&);
    void start();
    void stop();

private:
    void workerDoTask();
    Task getTask();

private:
    size_t _threadNum;
    size_t _capacity;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _que;
    bool _isExit;

    int thread_id_cnt = 0;
};

} //end of namespace se

#endif

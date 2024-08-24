///
/// @file    Thread.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-11-29 17:37:23
///

#ifndef __WD_THREAD_HPP__
#define __WD_THREAD_HPP__

#include <functional>
#include <pthread.h>

#include <memory>

class LRUCache;

namespace se {

class Thread {
public:
    using ThreadCallback = std::function<void()>;

    Thread(ThreadCallback&& cb, std::string name = "", int id = 0);
    ~Thread();

    void start();
    void join();

    int getId() { return _id; }
    std::string getName() { return _name; }

private:
    static void* threadFunc(void*);

private:
    bool _isRunning;
    int _id;
    std::string _name;
    pthread_t _pthid;
    ThreadCallback _cb;
};

} //end of namespace se

#endif

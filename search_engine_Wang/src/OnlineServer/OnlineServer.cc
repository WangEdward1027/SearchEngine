
#include "../../include/Cache/CacheManger.h"
#include "../../include/Cache/TimerListener.h"
#include "../../include/OnlineServer/MainLoopServer.hpp"
#include "../../include/OnlineServer/SearchTask.hpp"
#include "../Reactor/MyLogger.hpp"

#include <functional>
#include <iostream>
#include <unistd.h>

using namespace std;

using std::placeholders::_1;

se::Threadpool* gThreadpool = nullptr;
se::MyLogger* se::MyLogger::_instance = nullptr;
pthread_once_t se::CacheManger::once = PTHREAD_ONCE_INIT;
se::CacheManger* se::CacheManger::_instance = nullptr;

__thread int pthread_id = 0;

int main(void)
{
    auto logger = se::MyLogger::getInstance();

    logger->setLevel("ALL");
    logger->start();
    se::TimerListener timer_listener;

    auto manager = se::CacheManger::getInstance();
    se::TimerTask task(
        std::bind(&se::CacheManger::updateCache, manager),
        10, "update cache");
    timer_listener.addTimerTask(task);

    se::TimerTask task2(
        []() { cout << "hello" << endl; },
        25, "say hello");
    timer_listener.addTimerTask(task2);

    log_i("Server Start!\n");
    EchoServer server(8888);
    timer_listener.start();
    server.start();

    return 0;
}

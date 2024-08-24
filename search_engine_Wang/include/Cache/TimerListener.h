#ifndef __TIMERLISTENR_H__
#define __TIMERLISTENR_H__

#include "./TimerTask.hpp"

#include <pthread.h>
#include <unistd.h>

#include <algorithm>
#include <functional>
#include <list>
#include <vector>

using std::list;
using std::pair;
using std::vector;

namespace se {

class TimerListener {
public:
    TimerListener(int capacity = 20);

    ~TimerListener() { close(_timerfd); }

    void start();
    void stop();

    bool _is_running;

    int _timerfd;
    int _cur;
    int _capacity;
    pthread_t pid;

    vector<list<pair<int, TimerTask>>> wheel_list;

    int validPos(int value);
    int getRound(const TimerTask& task);

    void addTimerTask(const TimerTask& task);
    void delTimerTask(string task_name);

    static void* ListenerFunc(void* p);

private:
};

}

#endif

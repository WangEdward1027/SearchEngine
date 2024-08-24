#include "../../include/Cache/TimerListener.h"
#include "../../src/Reactor/MyLogger.hpp"

#include <iostream>
#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/timerfd.h>
#include <unistd.h>

using std::cout;
using std::endl;

namespace se {

TimerListener::TimerListener(int capacity)
    : _is_running(false)
    , _cur(0)
    , _capacity(capacity)
{
    wheel_list.resize(_capacity);
}

int TimerListener::getRound(const TimerTask& task)
{
    return task.getInterval() / _capacity;
}

int TimerListener::validPos(int value)
{
    return (value + _capacity) % _capacity;
}

void TimerListener::addTimerTask(const TimerTask& task)
{
    wheel_list[validPos(_cur + task.getInterval())].emplace_back(getRound(task), task);
}

void TimerListener::delTimerTask(string task_name)
{
    for (auto& pos_list : wheel_list) {
        pos_list.remove_if(
            [&](pair<int, TimerTask>& kv) -> bool {
                return task_name == kv.second.getName();
            });
    }
}

void TimerListener::start()
{
    _timerfd = timerfd_create(0, 0);
    struct itimerspec tv;
    memset(&tv, 0, sizeof(tv));
    tv.it_value.tv_sec = 3; // 第一次到期
    tv.it_value.tv_nsec = 0;
    tv.it_interval.tv_sec = 1; // 到期间隔
    tv.it_interval.tv_nsec = 0;
    if (timerfd_settime(_timerfd, 0, &tv, NULL) == -1) {
        perror("timerfd_settime");
    }
    _is_running = true;
    log_i("TimerListener Start!");
    pthread_create(&pid, NULL, &TimerListener::ListenerFunc, this);
}

void TimerListener::stop()
{
    _is_running = false;
}

void* TimerListener::ListenerFunc(void* p)
{
    TimerListener* _this = static_cast<TimerListener*>(p);

    struct pollfd pfd;
    pfd.fd = _this->_timerfd;
    pfd.events = POLLIN;

    while (_this->_is_running) {
        int nready = poll(&pfd, 1, 2000);
        if (nready == 0) {
            continue;
        } else if (nready == -1) {
            perror("timer poll");
        } else if (pfd.revents & POLLIN) {
            uint64_t num = 0;
            int ret = ::read(pfd.fd, &num, sizeof(num)); // 超时次数，一般为1
            if(ret<0) {
                perror("timer read");
                break;
            }
            _this->_cur = _this->validPos(_this->_cur + num); // 当前时刻+num

            if (_this->_cur % 5 == 0)
                log_v("timer wakeup cur = %d", _this->_cur);
            do {
                auto& cur_list = _this->wheel_list[_this->validPos(_this->_cur - num)];

                for (auto it = cur_list.begin(); it != cur_list.end();) {
                    if (it->first == 0) {
                        // 在当前轮次执行
                        log_i("do task [%s]", it->second.getName().c_str());
                        it->second.run();

                        if (it->second.isRepeatable()) {
                            // 需重复执行的任务
                            _this->addTimerTask(it->second);
                        }
                        it = cur_list.erase(it);
                    } else {
                        --(it->first); // 轮数-1
                        ++it;
                    }
                }
            } while (--num > 0); // 防止某次操作时间过长导致超时两次
        }
    }
    return _this;
}
}
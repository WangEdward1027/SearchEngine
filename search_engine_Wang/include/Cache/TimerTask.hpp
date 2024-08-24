#include <functional>
#include <string>
using std::function;
using std::string;
using std::to_string;

namespace se {

typedef function<void()> Task;

class TimerTask {
public:
    TimerTask(const Task& task, int interval, string name = "", bool repeat = true)
        : _repeat(repeat)
        , _interval(interval)
        , _name(name)
        , _task(task)
    {
        if (_name.empty()) {
            _name = "TimerTask" + to_string(interval) + to_string(repeat);
        }
    }

    int getInterval() const { return _interval; }
    bool isRepeatable() const { return _repeat; }
    string getName() const { return _name; }

    void run()
    {
        _task();
    }

    bool _repeat;
    int _interval;
    string _name;
    Task _task;

    bool operator==(const TimerTask& rhs) const
    {
        return _name == rhs._name;
    }
};

}

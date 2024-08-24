#ifndef __MYLOGGER_H__
#define __MYLOGGER_H__

#include "../Reactor/Noncopyable.hpp"

#include <elog.h>
#include <map>
#include <stdio.h>

namespace se {

class MyLogger : Noncopyable {
public:
    static MyLogger* getInstance()
    {
        if (_instance) {
            return _instance;
        }
        return new MyLogger;
    }

    static MyLogger* _instance;

    void setLevel(std::string level = "ALL")
    {
        std::map<std::string, int> level_map{
            { "ERROR", ELOG_LVL_ERROR },
            { "WARN", ELOG_LVL_WARN },
            { "INFO", ELOG_LVL_INFO },
            { "DEBUG", ELOG_LVL_DEBUG },
            { "VERBOSE", ELOG_LVL_DEBUG },
            { "ALL", ELOG_FILTER_LVL_ALL }
        };
        elog_set_filter_lvl(level_map[level]);
    }

    void setTag(const char* tag)
    {
        elog_set_filter_tag(tag);
    }

    void start()
    {

        elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_T_INFO | ELOG_FMT_DIR | ELOG_FMT_FUNC | ELOG_FMT_LINE
            //  | ELOG_FMT_ALL
            // | ELOG_FMT_TIME
        );
        elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_T_INFO | ELOG_FMT_DIR | ELOG_FMT_FUNC | ELOG_FMT_LINE
            //  | ELOG_FMT_ALL
            //  | ELOG_FMT_TIME
        );
        elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_T_INFO | ELOG_FMT_DIR | ELOG_FMT_FUNC | ELOG_FMT_LINE
            // | ELOG_FMT_ALL
            //   | ELOG_FMT_TIME
        );
        elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_LVL | ELOG_FMT_T_INFO | ELOG_FMT_DIR | ELOG_FMT_FUNC | ELOG_FMT_LINE
            // | ELOG_FMT_ALL
            //  | ELOG_FMT_TIME
        );

        elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_LVL | ELOG_FMT_T_INFO | ELOG_FMT_DIR | ELOG_FMT_FUNC | ELOG_FMT_LINE
            // | ELOG_FMT_ALL
            //  | ELOG_FMT_TIME
        );

#ifdef ELOG_COLOR_ENABLE
        elog_set_text_color_enabled(true);
#endif
        elog_start();

        // log_a("Hello EasyLogger!");
        // log_e("Hello EasyLogger!");
        // log_w("Hello EasyLogger!");
        // log_i("Hello EasyLogger!");
        // log_d("Hello EasyLogger!");
    }

private:
    MyLogger()
    {
        setbuf(stdout, NULL);
        elog_init();
    }
    ~MyLogger()
    {
        elog_deinit();
    }
};

} //end of namespace se
#endif


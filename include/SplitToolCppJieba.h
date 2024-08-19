#ifndef __SPLITOOLCPPJIEBA_H__
#define __SPLITOOLCPPJIEBA_H__

#include "SplitTool.h"
#include "cppjieba/Jieba.hpp"
#include <string>
#include <vector>
using std::string;
using std::vector;

class SplitToolCppJieba
: public SplitTool
{
public:
    SplitToolCppJieba();
    ~SplitToolCppJieba();

    vector<string> cut(const string &sentense) override;
private:
    cppjieba::Jieba _jieba;
};

#endif



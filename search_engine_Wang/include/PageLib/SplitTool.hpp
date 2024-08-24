#ifndef __SPLITTOOL_HPP__
#define __SPLITTOOL_HPP__

#include "../../lib/cppjieba-master/include/cppjieba/Jieba.hpp"
/* #include "master/include/cppjieba/Jieba.hpp" */
#include "Configuration.hpp"

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace se {
class SplitTool //用于中文分词
{
public:
    SplitTool();
    //~SplitTool();
    vector<string> cut(const string& sentence);
    //void cut(const string &sentence, vector<string> &words);
    //void cut(string &sentence, vector<string> &words);

private:
    cppjieba::Jieba _jieba;
};
}

#endif

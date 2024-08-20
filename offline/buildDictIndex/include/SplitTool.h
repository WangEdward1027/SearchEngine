#ifndef __SPLITTOOL_H__
#define __SPLITTOOL_H__

#include <string>
#include <vector>
using std::string;
using std::vector;

class SplitTool
{
public:
    SplitTool();
    virtual ~SplitTool();
    virtual vector<string> cut(const string &sentence) = 0; //分词函数,纯虚函数,提供接口
private:

};

#endif



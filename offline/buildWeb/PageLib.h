#ifndef __PAGELIB_H__
#define __PAGELIB_H__

#include "DirScanner.h"
#include "Configuration.h"
#include <string>
#include <vector>
#include <map>
#include <utility>
using std::string;
using std::vector;
using std::map;
using std::pair;

//网页库
class PageLib
{
public:
    PageLib(Configuration& conf, DirScanner& dirScanner, FileProcessor& fileProcessor);
    ~PageLib();

    void create();  //创建网页库
    void store();   //存储网页库和网页偏移库
private:
    DirScanner& _dirScanner;
    vector<string> _pages;              //网页
    map<int,pair<int,int>> _offsetLib;  //网页偏移库:每篇文档在网页库的位置信息
};

#endif



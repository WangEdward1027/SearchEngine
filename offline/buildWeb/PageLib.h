#ifndef __PAGELIB_H__
#define __PAGELIB_H__

#include "DirScanner.h"
#include "Configuration.h"
#include "tinyxml2/RssReader.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <utility>
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::pair;

//网页库
class PageLib
{
public:
    /* PageLib(Configuration & conf, DirScanner & dirScanner, RssReader & rssReader); */
    PageLib(DirScanner & dirScanner, RssReader & rssReader);
    ~PageLib();

    void buildWeb();        //创建网页库
    void buildWebOffset();  //创建网页库
    void store(const string &, const string &);           //存储网页库和网页偏移库
private:
    DirScanner& _dirScanner;  //扫描xml文件所在的目录
    RssReader & _rssReader;
    vector<string> _files;  // 存放格式化之后的xml文件
    vector<string> _pagelibs;  //网页库: 存放rss格式化之后的string
    map<int,pair<int,int>> _offsetLib; //网页偏移库:每篇文档在网页库的位置信息:<文章id, <起始偏移位置, 长度>>

    Configuration* _conf;
    RssReader& _titleFeature;

    unordered_map<string, vector<std::pair<int, double>>> _invertIndexLib;  // key:短语 value:<文章id+短语在文章中的权重>
    set<string> _doc;  // 存放单篇文章
};

#endif

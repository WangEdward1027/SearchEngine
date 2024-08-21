#ifndef __RSSREADER_H__
#define __RSSREADER_H__

#include <string>
#include <vector>
#include <utility>
#include <map>
#include "tinyxml2.h"
using std::string;
using std::vector;
using std::pair;
using std::map;
using namespace tinyxml2;

struct RssItem
{
    string title;
    string link;
    string description;
    string content;
};

class RssReader
{
public:
    void DFS(XMLElement *);
    bool parseRss(const string &filename);                                                 //解析
    void dump(const string &ripePage_dir, const string& offset_dir, vector<string> &pageLibs, map<int, pair<int,int>> &offsetLib); //输出
    void printRssItems() const;   //测试用
private:
    vector<RssItem> _rss;  //存解析出的rss
};

#endif

#ifndef __PAGELIBPREPROCESSOR_H__
#define __PAGELIBPREPROCESSOR_H__

#include "SplitTool.h"
#include "WebPage.h"
#include <unordered_map>
#include <utility>
using std::unordered_map;
using std::pair;

class PageLibPreprocessor
{
public:
    PageLibPreprocessor();
    //PageLibPreprocessor(Configuration& conf);
    ~PageLibPreprocessor();
 
    void doProcess();           //执行预处理
    void readInfoFromFile();    //根据配置信息读取网页库和网页偏移库的内容
    void cutRedundantPage();    //网页去重
    void buildInvertIndexMap(); //建立倒排索引表
    void storeOnDisk();         //将经过预处理后的网页库、网页偏移库、倒排索引表写回磁盘

private:
    SplitTool* _wordCutter;    //分词工具
    vector<WebPage> _pageList;                     //网页库的容器对象
    unordered_map<int, pair<int,int>> _offsetLib;  //网页偏移库对象
    unordered_map<string,vector<pair<int,double>>> _invertIndexLib; //倒排索引对象
};

#endif



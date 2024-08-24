#ifndef __SE_WEBPAGEQUERY_HPP__
#define __SE_WEBPAGEQUERY_HPP__

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using std::map;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;

namespace se {

class SplitTool;
class WebPage;
class WebPageQuery {

public:
    WebPageQuery()
    {
        Init();
    }

    /* string doQuery(); */

    vector<string> doQuery(const string& QueryString); //返回查询结果 相似的前10的网页

    /* private: */

    void doSplit(const string& queryString); //分割查询的string
    void Init(); //初始化 _offsetlib,_inverIndexLib;
    void initOffsetlib(const string& name);
    void initInvertIndexlib(const string& name);
    void findKeyPageWeb();
    void contAllKeyWordPageID();
    void coutQueryKeyWord();
    void coutCosWeight();
    void CosPageWebRank();
    void makeAbs();
    void clear();
    /* int lIdx(int n); */
    /* int rIdx(int n,int maxSize); */
    size_t getIdx(size_t idx);
    size_t nBytes(char ch);

    void bulitFreqMap();
    void bulitBaseVector(); //计算基准向量
    /* private: */
    /* vector<WebPage> _pages;  //存储查询相似度前10的网页 */
    unordered_map<int, pair<int, int>> _offsetlib; //存储网页偏移库的容器
    unordered_map<string, set<pair<int, double>>> _invertIndexLib; //存储倒排索引的容器
    vector<vector<int>> _pagesIdQueryed;
    vector<int> _AllKeyWordPageID;
    map<int, vector<double>> _CosWeight;
    vector<pair<int, double>> _CosPageWebRank;

    vector<string> _SplittedString; //分词后的结果
    unordered_map<string, int> _freq; //分词的词频
    set<string> _keyWord; //在倒排索引表中出现的词
    map<string, double> _BaseVector;
    /* vector<vector<double>> _AllVector; //向量  O代表基准向量 */
    vector<string> _QueryKeyWord;

    SplitTool* _wordCutTool;

    vector<string> _Abs;

    bool isInit = false;
};

} // end of namespace se
#endif

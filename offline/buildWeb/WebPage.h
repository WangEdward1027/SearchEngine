#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include "Configuration.h"
#include "../buildDictIndex/include/SplitTool.h"
#include <cwchar>
#include <string>
#include <vector>
#include <map>
#include "Simhash.h"
using std::string;
using std::vector;
using std::map;

//网页类
class WebPage
{
public:
    WebPage();
    /* WebPage(string& doc, Configuration& config, WordSegementation& jieba); */
    WebPage(string& docstr);
    ~WebPage();

    void setNewId(int id);
    void setAll(int id, string url, string title, string content);
    void buildWordsMap(Configuration* conf, SplitTool* splitTool);

    
    int getDocId();   //获取文档的docid
    string getDoc();  //获取文档
   
    string & getDocTitle();
    string & getDocUrl();
    string & getDocContent();

    map<string, int>& getWordsMap();  //获取文档的词频统计map
  
    //对格式化文档进行处理
    /* void processDoc(const string& doc, Configuration& config, SplitTool* cutter); */
    
    void calcSimhashValue(simhash::Simhaser & simhasher);

    void calcTopK(vector<string>& wordVec, int k, set<string>& stopWordList);  //求取文档的topK词集
    
    ////判断两篇文档是否相等
    friend bool operator==(const WebPage &lhs, const WebPage &rhs); 
    //对文档按DocId进行排序
    friend bool operator<(const WebPage &lhs, const WebPage &rhs);  

private:
    /* string _doc;  //整篇文档,包含xml在内 */
    int _docid;   //文档id
    string _docTitle;  //文档标题
    string _docUrl;   //文档url
    string _docContent;   //文档内容
    string _docSummary;    //文档摘要.需字典生成,不是固定的
    vector<string> _topWords;   //词频最高的前20个单词
    map<string,int> _wordsMap;   //保存每篇文档的所有词语和词频,不包括停用词
                                 //
    SplitTool* _cuttor;     //分词工具 
};

#endif



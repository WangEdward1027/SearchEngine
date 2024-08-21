#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
using std::string;
using std::vector;
using std::set;
using std::map;
using std::pair;

//将词典和索引读入
class Dictionary
{
public:
    Dictionary();
    ~Dictionary();
    
    //将词频字典文件加载到内存
    void loadDictionary();

    //将字典索引文件加载到内存
    void loadIndex();

    //获取字典库
    vector<pair<string,int>> getDict();

    //获取索引库
    map<string, set<int>> getIndexTable();

    vector<string> doQuery(const string & key);
    void queryIndex();
    int distance(string candidate);

private:
    vector<pair<string,int>> _dict_en;  //英文词典库
    vector<pair<string,int>> _dict_cn;  //中文词典库
    map<string, set<int>> _index_en;    //英文索引库
    map<string, set<int>> _index_cn;    //中文索引库
};

#endif

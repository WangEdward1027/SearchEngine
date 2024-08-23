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
  
    void loadCnIndex();      //将字典索引加载到内存
    void loadCnDictionary(); //将词频字典加载到内存
    
    /* int distance(string candidate); */
    /* vector<string> doQuery(const string & key); */
    /* void queryIndex(); */
public:
     //将索引和字典读入内存
    map<string, set<int>> _index_cn;   //中文词典索引
    vector<string> _dict_cn;           //中文字典的键,分词后的词语    

    //还没用上
    /* map<string, set<int>> _index_en;   //英文索引库 */
    /* vector<pair<string,int>> _dict_en; //英文词典库 */
};

#endif

#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include "SplitTool.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include "cppjieba/Jieba.hpp"
using std::string;
using std::vector;
using std::set;
using std::map;
using std::pair;

//词典创建类
class DictProducer
{
public:
    /* DictProducer(); */
    DictProducer(const string &dir, SplitTool* cuttor);
    ~DictProducer();
    
    void buildEnDict();  //创建英文词典文件
    void buildCnDict();  //创建中文词典文件
    void buildEnIndex(); //创建英文词典索引文件
    void buildCnIndex(); //创建中文词典索引文件
private:
    vector<string> _files;                //语料库文件的绝对路径集合
    
    SplitTool * _cuttor;                  //分词工具
    
    vector<pair<string, int>> _dict_en;   //英文词频字典。因为要用下标,所以用vector实现
    map<string,int> _dict_cn;             //中文词频字典
    
    map<char, set<string>> _index_en;     //英文词典索引
    map<string, set<string>> _index_cn;   //中文词典索引
};

#endif

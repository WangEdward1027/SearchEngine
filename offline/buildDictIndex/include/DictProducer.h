#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__

#include "SplitTool.h"
#include "DirScanner.h"
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

//词典、索引创建类
class DictProducer
{
public:
    DictProducer(SplitTool* cuttor);
    ~DictProducer();
    
    void buildEnDict();  //创建英文词典文件
    void buildCnDict();  //创建中文词典文件
    void buildEnIndex(); //创建英文词典索引文件
    void buildCnIndex(); //创建中文词典索引文件
private:
    //分词工具
    SplitTool * _cuttor;                  
    
    //目录扫描类子对象
    DirScanner _dirScanner;
    vector<string> _files;  //语料库文件的绝对路径集合,本在DirScanner类中,这里作为引用

    //英文词典和索引
    map<string,int> _dict_en_map;       //直接生成vector太慢了,所以先生成map,再用map的内容生成vector
    vector<pair<string,int>> _dict_en;  //英文词频字典。因为要用下标,所以用vector实现
    map<char,set<int>> _index_en;       //英文词典索引。值用int，为了节约存储空间
    
    //中文词典和索引
    vector<string> _words;              //存储cppjieba分词后的结果
    map<string,int> _dict_cn_map;       //中文词频字典,先生成map(速度快),再导入vector
    vector<pair<string,int>> _dict_cn;  
    map<string, set<int>> _index_cn;    //中文词典索引
};

#endif

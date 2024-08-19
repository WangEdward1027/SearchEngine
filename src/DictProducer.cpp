#include "../include/DictProducer.h"
#include "../include/SplitTool.h"
#include "../include/SplitToolCppJieba.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::istringstream;

DictProducer::DictProducer(const string &dir, SplitTool *cuttor)
: _cuttor(cuttor)
{
    _dict_en.reserve(10000);
}

DictProducer::~DictProducer()
{

}

//构建英文词典
void DictProducer::buildEnDict()
{
    //read()
    string filename = "test.txt";
    ifstream ifs(filename);
    if(!ifs.good()){
        cerr << "文件" << filename << "打开失败: ifs open Error!\n";
        return;
    }
    string line;
    while(getline(ifs, line)){
        istringstream iss(line);
        string word;
        while(iss >> word){
            //1.处理单词:只统计大小写字母，去掉数字和其他符号
            int len = word.length();
            bool alphabet = true;
            for(int i = 0; i < len; i++){
                if(!((word[i]>='A' && word[i]<='Z') || (word[i]>='a' && word[i]<='z'))){
                    alphabet = false;
                    break;
                }
            }
            if(alphabet == false) continue; //非字母.不计入词频字典

            //2.插入到vector中
            bool found = false;
            for(auto it = _dict_en.begin(); it != _dict_en.end(); ++it){
                if(it->first == word){
                    it->second++;
                    found = true;
                    break;
                }
            }
            if(found == false){
                _dict_en.push_back({word, 1});
            }
        }
    }
    /* sort(_dict.begin(), _dict.end()); */
    
    ifs.close();

    //store()
    filename = "dictionary.txt";
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "文件" << filename << "打开失败\n";
        return;
    }
    
    cout << "开始输出英文词频字典...\n";
    //下标方式遍历vector
    for(size_t i = 0; i < _dict_en.size(); ++i){
        ofs << _dict_en[i].first << " " << _dict_en[i].second << "\n";
    }
    cout << "输出英文词频字典:" << filename <<  "完毕。\n";
    ofs.close();
}

//创建英文词典索引
void DictProducer::buildEnIndex()
{
     //加入到索引map中
    for(size_t i = 0; i < _dict_en.size(); ++i){
        string word = _dict_en[i].first;
        for(int j = 0; j < word.size(); ++j){
            _index_en[word[j]].insert(word); //去重
        }
    }
    //输出英文索引
    string filename = "index_english.txt";
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "文件" << filename << "打开失败\n";
        return;
    }

    cout << "开始输出英文索引...\n";
    for(auto &elem: _index_en){
        ofs << elem.first << " " << elem.second << "\n";
    }
    cout << "输出英文索引:" << filename <<  "完毕。\n";
    ofs.close();
}

//构建中文词典
void DictProducer::buildCnDict()
{
    //read()
    string filename = "test_chinese.txt";
    ifstream ifs(filename);
    if(!ifs.good()){
        cerr << "文件" << filename << "打开失败: ifs open Error!\n";
        return;
    }

    // 读取整个文件到一个string中  
    string sentence((std::istreambuf_iterator<char>(ifs)), 
                    std::istreambuf_iterator<char>()); 
   
    vector<string> words =_cuttor->cut(sentence);

    for(auto &elem: words){
        if((elem[0] & 0x80) == 0){ //英文
            continue;
        }else{  //中文
            _dict_cn[elem]++;
        }
    }
    ifs.close();

    //store()
    filename = "dictionary_chinese.txt";
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "文件" << filename << "打开失败\n";
        return;
    }
    cout << "开始输出中文词频字典...\n";
    for(auto &elem : _dict_cn){
        ofs << elem.first << " " << elem.second << "\n";
    }
    cout << "输出词频字典文件:dictionary_chinese.txt完毕。" << "\n";
    ofs.close();     //文件输出流关闭
}

//创建中文词典索引
void DictProducer::buildCnIndex()
{
     //加入到索引map中
    for(auto &elem: _dict_cn){
        string word = elem.first;
        for(int i = 0; i < word.size(); ++i){
            //string(1,word[i])的作用是将char类型的word[i]转换为一个长度为1的string类型
            _index_cn[string(1,word[i])].insert(word);        
        }
    }
    
    //输出中文索引
    string filename = "index_chinese.txt";
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "文件" << filename << "打开失败\n";
        return;
    }
 
    cout << "开始输出中文索引...\n";
    for(auto &elem: _index_cn){
        cout << elem.first << " " << elem.second << "\n";
        ofs << elem.first << " " << elem.second << "\n";
    }
    cout << "输出中文索引:" << filename <<  "完毕。\n";
    ofs.close();
}

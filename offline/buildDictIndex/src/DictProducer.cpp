#include "../include/DictProducer.h"
#include "../include/SplitTool.h"
#include "../include/SplitToolCppJieba.h"
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::istringstream;

DictProducer::DictProducer(SplitTool *cuttor)
: _cuttor(cuttor)
, _dirScanner() //成员子对象在初始化列表中进行初始化
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
    //遍历目录下的语料，并将路径存储在_files中
    _dirScanner.traverse("../data/text_english");
    _files = _dirScanner.getFiles();
    int size = _files.size();

    //遍历语料路径 _files
    for(int i = 0; i < size; ++i){
        /* string filename = "../data/text_english/The_Holy_Bible.txt"; */
        string filename = _files[i];
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

                //2.插入到map中
                _dict_en_map[word]++;
            }
        }
        ifs.close();        
    }

    //用map构造vector
    for(auto &pair: _dict_en_map){
        _dict_en.push_back(pair);
    }

    //store()
    string filename = "../data/dictionary_english.dat";
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
            _index_en[word[j]].insert(i); 
        }
    }

    //输出英文索引
    string filename = "../data/index_english.dat";
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "文件" << filename << "打开失败\n";
        return;
    }

    cout << "开始输出英文索引...\n";
    for(auto &elem: _index_en){
        ofs << elem.first << " "; 
        for(auto &index: elem.second){
            ofs << index << " "; 
        }
        ofs << "\n";
    }
    cout << "输出英文索引:" << filename <<  "完毕。\n";
    ofs.close();
}

//构建中文词典
void DictProducer::buildCnDict()
{
    //read()
    _dirScanner.getFiles().clear(); //清空之前的英文目录

    //遍历目录下的语料，并将路径存储在_files中
    _dirScanner.traverse("../data/text_chinese");
    _files = _dirScanner.getFiles();
    int size = _files.size();

    //遍历语料路径 _files
    for(int i = 0; i < size; ++i){
        /* string filename = "../data/text_chinese/C3-Art0002.txt"; */
        string filename = _files[i];
        ifstream ifs(filename);
        if(!ifs.good()){
            cerr << "文件" << filename << "打开失败: ifs open Error!\n";
            return;
        }

        // 读取整个文件到一个string中  
        string sentence((std::istreambuf_iterator<char>(ifs)), 
                        std::istreambuf_iterator<char>()); 

        _words =_cuttor->cut(sentence);
        
        //构建map
        for(auto &elem: _words){
            if((elem[0] & 0x80) == 0){ //英文
                continue;
            }else{  //中文
                _dict_cn_map[elem]++;
            }
        }

        ifs.close();
    }

    //用map构建vector
    for(auto &pair: _dict_cn_map){
        _dict_cn.push_back(pair);
    }

    //store()
    string filename = "../data/dictionary_chinese.dat";
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
    for(int i = 0; i < _dict_cn.size(); ++i){
        string word = _dict_cn[i].first;
        for(int j = 0; j < word.size(); j+=3){
            string subword = word.substr(j,3);
            _index_cn[subword].insert(i);
        }
    }

    //输出中文索引
    string filename = "../data/index_chinese.dat";
    ofstream ofs(filename);
    if(!ofs.good()){
        cerr << "文件" << filename << "打开失败\n";
        return;
    }
 
    cout << "开始输出中文索引...\n";
    for(auto &elem: _index_cn){
        ofs << elem.first << " ";
        for(auto &index: elem.second){
            ofs << index << " ";
        }
        ofs << "\n";
    }
    cout << "输出中文索引:" << filename <<  "完毕。\n";
    ofs.close();
}

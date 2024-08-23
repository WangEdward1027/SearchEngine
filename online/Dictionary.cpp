#include "Dictionary.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cerr;
using std::ifstream;
using std::istringstream;

Dictionary::Dictionary(){}
Dictionary::~Dictionary(){}

//1.将索引读入内存
void Dictionary::loadCnIndex()
{
    string filename = "../offline/buildDictIndex/data/index_chinese.dat";       
    ifstream ifs(filename);
    if(!ifs.good()){
        cerr << "文件" << filename << "打开失败\n";
        exit(1);
    }
    string line;
    while(getline(ifs, line)){
        istringstream iss(line);
        string word;
        int index;
        iss >> word;
        while(iss >> index){
            _index_cn[word].insert(index);   
        }
    }
}

//2.将字典的key读入内存
void Dictionary::loadCnDictionary()
{
    string filename_dict = "../offline/buildDictIndex/data/dictionary_chinese.dat";
    ifstream ifs2(filename_dict);
    if(!ifs2.good()){
        cerr << "文件" << filename_dict << "打开失败\n";
        exit(1);
    }
    string line;
    while(getline(ifs2, line)){
        istringstream iss(line);
        string word;
        iss >> word;
        _dict_cn.push_back(word);
    }
}

/* int Dictionary::distance(string candidate) */
/* { */

/* } */

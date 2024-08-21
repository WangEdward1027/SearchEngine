#include "Dictionary.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;

Dictionary::Dictionary()
{

}

Dictionary::~Dictionary()
{

}

//将词频字典文件加载到内存
void Dictionary::loadDictionary()
{
    cout << "initialize dictionary" << endl;
    ifstream ifs("../data/dict.dat");
    string line;
    while(getline(ifs, line)){
        string word;
        string fre;
        bool flag = false;
        for(int i = 0; i < line.size(); ++i){
            if(line[i] == ' '){
                flag = true;
                continue;
            }
            if(!flag){
                word += line[i];
            }else{
                fre += line[i];
            }
        }
        int _fre = stoi(fre);
        _dict_en.push_back({word, _fre});
    }
    ifs.close();
}

//将字典索引文件加载到内存
void Dictionary::loadIndex()
{
    cout << "initialize index" << endl;
    ifstream ifs("../data/dictIndex.dat");
    string line;
    while(getline(ifs, line)){
        string word;
        string num;
        bool flag = false;
        for(int i = 0; i < line.size(); ++i){
            if(!flag && line[i] == ' '){
                continue;
            }
            if(flag && line[i] == ' '){
                int _num = stoi(num);
                _index_en[word].insert(_num);
                num.clear();
            }
            if(!flag && line[i] >= '0' && line[i] <= '9'){
                flag = true;
            }
            if(!flag){
                word += line[i];
            }else{
                num += line[i];
            }
        }
    }
    ifs.close();
}

//获取字典库
vector<pair<string,int>> Dictionary::getDict()
{

}

//获取索引库
map<string, set<int>> Dictionary::getIndexTable()
{

}

vector<string> Dictionary::doQuery(const string & key)
{

}

void Dictionary::queryIndex()
{

}

int Dictionary::distance(string candidate)
{

}


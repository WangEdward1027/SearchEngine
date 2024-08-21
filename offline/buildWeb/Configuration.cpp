#include "Configuration.h"
#include <fstream>
#include <iostream>
#include <sstream>
using std::ifstream;
using std::cerr;
using std::istringstream;

Configuration::Configuration(const string& filepath)
: _filepath(filepath)
{
    loadConfigFile();
    loadStopWordList();
}

Configuration* Configuration::getInstance()
{
    if(_pInstance == nullptr){
        _pInstance = new Configuration("../conf/test.conf");
    }
    return _pInstance;
}

void Configuration::loadConfigFile()
{
    ifstream ifs(_filepath);   
    if(!ifs.is_open()){
        cerr << "open configuration file failed!\n";
        exit(-1);
    }

    //逐行装入line，再逐词装入iss，最后装入_configMap中
    string line;
    while(getline(ifs, line)){
        if(line.size() == 0){
            continue;
        }

        string filename, filepath;
        istringstream iss(line);
        iss >> filename;
        iss >> filepath;
        if(filepath.size() > 0 && filename.size() > 0){
            _configMap.insert({filename, filepath});
        }else{
            break;
        }

        iss.clear();
    }
    ifs.close();
}

void Configuration::loadStopWordList()
{
    string stopWordFilePath = _configMap["STOP_WORDS_LIST_CN_PATH"];
    ifstream ifs(stopWordFilePath);
    if(!ifs.is_open()){
        cerr << "open stopword file failed!\n";
        exit(-1);
    }

    string word;
    while(ifs >> word){
        _stopWordList.insert(word);
    }

    ifs.close();
}

//获取存放配置文件的内容的map
map<string,string>& Configuration::getConfigMap()
{
    return _configMap;
}

//获取停用词词集
set<string> Configuration::getStopWordList()
{
    return _stopWordList;
}


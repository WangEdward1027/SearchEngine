#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <set>
#include <map>
using std::string;
using std::set;
using std::map;

class Configuration
{
public:
    Configuration(const string& filepath);
    ~Configuration();

    Configuration* getInstance();
    map<string,string>& getConfigMap(); //获取存放配置文件的内容的map
    set<string> getStopWordList();      //获取停用词词集
private:
    string _configFilePath;       //配置文件路径
    map<string,string> _configs;  //配置文件内容
    set<string> _stopWordList;    //停用词词集
};

#endif

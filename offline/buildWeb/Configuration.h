#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <set>
#include <map>
using std::string;
using std::set;
using std::map;

//配置文件类,单例类
class Configuration
{
public:
    class AutoRelease{  //内部类
    public:
        AutoRelease() = default;
        ~AutoRelease(){
            if(_pInstance){
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

public:

    Configuration* getInstance();
    map<string,string>& getConfigMap(); //获取存放配置文件的内容的map
    set<string> getStopWordList();      //获取停用词词集
private:
    Configuration(const string& filepath);
    void loadConfigFile();     //加载配置文件，装入_configMap中
    void loadStopWordList();   //加载停用词文件，装入_stopWordList中

private:
    string _filepath;       //配置文件路径
    map<string,string> _configMap;  //配置文件内容
    set<string> _stopWordList;    //停用词词集
                                  
    static Configuration* _pInstance;
    static AutoRelease _ar;
};

#endif

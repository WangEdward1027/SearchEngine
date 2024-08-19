#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
#include <map>
using std::string;
using std::map;

class Configuration
{
public:
    Configuration();
    ~Configuration();

    Configuration *getInstance();
    map<string, string> &getConfigMap();

private:
    string configFilePath;
    map<string, string> configs;
};

#endif

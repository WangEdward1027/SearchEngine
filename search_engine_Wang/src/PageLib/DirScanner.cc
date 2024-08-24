#include "../../include/PageLib/DirScanner.hpp"

#include <string.h>
#include <dirent.h>

#include <iostream>

using std::cout;
using std::endl;

namespace se
{

DirScanner::DirScanner(){};
DirScanner::~DirScanner(){};

void DirScanner::traverse(const string &dirname)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(dirname.c_str()))){
        cout<<"Folder doesn't Exist!"<<endl;
        return;
    }
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0){
            _files.push_back(dirname+ "/" + ptr->d_name);
        }
    }
    closedir(pDir);
}

vector<string> & DirScanner::files()
{
    return _files;
}

void DirScanner::operator()(const string &dirname)
{
    traverse(dirname);
}

}// end of namespace se

#include "../include/DirScanner.h"
#include <dirent.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
using std::cout;

DirScanner::DirScanner(){}

DirScanner:: ~DirScanner(){}

vector<string>& DirScanner::getFiles()
{
    return _files;
}

//获取语料库目录下的所有语料文件
void DirScanner::traverse(string path)
{
    //打开目录
    DIR* dir = opendir(path.c_str()); //c_str(): string转const char *
    if(dir == NULL){
        error(1, errno, "opendir %s", path.c_str());
    }

    //读取目录中的每一项
    struct dirent * entry;
    while((entry = readdir(dir)) != NULL){
        if((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)){
            continue;
        }  
        if(entry->d_type == DT_DIR){  //是目录
            path = path + "/" + entry->d_name;
            traverse(path);
        }else{  //是文件
            string filepath = path + "/" + entry->d_name;
            /* cout << filepath << "\n"; */
            _files.push_back(filepath);
        }
    }

    //关闭目录
    closedir(dir);
}

#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__

#include <string>
#include <vector>
using std::string;
using std::vector;

//目录扫描类:保存语料库的路径
class DirScanner
{
public:
    DirScanner();
    ~DirScanner();
    
    vector<string>& getFiles();  //返回_files的引用
    void traverse(string path);  //获取语料库目录下的所有语料文件
private:
    vector<string> _files;  //语料库文件的绝对路径集合
};

#endif

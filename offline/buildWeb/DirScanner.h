#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__

#include <string>
#include <vector>
using std::string;
using std::vector;

//该类的作用是遍历中文语料库所在路径，将每个中文语料文件的绝对路径存放到_file中
class DirScanner
{
public:
    DirScanner();
    ~DirScanner();

    /* void operator()(string & dirname); //重载函数调用运算符,调用traverse函数 */
    
    vector<string>& getFiles();  //返回_vecFilesfiles的引用  
    void traverse(string path);  //获取语料库目录下的所有语料文件

private:
    vector<string> _files;  //每个语料文件的绝对路径
};

#endif

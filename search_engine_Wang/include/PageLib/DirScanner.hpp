#ifndef __SE_DIRSCANNER_HPP__
#define __SE_DIRSCANNER_HPP__

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace se
{

    class DirScanner
    {
    public:
        DirScanner();
        ~DirScanner();

        //重载括号运算符,可直接通过对象遍历目录
        void operator()(const string &dirname);

        //返回遍历结果的引用
        vector<string> &files();

        //传入存放xml文件的路径
        //加遍历结果放入容器_files里面
        void traverse(const string &dirname);

    private:
        vector<string> _files;
    };

} // end of namespace se

#endif

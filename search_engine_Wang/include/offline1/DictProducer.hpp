#ifndef __DICTPRODUCER_HPP__
#define __DICTPRODUCER_HPP__

#include "SplitTool.hpp"

#include <map>
#include <set>
#include <unordered_map>
//#include <utility> //pair

using std::map;
using std::pair;
using std::set;
using std::unordered_map;

namespace se
{
        class PageLibPreProcessor;
        class DictProducer
        {
        public:
                //DictProducer(const string &dir);                  //英文用
                //DictProducer(const string &dir, SplitTool *tool); //中文用
                DictProducer(PageLibPreProcessor *pagelib);
                DictProducer(PageLibPreProcessor *pagelib, SplitTool *tool);

                //for test
                DictProducer();
                DictProducer(SplitTool *tool);
                void showDict();
                void showIndex();

                void buildEnDict();
                void buildCnDict();
                void createIndex();
                void storeDict(const char *path);
                void storeIndex(const char *path);

        private:
                //vector<string> _files;
                //从config读取语料文件夹->取得xml文件
                //->直接从PageLibPreprocessor里读取所有文章content
                PageLibPreProcessor *_pagelib;
                //vector<WebPage> _pagelist;

                vector<pair<string, int>> _dict;        //词+词频->词典
                unordered_map<string, int> _dict_index; //词+词典下标
                map<string, set<int>> _index;           //字+含有字的词在词典的下标->索引
                SplitTool *_tool;

                //for test
                string article;
        };
}

#endif
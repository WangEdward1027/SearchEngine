#ifndef __PAGELIBPREPROCESSOR_HPP__
#define __PAGELIBPREPROCESSOR_HPP__

#include "WebPage.hpp"
#include <set>
#include <vector>
#include <unordered_map>
#include <string>

using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;

namespace se
{
    class SplitTool;
    class PageLibPreProcessor
    {

    public:
        PageLibPreProcessor(SplitTool *splitTool);
        ~PageLibPreProcessor() {}

        void cutRedundantPage(const string &filepath);
        void readInfoFromFile(const string &filepath);

        void buildInvertIndexMap();
        void storeOnDisk(const string &filepath);

        vector<WebPage> getPageList();

        // void display();

    private:
        vector<WebPage> _pageList;
        unordered_map<int, pair<int, int>> _offsetLib;
        unordered_map<string, set<pair<int, double>>> _invertIndexLib;
        SplitTool *_wordCutter;
    };

}

#endif

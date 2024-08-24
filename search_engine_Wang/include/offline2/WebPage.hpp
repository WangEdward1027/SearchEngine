#ifndef __WEBPAGE_HPP__
#define __WEBPAGE_HPP__

#include "../offline1/SplitTool.hpp"
#include "../PageLib/tinyxml2.h"
#include <map>
#include <vector>
#include <string>

using std::map;
using std::string;
using std::vector;

using namespace tinyxml2;

namespace se
{
    class SplitTool;
    class WebPage
    {
        /*friend bool operator==(const WebPage &lhs, const WebPage &rhs);
        friend bool operator<(const WebPage &lhs, const WebPage &rhs); */

    public:
        WebPage();
        WebPage(const char *doc, SplitTool *splitTool);
        void RssParse();

        int getDocId();
        string getDocURL();
        string getDocTitle();
        string getDocContent();

        void modifySum(double w);
        double getSum();

        vector<string> getWordsRaw();
        map<string, int> getWordsMap();
        // void calcTopK();

    private:
        string _doc; //xml格式字符串
        SplitTool *_wordCutter;

        int _docId;
        string _docURL;
        string _docTitle;
        string _docContent;
        //string _docSummary;

        double _sum;

        vector<string> _wordsRaw;
        map<string, int> _wordsMap;
        vector<string> _topWords;
    };
}

#endif

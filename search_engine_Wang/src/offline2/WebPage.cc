#include "../../include/offline2/WebPage.hpp"
#include "tinyxml2.cpp"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using namespace tinyxml2;

namespace se
{
    WebPage::WebPage(const char *doc, SplitTool *splitTool)
        : _doc(string(doc)), _wordCutter(splitTool), _sum(0), _wordsRaw()
    {
    }

    void WebPage::RssParse()
    {
        XMLDocument xml;
        xml.Parse(_doc.c_str());

        XMLElement *root = xml.RootElement();

        _docId = atoi(root->FirstChildElement("docid")->GetText());
        _docURL = root->FirstChildElement("url")->GetText();
        _docTitle = root->FirstChildElement("title")->GetText();

        const char *temp = root->FirstChildElement("content")->GetText();
        if (0 != temp)
        {
            _docContent = temp;
        }
        else
        {
            _docContent = string(" ");
        }

        _wordsRaw = _wordCutter->cut(_docContent);

        for (auto it = _wordsRaw.begin(); it != _wordsRaw.end(); ++it)
        {
            unsigned char c = (*it)[0];
            if (c < 128)
            {
                continue;
            }
            ++_wordsMap[*it];
        }
    }

    int WebPage::getDocId()
    {
        return _docId;
    }

    string WebPage::getDocURL()
    {
        return _docURL;
    }

    string WebPage::getDocTitle()
    {
        return _docTitle;
    }

    string WebPage::getDocContent()
    {
        return _docContent;
    }

    void WebPage::modifySum(double w)
    {
        // _sum += pow(w, 2.0);
        _sum += w * w;
    }

    double WebPage::getSum()
    {
        return _sum;
    }

    vector<string> WebPage::getWordsRaw()
    {
        return _wordsRaw;
    }

    map<string, int> WebPage::getWordsMap()
    {
        return _wordsMap;
    }
}

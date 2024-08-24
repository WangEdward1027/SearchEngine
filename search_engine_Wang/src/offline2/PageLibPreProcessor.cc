#include "../../include/offline2/PageLibPreprocessor.hpp"
// #include "../../include/offline1/SplitTool.hpp"
// #include "../../include/offline2/WebPage.hpp"

#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::stoi;
using std::string;

namespace se {
PageLibPreProcessor::PageLibPreProcessor(SplitTool* splitTool)
    : _wordCutter(splitTool)
{
}

void PageLibPreProcessor::cutRedundantPage(const string& filepath)
{
    ifstream ifs(filepath, ifstream::in);
    if (!ifs) {
        cerr << "couldn't open" + string(filepath) << endl;
    }
    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string docId, pos, len;
        iss >> docId;
        iss >> pos;
        iss >> len;

        _offsetLib[stoi(docId)] = std::make_pair(stoi(pos), stoi(len));
    }
}

void PageLibPreProcessor::readInfoFromFile(const string& filepath)
{
    ifstream ifs(filepath, ifstream::in);
    if (!ifs) {
        cerr << "couldn't open " + string(filepath) << endl;
    }

    char* buf = new char[65535];
    int offset = 0;
    int num = 0;
    for (size_t idx = 0; idx < _offsetLib.size(); ++idx) {
        memset(buf, 0, 65535);
        offset = _offsetLib[idx].first;
        ifs.seekg(offset, ifs.beg);
        ifs.read(buf, _offsetLib[idx].second);
        WebPage page(buf, _wordCutter);

        page.RssParse();
        _pageList.push_back(page);
    }
    delete[] buf;
    ifs.close();
}

void PageLibPreProcessor::buildInvertIndexMap()
{
    //DF(Document Frequency)
    //calculate the number of articles including this word
    for (int idx = 0; idx < _pageList.size(); ++idx) {
        map<string, int> temp = _pageList[idx].getWordsMap();
        for (auto it = temp.begin(); it != temp.end(); ++it) {
            _invertIndexLib[it->first].insert(pair<int, double>(idx, 0));
        }
    }

    //calculate w(Weight)
    int N = _pageList.size();
    for (int idx = 0; idx < _pageList.size(); ++idx) {
        //TF(Term Frequency) = _pageList[idx]._wordsMap[word] = it->second
        //DF = _invertIndexLib[word].size() = _invertIndexLib[it->first].size()
        // N = _pageList.size()
        // w = TF * log2(N/(DF+1))
        map<string, int> temp = _pageList[idx].getWordsMap();
        for (auto it = temp.begin(); it != temp.end(); ++it) {
            double w = (it->second) * ((double)(log(N / (_invertIndexLib[it->first].size() + 1))) / log(2));

            _invertIndexLib[it->first].erase(pair<int, double>(idx, 0));
            _invertIndexLib[it->first].insert(pair<int, double>(idx, w));

            _pageList[idx].modifySum(w);
        }
    }

    //normalization
    for (auto it1 = _invertIndexLib.begin(); it1 != _invertIndexLib.end(); ++it1) {
        for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
            int pageNum = it2->first;
            double w = (it2->second) / sqrt(_pageList[pageNum].getSum());
            it1->second.erase(it2);
            it1->second.insert(pair<int, double>(pageNum, w));
        }
    }
}

void PageLibPreProcessor::storeOnDisk(const string& filepath)
{
    ofstream ofs(filepath, ofstream::out);
    if (!ofs) {
        cerr << "couldn't open " + filepath << endl;
    }

    for (auto it = _invertIndexLib.begin(); it != _invertIndexLib.end(); ++it) {
        ofs << it->first << " ";

        for (auto it1 = it->second.begin(); it1 != it->second.end(); ++it1) {
            ofs << it1->first << " " << it1->second << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

vector<WebPage> PageLibPreProcessor::getPageList()
{
    return _pageList;
}

}

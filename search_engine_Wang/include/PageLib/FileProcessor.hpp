#ifndef __SE_FILEPROCESSOR_HPP__
#define __SE_FILEPROCESSOR_HPP__

#include "tinyxml2.h"
#include <vector>
#include <string>
#include <map>

using std::map;
using std::pair;
using std::string;
using std::vector;

namespace se
{

    using namespace tinyxml2;
    class FileProcessor
    {
    public:
        struct NetXML
        {
            vector<string> _page;
            map<int, pair<int, int>> _offset;
            vector<string> _offsetString;
        };

        NetXML process(const string &FilePath, int &docidN, int &offsetN);
    };

} // end of namespace se

#endif

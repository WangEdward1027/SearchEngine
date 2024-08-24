#include "../../include/PageLib/PageLib.hpp"
#include "../../include/Configuration.hpp"
#include "../../include/PageLib/DirScanner.hpp"
#include "../../include/PageLib/FileProcessor.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

using std::ofstream;

namespace se
{

    void PageLib::create()
    {
        Configuration *ps1 = Configuration::getInstance();
        _dirScanner(ps1->getConfigMap()["xml"]);
        auto xmlFileVector = _dirScanner.files();
        ofstream ofsNet(ps1->getConfigMap()["page"]);
        ofstream ofsOffset(ps1->getConfigMap()["offset"]);
        ofstream ofsOffset(ps1->getConfigMap()["offset"]);

        int docidN = 0;
        int offsetN = 0;
        int XMLN = 0;
        auto it = xmlFileVector.begin();
        while (it != xmlFileVector.end())
        {
            auto PageNetLib = _fileProcessor.process(*it, docidN, offsetN);
            _pages.insert(_pages.end(), PageNetLib._page.begin(), PageNetLib._page.end());
            _offsetLib.insert(PageNetLib._offset.begin(), PageNetLib._offset.end());
            cout << "XMLN---->" << XMLN << "<-----" << *it << endl;
            ++XMLN;
            ++it;
        }
    }

    void PageLib::store()
    {
        Configuration *ps1 = Configuration::getInstance();
        ofstream ofsNet(ps1->getConfigMap()["page"]);
        ofstream ofsOffset(ps1->getConfigMap()["offset"]);
        auto it = _pages.begin();
        while (it != _pages.end())
        {
            ofsNet << *it << endl;
            ++it;
        }
        ofsNet.close();

        auto it2 = _offsetLib.begin();
        while (it2 != _offsetLib.end())
        {
            string offset(to_string(it2->first) + " " + to_string(it2->second.first) + " " + to_string(it2->second.second));
            ofsOffset << offset << endl;
            ++it2;
        }
    }

} // end of namespace se

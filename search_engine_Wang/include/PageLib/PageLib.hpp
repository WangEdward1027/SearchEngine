#ifndef __SE_PAGELIB_HPP__
#define __SE_PAGELIB_HPP__

#include "DirScanner.hpp"
#include "FileProcessor.hpp"
#include "Configuration.hpp"

namespace se
{

    class PageLib
    {
    public:
        /* PageLib(); */
        void create();
        void store();

    private:
        DirScanner _dirScanner;
        vector<string> _pages;
        map<int, pair<int, int>> _offsetLib;
        FileProcessor _fileProcessor;
    };

} // end of namespace se

#endif

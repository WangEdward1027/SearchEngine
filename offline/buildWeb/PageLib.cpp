#include "PageLib.h"

PageLib::PageLib(DirScanner & dirScanner, RssReader & rssReader)
: _dirScanner(dirScanner)
, _rssReader(rssReader)
{

}

PageLib::~PageLib()
{

}

//创建网页库
void PageLib::buildWeb()
{

}

//创建网页库
void PageLib::buildWebOffset()
{
    
}

//存储网页库和网页偏移库
void PageLib::store(const string & pagelibs_dir, const string & offsetLib_dir)
{
    _rssReader.dump(pagelibs_dir, offsetLib_dir, _pagelibs, _offsetLib);
} 

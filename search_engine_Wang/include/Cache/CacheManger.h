#ifndef __CACHEMANGER_H__
#define __CACHEMANGER_H__

#include "../../src/Reactor/MyLogger.hpp"
#include "../PageLib/WebPageQuery.hpp"
#include "./LRUCache.h"

#include <atomic>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

using Node = se::LRUCache::Node;

namespace se {

class CacheManger {

public:
    void updateCache();

    vector<LRUCache> main_caches;
    vector<WebPageQuery> web_querys;

    static CacheManger* _instance;

public:
    static CacheManger* getInstance()
    {
        pthread_once(&once, init);
        return _instance;
    }

    static void init()
    {
        if (_instance == nullptr) {
            log_i("CacheManger Init Success");
            _instance = new CacheManger;
        }
    }

    LRUCache& getMainCache(int id)
    {
        return main_caches.at(id);
    }

    WebPageQuery& getWebPageQuery(int id)
    {
        return web_querys.at(id);
    }

private:
    CacheManger();
    ~CacheManger() { }

    static pthread_once_t once;
};

}
#endif

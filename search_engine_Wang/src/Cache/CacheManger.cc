
#include "../../include/Cache/CacheManger.h"
#include "../../include/Cache/LRUCache.h"
#include "../../include/Configuration.hpp"
#include "../../include/PageLib/WebPageQuery.hpp"
#include "../Reactor/MyLogger.hpp"

#include <atomic>
#include <memory>
#include <unordered_map>
#include <vector>

using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::vector;

using Node = se::LRUCache::Node;

namespace se {

CacheManger::CacheManger()
{
    // 初始化每个线程的数据
    auto configuration = Configuration::getInstance();
    int num_of_thread = std::stoi(configuration->getConfigValue("num_of_thread"));
    main_caches.reserve(num_of_thread);
    web_querys.reserve(num_of_thread);
    for (int i = 0; i < num_of_thread; ++i) {
        main_caches.emplace_back();
        web_querys.emplace_back();
        web_querys.back().Init();
    }
}

void CacheManger::updateCache()
{
    // 新增数据大于三条才会进行缓存同步与备份
    size_t pending_cnt = 0;
    for (auto& cache : main_caches) {
        pending_cnt += cache._pending_update_list.size();
    }
    if (pending_cnt < 3) {
        return;
    }

    // 复制0号线程的缓存作为主备份缓存
    LRUCache backup_cache;
    while (!main_caches[0].update_flg.test_and_set()) {
        backup_cache = main_caches[0];
        main_caches[0].update_flg.clear();
        break;
    }

    // 将其他线程中更新列表中的数据插入主备份，并清空其更新列表
    for (auto it = ++main_caches.begin(); it != main_caches.end(); ++it) {
        while (!it->update_flg.test_and_set()) {
            for (auto& node : it->_pending_update_list) {
                if (!it->get(node.key, false).empty())
                    backup_cache.addRecord(node.key, node.value);
            }
            it->update_flg.clear();
            break;
        }
    }
    backup_cache._pending_update_list.clear();

    // 将主备份会写到各个缓存中
    for (auto& cache : main_caches) {
        while (!cache.update_flg.test_and_set()) {
            cache = backup_cache;
            cache.update_flg.clear();
            break;
        }
    }

    log_d("update success");

    // 备份缓存
    backup_cache.writeToFile(se::Configuration::getInstance()->getConfigValue("cachelib"));
}
}
// #include "../Reactor/MyLogger.hpp"

#include "../../include/Cache/LRUCache.h"
#include "../../include/Configuration.hpp"
#include "../Reactor/MyLogger.hpp"

// #include "json.hpp"

#include "unistd.h"

#include <algorithm>
#include <atomic>
#include <fstream>
#include <functional>
#include <sstream>

using std::cout;
using std::endl;

namespace se {

using se::Configuration;

string LRUCache::empty_js {};

using hash_pair = se::hash_pair;

LRUCache::LRUCache(int capacity)
    : update_flg(ATOMIC_FLAG_INIT)
    , _capacity(capacity)
    , _result_list(list<Node>())
    , _hashmap(unordered_map<pair<int, string>, list<Node>::iterator, hash_pair>())
    , _pending_update_list(list<Node>())
{
    _capacity = std::stoi(se::Configuration::getInstance()->getConfigValue("size_of_cache"));
    readFromFile(se::Configuration::getInstance()->getConfigValue("cachelib"));
}

LRUCache::LRUCache(const LRUCache& rhs)
{
    _capacity = rhs._capacity;
    _result_list = rhs._result_list;
    _hashmap = rhs._hashmap;
    _pending_update_list = rhs._pending_update_list;
}

string LRUCache::get(const pair<int, string>& key, bool log)
{
    if (_hashmap.count(key) == 0) {
        if (log)
            log_v("miss!");
        return LRUCache::empty_js;
    }
    if (!update_flg.test_and_set()) {
        if (log)
            log_v("found!");
        // 取得value后要将对应的pair<string, value>从队列中移动到队尾，并更新map中
        _result_list.splice(_result_list.end(), _result_list, _hashmap[key]);
        _hashmap[key] = --_result_list.end();
        auto ret = _hashmap[key]->value;
        update_flg.clear();
        return ret;
    }
    return LRUCache::empty_js;
}

void LRUCache::addRecord(pair<int, string> key, string value, bool log)
{
    if (!update_flg.test_and_set()) {
        if (_result_list.size() < _capacity) {
            // 未达到容量上限，直接插入
            _result_list.emplace_back(key, value);
            _pending_update_list.emplace_back(key, value);
            _hashmap[key] = --_result_list.end();
            if (log)
                log_i("update new key %d %s", _hashmap[key]->key.first, _hashmap[key]->key.second.c_str());
        } else {
            // 达到容量上限，需要删除队头元素
            if (log)
                log_i("Cache Miss : %s out", _result_list.front().key.second.c_str());
            _hashmap.erase(_result_list.front().key);
            _result_list.pop_front();
            // 插入新元素
            _result_list.emplace_back(key, value);
            _pending_update_list.emplace_back(key, value);
            _hashmap[key] = --_result_list.end();
            if (log)
                log_i("update new key %d %s", _hashmap[key]->key.first, _hashmap[key]->key.second.c_str());
        }
        update_flg.clear();
    }
}

void LRUCache::readFromFile(const string& file_name)
{
    std::ifstream in(file_name);
    if (!in.is_open()) {
        log_e("open input cache file error");
        return;
    }

    /* std::stringstream line; */
    /* line << in.rdbuf(); */
    /* int op; */
    /* while (line >> op) { */
    /*     string keyword, value; */
    /*     line >> keyword >> value; */
    /*     /1* cout << keyword << "  " << value; *1/ */
    /*     addRecord({ op, keyword }, value, false); */
    /* } */

    string line;
    string keyword, value;
    int op;

    while (getline(in, line)) {
        size_t sz1 = line.find(" ");
        if (sz1 == line.npos)
            continue;

        op = std::stoi(line.substr(0, sz1));

        size_t sz2 = line.substr(sz1 + 1).find(" ");
        if (sz2 == line.npos)
            continue;

        keyword = line.substr(sz1 + 1, sz2 - sz1 + 1);
        value = line.substr(sz2 + 2);

        addRecord({ op, keyword  }, value, false);
    }
    in.close();
}

void LRUCache::writeToFile(const string& file_name)
{
    std::ofstream out;
    out.open(file_name, std::ios::out);
    if (!out.is_open()) {
        log_e("open output cache file error");
        return;
    }

    while (!update_flg.test_and_set()) {
        for (auto& node : _result_list) {
            out << node.key.first << " "
                << node.key.second << " "
                << node.value << endl;
        }
        log_d("backup success");
        update_flg.clear();
        break;
    }

    out.close();
}

LRUCache& LRUCache::operator=(const LRUCache& rhs)
{
    _capacity = rhs._capacity;
    _result_list = rhs._result_list;
    _hashmap = rhs._hashmap;
    _pending_update_list = rhs._pending_update_list;

    return *this;
}
}

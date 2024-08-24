#ifndef __LRUCACHE_H__
#define __LRUCACHE_H__

#include <atomic>
#include <iostream>
#include <list>
#include <unordered_map>

using std::atomic_flag;
using std::list;
using std::pair;
using std::string;
using std::unordered_map;

namespace se {

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1> {}(p.first);
        auto hash2 = std::hash<T2> {}(p.second);
        return hash1 ^ hash2;
    }
};

class LRUCache {
public:
    LRUCache(int capacity = 5);
    LRUCache(const LRUCache& rhs);
    // ~LRUCache() { cout << "~LRUCache()" << endl; }

    struct Node {
        pair<int, string> key;
        string value;
        Node() = default;
        Node(pair<int, string> new_key, string new_value)
            : key(new_key)
            , value(new_value)
        {
        }
    };

    atomic_flag update_flg;

    size_t _capacity;

    list<Node> _result_list;
    unordered_map<pair<int, string>, list<Node>::iterator, hash_pair> _hashmap;
    list<Node> _pending_update_list;

    string get(const pair<int, string>& key, bool log = true);

    void addRecord(pair<int, string> key, string value, bool log = true);

    void readFromFile(const string& file_name);
    void writeToFile(const string& file_name);

    LRUCache& operator=(const LRUCache& rhs);

    // void update(const LRUCache& new_cache); // 更新全部缓存

    static string empty_js;

private:
};

}

#endif

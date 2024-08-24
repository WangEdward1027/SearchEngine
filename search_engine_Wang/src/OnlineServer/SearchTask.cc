
#include "../../include/OnlineServer/SearchTask.hpp"
#include "../../include/Cache/CacheManger.h"
#include "../../include/PageLib/WebPageQuery.hpp"
#include "../../include/proparse/protocol.hpp"
#include "../Reactor/MyLogger.hpp"

#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::placeholders::_1;

static __thread int thread_id;

void SearchTask::process()
{
    if (_request.size() <= 1) {
        return;
    }

    if (_request.back() == '\n') {
        _request.pop_back();
    }

    auto& cache = se::CacheManger::getInstance()->getMainCache(thread_id);

    log_v("receive %s", _request.c_str());

    printf("-------------------------------\n");
    ProtocolParser tran;
    auto res = tran.doParse(_request);
    for (auto i : res._content) {
        cout << i << endl;
    }

    auto content = res._content.front();

    if (res._id == 1) // c->s id=1 为关键词查询
    {

        string query_ret = cache.get(make_pair(1, content));

        if (query_ret.empty()) {
            // 查库
            vector<string> result = _key.doQuery(content);
            for (auto& word : result) {
                cout << word << endl;
            }

            query_ret = tran.doPack(100, result);

            cache.addRecord(make_pair(1, content), query_ret);
        }
        _conn->sendInLoop(query_ret);
    } else if (res._id == 2) // c->s id=2 为网页查询
    {

        string query_ret = cache.get(make_pair(2, content));

        if (query_ret.empty()) {
            // 查库
            se::WebPageQuery& _web = se::CacheManger::getInstance()->getWebPageQuery(thread_id);

            vector<string> result = _web.doQuery(content);
            cout << "Key Words : ";
            for (auto& w : _web._keyWord) {
                cout << w << " ";
            }
            cout << endl;
            _web.clear();
            for (auto abs : result) {
                cout << abs << endl;
            }
            query_ret = tran.doPack(200, result);
            
            cache.addRecord(make_pair(2, content), query_ret);
        }
        
        cout << query_ret << endl;
        
        _conn->sendInLoop(query_ret);
    } else {
        nlohmann::json _j;
        _j["id"] = -1;
        _j["content"] = vector<string>();
        _conn->sendInLoop(_j.dump());
    }

    printf("-------------------------------\n");
}

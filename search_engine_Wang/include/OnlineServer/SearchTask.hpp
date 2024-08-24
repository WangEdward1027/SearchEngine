#ifndef __SEARCHTASK_H__
#define __SEARCHTASK_H__

#include "../Reactor/TcpServer.hpp"
#include "../Reactor/Threadpool.hpp"
#include "../keyRecommand/keyRecommender.hpp"

class SearchTask {
public:
    SearchTask(const string& request, const se::TcpConnectionPtr& conn)
        : _request(request)
        , _conn(conn)
    {
    }

    //process方法运行在线程池中一个子线程
    void process();

private:
    string _request;
    se::TcpConnectionPtr _conn;
    se::KeyRecommender _key;
};

#endif

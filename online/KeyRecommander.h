#ifndef __KEYRECOMMANDER_H__
#define __KEYRECOMMANDER_H__

#include "CandidateResult.h"
#include "./ReactorV5/TcpConnection.h"
#include <string>
#include <queue>
using std::string;
using std::priority_queue;

using TcpConnectionPtr = shared_ptr<TcpConnection>;

class KeyRecommander
{
public:
    KeyRecommander(string & queryword, const TcpConnectionPtr & ptr);
    ~KeyRecommander();

    string doQuery();
private:
    string _sought;
    priority_queue<CandidateResult>;   
};

#endif



#ifndef __KEYRECOMMANDER_H__
#define __KEYRECOMMANDER_H__

#include "CandidateResult.h"
#include <string>
#include <queue>
using std::string;
using std::priority_queue;

class KeyRecommander
{
public:
    KeyRecommander(string & queryword, const TcpConnectionPrt & ptr);
    ~KeyRecommander();

    string doQuery();
private:
    string _sought;
    priority_queue<CandidateResult>;   
};

#endif



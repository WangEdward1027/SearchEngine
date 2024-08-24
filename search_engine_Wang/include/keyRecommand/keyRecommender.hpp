#ifndef __KEYRECOMMENDER_HPP__
#define __KEYRECOMMENDER_HPP__

#include "dictionary.hpp"

#include <string>
#include <queue>
#include <vector>

using std::priority_queue;
using std::string;
using std::vector;

namespace se
{
    class KeyRecommender
    {
    public:
        KeyRecommender()
            : _dict(Dictionary::getInstance()) {}
        vector<string> doQuery(const string &str);

    private:
        struct myCmp
        {
            bool operator()(CandidateResult &lhs, CandidateResult &rhs)
            {
                return lhs._word < rhs._word;
            }
        };

    private:
        int _capacity = 5;
        // string _sought;
        priority_queue<CandidateResult, vector<CandidateResult>, myCmp> _que;
        vector<string> _resWords;
        // TcpConnectionPtr _conn;
        Dictionary *_dict;
    };
}

#endif

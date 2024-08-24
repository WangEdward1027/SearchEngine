#include "../../include/keyRecommand/keyRecommender.hpp"

#include <iostream>

namespace se
{
    vector<string> KeyRecommender::doQuery(const string &str)
    {
        _resWords.clear();
        int cnt = 0;
        while (cnt < _capacity)
        {
            vector<CandidateResult> temp = _dict->doQuery(str);

            if (temp.empty())
            {
                break;
            }
            for (auto &it : temp)
            {
                if (cnt == _capacity)
                {
                    break;
                }
                _que.push(it);
                ++cnt;
            }
        }

        while (!_que.empty())
        {
            _resWords.push_back(_que.top()._word);
            _que.pop();
        }

        return _resWords;
    }

}

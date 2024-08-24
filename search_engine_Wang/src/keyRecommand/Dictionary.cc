#include "../../include/keyRecommand/dictionary.hpp"
#include "../../include/Configuration.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using std::cerr;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;

namespace se
{
    Dictionary *Dictionary::_sigDict = nullptr;

    Dictionary *Dictionary::getInstance()
    {
        if (_sigDict == nullptr)
        {
            _sigDict = new Dictionary;
            _sigDict->get_dict();
            _sigDict->get_index();
        }
        return _sigDict;
    }

    size_t Dictionary::nBytesCode(char ch)
    {
        size_t res = 1;
        int N = 6;
        if (ch & (1 << 7))
        {
            while ((ch & (1 << N)) != 0)
            {
                ++res;
                --N;
            }
        }
        return res;
    }

    size_t Dictionary::length(const string &word)
    {
        size_t len = 0;
        for (size_t idx = 0; idx < word.size();)
        {
            size_t bytes = nBytesCode(word[idx]);
            ++len;
            idx += bytes;
        }
        return len;
    }

    int Dictionary::triple_min(const int &a, const int &b, const int &c)
    {
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }

    int Dictionary::editDistance(const string &lhs, const string &rhs)
    {
        size_t lhs_len = length(lhs);
        size_t rhs_len = length(rhs);
        size_t blhs_len = lhs.size();
        size_t brhs_len = rhs.size();

        int editDist[lhs_len + 1][rhs_len + 1];

        for (size_t idx = 0; idx <= lhs_len; ++idx)
        {
            editDist[idx][0] = idx;
        }

        for (size_t idx = 0; idx <= rhs_len; ++idx)
        {
            editDist[0][idx] = idx;
        }

        string sublhs, subrhs;
        for (size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len && lhs_idx <= blhs_len; ++dist_i)
        {
            size_t nBytes = nBytesCode(lhs[lhs_idx]);
            sublhs = lhs.substr(lhs_idx, nBytes);
            lhs_idx += nBytes;

            for (std::size_t dist_j = 1, rhs_idx = 0; dist_j <= rhs_len && rhs_idx <= brhs_len; ++dist_j)
            {
                nBytes = nBytesCode(rhs[rhs_idx]);
                subrhs = rhs.substr(rhs_idx, nBytes);
                rhs_idx += nBytes;
                if (sublhs == subrhs)
                {
                    editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
                }
                else
                {
                    editDist[dist_i][dist_j] = 1 + triple_min(
                                                       editDist[dist_i][dist_j - 1],
                                                       editDist[dist_i - 1][dist_j],
                                                       editDist[dist_i - 1][dist_j - 1]);
                }
            }
        }
        return editDist[lhs_len][rhs_len];
    }

    void Dictionary::destory()
    {
        if (_sigDict)
        {
            delete _sigDict;
            _sigDict = nullptr;
        }
    }

    bool Dictionary::dis_compare(CandidateResult &lhs, CandidateResult &rhs)
    {
        return lhs._freq > rhs._freq;
    }

    vector<CandidateResult> Dictionary::doQuery(const string &str)
    {
        string word = str;
        string letter;
        map<string, int> find_word; //从_dict得到的词+词频

        //每个字
        size_t i = 0;
        while (i < word.size())
        {
            //编码中开头只有一个1，是英文，英文符号，数字
            unsigned char c = word[i];
            if (c < 128)
            {
                ++i;
                continue;
            }
            //取得单个汉字共多少字节
            size_t cnt = 1;
            for (; cnt < 6; ++cnt)
            {
                unsigned char b = c << cnt;
                if (b < 128)
                {
                    break;
                }
            }

            letter = word.substr(i, cnt);
            i += cnt;

            auto _index_it = _index.find(letter);
            if (_index_it != _index.end())
            {
                for (auto set_it : _index_it->second)
                {
                    find_word.insert(pair<string, int>(_dict[set_it].first, _dict[set_it].second));
                }
            }
        }

        vector<CandidateResult> res;
        int min_dis = 5; //初始设置一个编辑距离
        for (auto &find_it : find_word)
        {
            auto isVisited_it = find(_isVisited.begin(), _isVisited.end(), find_it.first);
            if (isVisited_it != _isVisited.end())
            {
                continue;
            }

            int dis = editDistance(word, find_it.first);
            CandidateResult elem;

            if (dis < min_dis)
            {
                res.clear();
                min_dis = dis;

                elem._dist = dis;
                elem._word = find_it.first;
                elem._freq = find_it.second;

                res.push_back(elem);
            }
            else if (dis == min_dis)
            {
                elem._dist = dis;
                elem._word = find_it.first;
                elem._freq = find_it.second;

                res.push_back(elem);
            }
            else
            {
                continue;
            }
        }
        for (auto &find_it : res)
        {
            _isVisited.push_back(find_it._word);
        }
        std::sort(res.begin(), res.end(), dis_compare);
        return res;
    }

    void Dictionary::get_dict()
    {
        string filepath = se::Configuration::getInstance()->getConfigValue("dict");
        // string filepath = "./data/offlinedict/dict.txt";
        ifstream ifs(filepath, ifstream::in);
        if (!ifs)
        {
            cerr << "couldn't open " + string(filepath) << endl;
        }
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            string word, freq;
            iss >> word >> freq;
            _dict.push_back(pair<string, int>(word, stoi(freq)));
        }
    }

    void Dictionary::get_index()
    {
        string filepath = se::Configuration::getInstance()->getConfigValue("index");
        // string filepath = "./data/offlinedict/dictindex.txt";
        ifstream ifs(filepath, ifstream::in);
        if (!ifs)
        {
            cerr << "couldn't open " + string(filepath) << endl;
        }
        string line;
        while (getline(ifs, line))
        {
            istringstream iss(line);
            string word, freq;
            iss >> word;
            while (iss >> freq)
            {
                _index[word].insert(stoi(freq));
            }
        }
    }
}

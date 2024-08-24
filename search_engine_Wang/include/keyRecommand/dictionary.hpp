#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__

#include <vector>
#include <map>
#include <string>
#include <set>

using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

namespace se
{
    typedef struct res
    {
        string _word;
        int _freq;
        int _dist;
    } CandidateResult;

    class Dictionary
    {

    public:
        static Dictionary *getInstance();
        void destory();

        vector<CandidateResult> doQuery(const string &str);
        static bool dis_compare(CandidateResult &lhs, CandidateResult &rhs);

        size_t nBytesCode(char ch);
        size_t length(const string &word);
        int triple_min(const int &a, const int &b, const int &c);
        int editDistance(const string &lhs, const string &rhs);
        //int getDistance(const string &lhs, const string &rhs);

        void get_dict();
        void get_index();

    private:
        Dictionary(){};
        static Dictionary *_sigDict;
        vector<pair<string, int>> _dict;
        vector<string> _isVisited;
        map<string, set<int>> _index;
    };
}

#endif

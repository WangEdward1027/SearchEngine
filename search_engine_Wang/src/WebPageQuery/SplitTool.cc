#include "../../include/PageLib/SplitTool.hpp"

using std::cout;
using std::endl;
using std::unordered_set;

namespace se {
const char* const DICT_PATH = "./lib/cppjieba-master/dict/jieba.dict.utf8";
const char* const HMM_PATH = "./lib/cppjieba-master/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./lib/cppjieba-master/dict/user.dict.utf8";
const char* const IDF_PATH = "./lib/cppjieba-master/dict/idf.utf8";
const char* const STOP_WORD_PATH = "./lib/cppjieba-master/dict/stop_words.utf8";
SplitTool::SplitTool()
    : _jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH)
//,_config(config)
{
}

vector<string> SplitTool::cut(const string& sentence)
{
    vector<string> all_words;
    _jieba.Cut(sentence, all_words, true); //cut with HMM

    //去除停用词
    vector<string> words;
    // Configuration *config1 = Configuration::getInstance();
    // unordered_set<string> stop_words = config1->getStopWordList();

    unordered_set<string> stop_words = se::Configuration::getInstance()->getStopWordList();
    // set<string> stop_words = se::Configuration::getInstance()->getStopWordList();

    // cout << "size = " << stop_words.size() << endl;

    for (auto& it : all_words) {
        if (stop_words.find(it) != stop_words.end()) {
            continue;
        } else {
            words.push_back(it);
        }
    }
    //_jieba.Cut(sentence, words);

    return words;
}

/*  void SplitTool::cut(const string &sentence, vector<string> &words)
    {
        _jieba.Cut(sentence, words, true); //cut with HMM
    } */
/* void SplitTool::cut(string &sentence, vector<string> &words)
    {
        _jieba.Cut(sentence, words, true); //cut with HMM
    } */

}

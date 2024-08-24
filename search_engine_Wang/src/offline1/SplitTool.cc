#include "../../include/offline1/SplitTool.hpp"

using std::cout;
using std::endl;

namespace se
{
    const char *const DICT_PATH = "../../lib/cppjieba-master/dict/jieba.dict.utf8";
    const char *const HMM_PATH = "../../lib/cppjieba-master/dict/hmm_model.utf8";
    const char *const USER_DICT_PATH = "../../lib/cppjieba-master/dict/user.dict.utf8";
    const char *const IDF_PATH = "../../lib/cppjieba-master/dict/idf.utf8";
    const char *const STOP_WORD_PATH = "../../lib/cppjieba-master/dict/stop_words.utf8";
    /* SplitTool::SplitTool()
        : _jieba(DICT_PATH,
                 HMM_PATH,
                 USER_DICT_PATH,
                 IDF_PATH,
                 STOP_WORD_PATH)
    //,_config(config)
    {
    } */

    //SplitTool *SplitTool::_sptool = nullptr;
    //cppjieba::Jieba *SplitTool::_jieba = nullptr;
    SplitTool *SplitTool::_sptool = nullptr;
    CppJieba *SplitTool::_jieba = nullptr;

    CppJieba::CppJieba()
        : _jieba_(DICT_PATH,
                  HMM_PATH,
                  USER_DICT_PATH,
                  IDF_PATH,
                  STOP_WORD_PATH)
    {
    }

    SplitTool *SplitTool::getInstance()
    {
        if (_sptool == nullptr)
        {
            _jieba = new CppJieba;
            _sptool = new SplitTool;
        }
        return _sptool;
    }
    /* SplitTool *SplitTool::getInstance()
    {
        if (_sptool == nullptr)
        {
            cout << "before" << endl;
            *_jieba = cppjieba::Jieba(DICT_PATH,
                                      HMM_PATH,
                                      USER_DICT_PATH,
                                      IDF_PATH,
                                      STOP_WORD_PATH);
            cout << "after" << endl;
            _sptool = new SplitTool();
        }
        return _sptool;
    } */

    void SplitTool::destory()
    {
        if (_sptool)
        {
            delete _sptool;
            _sptool = nullptr;
            delete _jieba;
            _jieba = nullptr;
        }
    }

    vector<string> SplitTool::cut(const string &sentence)
    {
        vector<string> all_words;
        _jieba->_jieba_.Cut(sentence, all_words, true); //cut with HMM

        //去除停用词
        vector<string> words;
        Configuration *config1 = Configuration::getInstance();
        unordered_set<string> stop_words = config1->getStopWordList();

        for (auto &it : all_words)
        {
            if (stop_words.find(it) != stop_words.end())
            {
                continue;
            }
            else
            {
                words.push_back(it);
            }
        }
        //_jieba.Cut(sentence, words);

        //去除英文乱码或数字
        all_words.clear();

        for (auto &it : words)
        {
            unsigned char c = it[0];
            if (c < 128)
            {
                continue;
            }
            else
            {
                all_words.push_back(it);
            }
        }

        return all_words;
    }

    //SplitTool *SplitTool::_sptool = nullptr;
    //cppjieba::Jieba *SplitTool::_jieba = nullptr;

    /*  void SplitTool::cut(const string &sentence, vector<string> &words)
    {
        _jieba.Cut(sentence, words, true); //cut with HMM
    } */
    /* void SplitTool::cut(string &sentence, vector<string> &words)
    {
        _jieba.Cut(sentence, words, true); //cut with HMM
    } */

}
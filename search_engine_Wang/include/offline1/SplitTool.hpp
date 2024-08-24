#ifndef __SPLITTOOL_HPP__
#define __SPLITTOOL_HPP__

#include "../../lib/cppjieba-master/include/cppjieba/Jieba.hpp"
#include "../PageLib/Configuration.hpp"

#include <vector>
#include <string>

using std::string;
using std::vector;

namespace se
{
    class CppJieba
    {
        friend class SplitTool;

    public:
        CppJieba();

    private:
        cppjieba::Jieba _jieba_;
    };

    class SplitTool //用于中文分词,单例模式,无自动释放
    {
    public:
        static SplitTool *getInstance();
        void destory();
        //~SplitTool();
        vector<string> cut(const string &sentence);
        //void cut(const string &sentence, vector<string> &words);
        //void cut(string &sentence, vector<string> &words);

    private:
        SplitTool(){};
        ~SplitTool(){};
        static SplitTool *_sptool;
        static CppJieba *_jieba;
        /* const char *const DICT_PATH = "../../lib/cppjieba-master/dict/jieba.dict.utf8";
        const char *const HMM_PATH = "../../lib/cppjieba-master/dict/hmm_model.utf8";
        const char *const USER_DICT_PATH = "../../lib/cppjieba-master/dict/user.dict.utf8";
        const char *const IDF_PATH = "../../lib/cppjieba-master/dict/idf.utf8";
        const char *const STOP_WORD_PATH = "../../lib/cppjieba-master/dict/stop_words.utf8"; */

        //Configuration _config;
    };
    //SplitTool *SplitTool::_sptool = nullptr;
}

#endif

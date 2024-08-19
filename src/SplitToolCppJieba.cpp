#include "../include/SplitToolCppJieba.h"
#include "../include/cppjieba/Jieba.hpp" 

const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const HMM_PATH = "./dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";


SplitToolCppJieba::SplitToolCppJieba() // 构建结巴对象 （操作非常耗时）
: _jieba(DICT_PATH, 
         HMM_PATH, 
         USER_DICT_PATH,
         IDF_PATH,
         STOP_WORD_PATH)
{

}

SplitToolCppJieba::~SplitToolCppJieba()
{

}

vector<string> SplitToolCppJieba::cut(const string &sentense) 
{
    vector<string> words;
    _jieba.Cut(sentense, words, true);
    return words;
}

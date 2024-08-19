#include "cppjieba/Jieba.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::string;
using std::vector;

const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const HMM_PATH = "./dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";

int main(int argc, char** argv) {
    // 构建结巴对象 （操作非常耗时）
    cppjieba::Jieba jieba(DICT_PATH,
                          HMM_PATH,
                          USER_DICT_PATH,
                          IDF_PATH,
                          STOP_WORD_PATH);
    // words 保存单词
    vector<string> words;
    string sentence = "文学、艺术理论的建设和发展，应该密切关注文学、艺术的实际存在状态及其已然或可能发生的变化。这样一个浅近的道理大约谁都不会怀疑。然而，当下正在我们身边发生的艺术世界总体格局的巨大变化却又常常为我们视而不见。这不能不带来诸多理论上的遗憾。";

    jieba.Cut(sentence, words, true);
    for(auto word:words){
        cout << "word = " << word << "\n";
    }
}

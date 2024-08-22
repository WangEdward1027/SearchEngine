#include "../include/DictProducer.h"
#include "../include/SplitToolCppJieba.h"

int main()
{
    SplitToolCppJieba cppjieba;
    DictProducer dict(&cppjieba);
    
    dict.buildEnDict();
    dict.buildEnIndex();

    dict.buildCnDict();
    dict.buildCnIndex();
    
    return 0;
}

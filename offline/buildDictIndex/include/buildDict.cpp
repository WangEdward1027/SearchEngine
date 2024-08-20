#include "../include/DictProducer.h"
#include "../include/SplitToolCppJieba.h"
/* #include "SplitTool.h" */
/* #include "SplitToolCppJieba.h" */

int main()
{
    string dir;
    SplitToolCppJieba cppjieba;
    DictProducer dict(dir, &cppjieba);
    
    dict.buildEnDict();
    dict.buildEnIndex();

    dict.buildCnDict();
    dict.buildCnIndex();
    
    return 0;
}

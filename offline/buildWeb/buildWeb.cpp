#include "DirScanner.h"

int main()
{
    DirScanner dirScanner;  //如果是默认构造函数,不要加括号
    dirScanner.traverse("./dict");
    return 0;
}


#include "RssReader.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    RssReader rss;  
    if (rss.parseRss("auto.xml")) {  
        rss.printRssItems(); // 调用新添加的打印函数  
    } else {  
        cout << "Failed to parse RSS file." << endl;  
    } 
    
    return 0;
}


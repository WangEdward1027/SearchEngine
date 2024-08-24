#include "../../include/PageLib/Configuration.hpp"
#include "../../include/PageLib/DirScanner.hpp"
#include "../../include/PageLib/FileProcessor.hpp"
#include "../../include/PageLib/PageLib.hpp"

#include <iostream>
#include "../../include/PageLib/tinyxml2.h"
#include <regex>
#include <fstream>

using std::cout;
using std::endl;
using std::ofstream;

using namespace se;
using namespace tinyxml2;

//测试单例模式以及 Configuration的getConfigMap
//getStopWordList方法 输出配置文件内容
//以及停用词前50个
void test()
{
    Configuration *ps1 = Configuration::getInstance();
    Configuration *ps2 = Configuration::getInstance();
    auto it = ps1->getConfigMap().begin();
    while(it !=ps1->getConfigMap().end())
    {
        cout << it->first <<"--->"
            <<it->second <<endl;
        ++it;
    }

    auto ti = ps2->getStopWordList().begin();
    for(size_t idx = 0; idx != 50 ; ++idx)
    {
        cout << *ti << endl;
        ++ti;
    }
}

//测试文件扫描类的扫描结果
void test2()
{
    DirScanner ds;
    ds("../data/xml");
    auto it = ds.files().begin();
    while(it != ds.files().end())
    {
        cout << *it << endl;
        ++it;
    }
}

//测试文件扫描类配合Config类
void test3()
{
    //扫描文件夹的步骤
    //1.获取Configuratin类
    Configuration *ps1 = Configuration::getInstance();
    //2.创建扫描类对象ds
    DirScanner ds;
    //3.输入关键词获取路径并重载给ds
    ds(ps1->getConfigMap()["xml"]);


    auto it = ds.files().begin();
    while(it != ds.files().end())
    {
        cout << *it << endl;
        ++it;
    }
}

void test4()
{
    /* Configuration *ps1 = Configuration::getInstance(); */
    /* DirScanner ds; */
    /* ds(ps1->getConfigMap()["xml"]); */
    /* //打开文件流 */
    
    /* ofstream ofsNet(ps1->getConfigMap()["page"]); */
    /* ofstream ofsOffset(ps1->getConfigMap()["offset"]); */
    
    /* cout << "1111" <<endl; */
    /* FileProcessor fp; */
    /* auto xml= fp.process(ds.files()[30]); */
    /* /1* cout << ds.files()[4] <<endl; *1/ */
    /* auto it = xml._page.begin(); */
    /* cout << "222" <<endl; */
    /* while(it != xml._page.end()) */
    /* { */
    /*     cout << *it << endl; */
    /*     ++it; */
    /* } */

    /* auto ct = xml._offset.begin(); */
    /* while(ct !=xml._offset.end()) */
    /* { */
    /*     cout << ct->first << endl; */
    /*     ++ct; */
    /* } */

    /* ofsNet.close(); */
    /* ofsOffset.close(); */
}

void test5()
{
    PageLib pg;
    pg.create();
    pg.store();

    /* cout <<pg._pages[2630] << endl; */
    /* cout << "---------------------" << endl; */
    /* cout << "---------------------" << endl; */
    /* cout << pg._pages[2631] <<endl; */
    /* cout << "---------------------" << endl; */
    /* cout << "---------------------" << endl; */
    /* cout<<pg._pages[2632] << endl; */

    /* auto mm = pg._offsetLib.begin(); */
    /* for(size_t idx = 0;idx < 2640 ;++idx) */
    /* { */
    /*     if(idx > 2625 ) */
    /*     { */
    /*         cout << mm->first <<"----->" */
    /*             <<mm->second.first <<"&" <<mm->second.second<< endl; */
    /*     } */
    /*     ++mm; */
    /* } */
}

int main()
{
#if 0
    cout <<"test >>>>" <<endl;
    test();
    cout << endl;
    cout <<"---------------------" <<endl;
    cout<<"test2>>>>>"<<endl;
    test2();
    cout << endl;
    cout <<"---------------------" <<endl;
    cout<<"test3>>>>>"<<endl;
    test3();
#endif
    cout <<"---------------------" <<endl;
    cout<<"test4>>>>>"<<endl;
    /* test4(); */
    test5();
}

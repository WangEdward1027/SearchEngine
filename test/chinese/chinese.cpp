#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

//测试汉字的size
void test1()
{
    string word = "Hi中国";   
    cout << word.size() << endl; //测试发现,一个汉字的size是3
    
    string word2 = "。。";   //汉字符号也是3个字节,每个汉字字符的size也是3
    cout << word2.size() << endl;
}

//判断是中文还是英文,通过最高位比特是否为1:中文为1,英文为0
void test2()
{
    string str = "hi你好";
    for(size_t i = 0; i < str.size();){
        // 1000 0000 & ch
        if((str[i] & 0x80) == 0){
            cout << "英文: " << str.substr(i,1) << endl; 
            i++;
        }else{
            cout << "中文: " << str.substr(i,3) << endl;
            i += 3;
        }
    }
}

//尝试分离出一个个的汉字
void test3()
{
    string word = "你好中国";
    for(int i = 0; i < word.size(); i+=3){
        string subword = word.substr(i,3);
        cout << subword << endl;
    }
}

int main()
{
    /* test1(); */
    /* test2(); */
    test3();
    return 0;
}

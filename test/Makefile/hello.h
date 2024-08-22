#ifndef __HELLO_H__
#define __HELLO_H__

class hello
{
public:
    hello();  //类的构造函数和析构函数，要么就不声明,编译器会执行默认的构造和析构函数
    ~hello(); //如果声明了,就一定要实现。哪怕函数体内是空的
    void sayHi();   
};

#endif

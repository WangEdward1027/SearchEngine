 ///
 /// @file    Noncopyable.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-11-30 17:36:55
 ///
 
#ifndef __WD_NONCOPYABLE_HPP__
#define __WD_NONCOPYABLE_HPP__


namespace se
{


//1.不希望进行复制
//2.不希望直接创建对象
class Noncopyable
{
protected:
	// ==> 定义了protected型构造函数的类也称为抽象类
	Noncopyable() {} 
	~Noncopyable() {}

	Noncopyable(const Noncopyable&)= delete;
	Noncopyable & operator=(const Noncopyable&) = delete;
};

}//end of namespace se
 
 
 
#endif

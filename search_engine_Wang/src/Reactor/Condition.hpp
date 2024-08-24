 ///
 /// @file    Condition.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-11-30 15:23:48
 ///
 
#ifndef __WD_CONDITION_HPP__
#define __WD_CONDITION_HPP__

#include "Noncopyable.hpp"
#include <pthread.h>



namespace se
{

class MutexLock;//互斥锁的前向声明
class Condition : Noncopyable
{
public:
	Condition(MutexLock &);
	~Condition();

	void wait();
	void notify();
	void notifyAll();

private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};

}//end of namespace se
 
 
 
#endif

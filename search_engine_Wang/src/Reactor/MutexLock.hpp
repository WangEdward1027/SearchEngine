 ///
 /// @file    MutexLock.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-11-30 15:09:46
 ///
 
#ifndef __WD_MUTEXLOCK_HPP__
#define __WD_MUTEXLOCK_HPP__

#include "Noncopyable.hpp"

#include <pthread.h>

namespace se
{

class MutexLock : Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();

	pthread_mutex_t * getMutexLockPtr() 
	{	return &_mutex;	}

private:
	//可以进行复制==》值语义 ==》值传递
	//
	//C++11之前的写法：禁止复制==》对象语义
	//MutexLock(const MutexLock&);
	//MutexLock & operator=(const MutexLock&);

	//C++11标准之后的写法
	//MutexLock(const MutexLock&) = delete;
	//MutexLock & operator=(const MutexLock&) = delete;
private:
	pthread_mutex_t _mutex;
};

//利用RAII的技术，进行保护
class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex)
	: _mutex(mutex)
	{
		_mutex.lock();
	}

	~MutexLockGuard()
	{	_mutex.unlock();	}

private:
	MutexLock & _mutex;
};

}//end of namespace se
 
 
 
#endif

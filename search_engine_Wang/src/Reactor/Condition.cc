 ///
 /// @file    Condition.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-11-30 15:26:02
 ///
 

#include "Condition.hpp"
#include "MutexLock.hpp"// 在条件变量的实现文件中才加上互斥锁的头文件

#include <stdio.h>
#include <errno.h>

namespace se
{

Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
	int ret = 0;
	if((ret = pthread_cond_init(&_cond, nullptr))!=0){
		errno = ret;
		perror("pthread_cond_init");
	}
}

void Condition::wait()
{
	int ret = 0;
	if((ret = pthread_cond_wait(&_cond, _mutex.getMutexLockPtr()))!=0){
		errno = ret;
		perror("pthread_cond_wait");
	}
}

void Condition::notify()
{
	int ret = 0;
	if((ret = pthread_cond_signal(&_cond))!=0){
		errno = ret;
		perror("pthread_cond_signal");
	}
}

void Condition::notifyAll()
{
	int ret = 0;
	if((ret = pthread_cond_broadcast(&_cond))!=0){
		errno = ret;
		perror("pthread_cond_broadcast");
	}
}

Condition::~Condition()
{
	int ret = 0;
	if((ret = pthread_cond_destroy(&_cond))!=0){
		errno = ret;
		perror("pthread_cond_destroy");
	}
}

}//end of namespace se

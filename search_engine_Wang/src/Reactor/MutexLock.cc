 ///
 /// @file    MutexLock.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-11-30 15:12:54
 ///
 
#include "MutexLock.hpp"
#include <stdio.h>
#include <errno.h>

namespace se
{
	
MutexLock::MutexLock()
{
	int ret = 0;
	if((ret = pthread_mutex_init(&_mutex, nullptr)) != 0) {
		errno = ret;
		perror("pthread_mutex_init");
	}
}


MutexLock::~MutexLock()
{
	int ret = 0;
	if((ret = pthread_mutex_destroy(&_mutex)) != 0) {
		errno = ret;
		perror("pthread_mutex_destroy");
	}
}

void MutexLock::lock()
{
	int ret = 0;
	if((ret = pthread_mutex_lock(&_mutex)) != 0) {
		errno = ret;
		perror("pthread_mutex_lock");
	}
}

void MutexLock::unlock()
{
	int ret = 0;
	if((ret = pthread_mutex_unlock(&_mutex)) != 0) {
		errno = ret;
		perror("pthread_mutex_unlock");
	}
}

}//end of namespace se

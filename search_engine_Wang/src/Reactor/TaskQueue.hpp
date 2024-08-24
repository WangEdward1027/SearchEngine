///
/// @file    TaskQueue.hpp
/// @author  lemon(haohb13@gmail.com)
/// @date    2021-11-30 15:58:59
///

#ifndef __WD_TASKQUEUE_HPP__
#define __WD_TASKQUEUE_HPP__

#include "MutexLock.hpp"
#include "Condition.hpp"
#include "Task.hpp"

#include <queue>
using std::queue;

namespace se
{

	using ElemType = Task;

	class TaskQueue
	{
	public:
		TaskQueue(size_t capacity);

		bool empty() const;
		bool full() const;
		void push(ElemType &&);
		ElemType pop();

		void wakeup();

	private:
		size_t _capacity;
		queue<ElemType> _que;
		MutexLock _mutex;
		Condition _notEmpty;
		Condition _notFull;
		bool _flag;
	};

} //end of namespace se

#endif

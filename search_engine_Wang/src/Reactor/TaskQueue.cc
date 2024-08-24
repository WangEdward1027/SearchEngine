 ///
 /// @file    TaskQueue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2021-11-30 16:02:40
 ///
 
#include "TaskQueue.hpp"

namespace se
{

TaskQueue::TaskQueue(size_t capacity)
: _capacity(capacity)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
, _flag(true)
{}

bool TaskQueue::empty() const
{
	return _que.size() == 0;
}

bool TaskQueue::full() const
{	return _que.size() == _capacity;	}


//该方法运行在生产者线程
void TaskQueue::push(ElemType && elem)
{
	//1.定义一个互斥锁保护类的局部对象
	//当对象销毁时，一定会执行析构函数，从而达到解锁的目的
	
	{//2. 使用语句块可以控制加锁的范围
	MutexLockGuard autolock(_mutex);
	if(full()) {
		//发现队列已满，只能等待,阻塞当前线程
		_notFull.wait();
	}

	//....代码维护时，如果不小心在这里退出了
	//队列还有空间时，放入数据
	_que.push(std::move(elem));
	}

	//队列中有数据时，通知消费者线程取数据
	_notEmpty.notify();//有概率会唤醒多个条件变量的
}

//该方法运行在消费者线程
ElemType TaskQueue::pop()
{

	MutexLockGuard autolock(_mutex);
	while(_flag && empty()) { //使用while是为了防止发生虚假唤醒的情况
		//发现队列为空，只能等待，阻塞当前线程
		_notEmpty.wait();
	}

	if(_flag) {
		//获取队列头部的元素
		ElemType tmp;
		tmp = _que.front();
		_que.pop();
		
		//队列还有空间的时候，通知生产者线程放数据
		_notFull.notify();

		return tmp;
	} else 
		return nullptr;
}

void TaskQueue::wakeup()
{
	_flag = false;
	_notEmpty.notifyAll();
}


}//end of namespace se

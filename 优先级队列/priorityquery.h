


#pragma once
#include"heap.h"
#include<iostream>
#include<cstdlib>
#include<cassert>

using namespace std;

template<typename T,typename Compare=Greater<T>>
class PriorityQueue
{
public:
	PriorityQueue(T* a,size_t size)
		:_h(a,size)
	{
		
	}
	void Push(const T& d)
	{
		_h.Push(d);
	}
	void Pop()
	{
		_h.pop();
	}
	size_t Size()
	{
		return _h.Size();
	}
	const T& Top()
	{
		return _h.Top();
	}
	bool empty()
	{
		return _h.empty();
	}
protected:
	Heap<T, Compare> _h;
};
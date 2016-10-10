//堆

#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>

template<typename T>
class BinaryHeap
{

	
public:
	//默认构造函数
	//BinaryHeap() = default;
	//构造函数
	BinaryHeap(int capacit = 10)
		:_capacity(capacit)
		, _size(0)
		, _pheap(new T [_capacity])
	{
		;
	}
	//析构函数
	~BinaryHeap()
	{
		delete[] _pheap;
		
	}
	//堆中插入一个节点
	void Insert(const T& val)
	{
		if (_size == _capacity)
			return;
		_pheap[_size] = val;
		SiftUp(_size);
		_size++;

	}
	//堆中删除值为data的节点
	void Remove(const T& data)
	{
		if (_size == 0)
			return;
		int index = -1;
		for (size_t i = 0; i < _size; i++)
		{
			if (_pheap[i] == data)
			{
				index = i;
				break;
			}
		}
		if (index == -1)
		{
			return;
		}
		_pheap[index] = _pheap[_size - 1];
		SiftDown(0, _size - 1);
	}
	//打印整个堆
	void PrintHeap()
	{
		for (size_t i = 0; i < _size; i++)
		{
			cout << _pheap[i] << " ";
		}
		cout << endl;
	}
	//取得堆上的最值
	T Top()
	{
		if (_size！ = 0)
			return _pheap[0];
	}
	//创建堆
	void CreateMinHeap(T* a, size_t length)
	{
		if (_size == _capacity)
		{
			return ;
		}
		else
		{
			for (size_t i = 0; i < length; i++)
			{
				Insert(a[i]);
			}
		}
	}
	

protected:
	//上滑调整法
	void SiftUp(size_t size)
	{
		T tmp = _pheap[size];
		while (size>0)
		{
			size_t parent = (size - 1) / 2;
			if (tmp < _pheap[parent])
				break;
			else
			{
				_pheap[size] = _pheap[parent];
				size = parent;
			}
		}
		_pheap[size] = tmp;
	}
	//下滑调整法
	void SiftDown(size_t cur, size_t end)
	{
		int child = 2 * cur + 1;
		T tmp = _pheap[cur];
		while (child <= end)
		{
			if (child < end&&_pheap[child] < _pheap[child + 1])
				child++;
			if (tmp>_pheap[child])
				break;
			else
			{
				_pheap[cur] = _pheap[child];
				cur = child;
				child = child * 2 + 1;
			}
		}
		_pheap[cur] = tmp;

	}

protected:
	size_t _size;
	size_t _capacity;
	T* _pheap;
};




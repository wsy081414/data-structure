#pragma once 

#include<iostream>
#include<cassert>
#include<cstdlib>



using namespace std;



template<typename T>
class Stack
{
public:
	Stack()
		: _array(0)
		, _sz1(0)
		, _sz2(0)
		, _capacity(0)
	{
	}
	~Stack()
	{
		if (_array != NULL)
		{
			delete[] _array;
		}
	}
	void push1(const T& d)
	{
		CheckCapacity();
		_array[_sz1] = d;
		_sz1++;
	}
	void pop1()
	{
		assert(_sz1 > 0);
		_sz1--;
	}
	bool empty1()
	{
		return _sz1 == 0;
	}
	void push2(const T& d)
	{
		CheckCapacity();
		_array[_sz2] = d;
		_sz2--;
	}
	void pop2()
	{
		assert(_sz2 < _capacity - 1);
		_sz2++;
	}
	bool empty2()
	{
		return _sz2 == _capacity - 1;
	}
	size_t size1()
	{
		return _sz1;
	}
	size_t size2()
	{
		return _capacity - 1 - _sz2;
	}
	T& top1()
	{
		assert(_sz1 > 0);
		return _array[_sz1 - 1];
	}
	T& top2()
	{
		assert(_sz2 != 0 || _sz2 < _capacity - 1);
		return _array[_sz2 + 1];
	}

	void CheckCapacity()
	{
		if (_sz1 ==_sz2)
		{
			size_t NewCapacity = 2 * _capacity+2 ;
			T* tmp = new T[NewCapacity];
			for (size_t i = 0; i < _sz1; ++i)
			{
				tmp[i] = _array[i];
			}
			size_t j(0);
			for (j = NewCapacity - 1; j<NewCapacity-1&&j>NewCapacity - _sz2; --j)
			{
				tmp[j] = _array[_capacity];
			}
			_sz2 = NewCapacity - (_capacity - _sz2);
			_capacity = NewCapacity;
			_array = tmp;
		}
		
	}
protected:
	T* _array;
	size_t _sz1;
	size_t _sz2;
	size_t _capacity;
};
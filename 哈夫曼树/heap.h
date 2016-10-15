
//¶Ñ

#pragma once
#include<iostream>
#include<cstdlib>
#include<cassert>
#include<vector>

using namespace std;

template<typename T>
class Less
{
public:
	bool operator ()(const T& a, const T& b)
	{
		return a < b;
	}
};

template<typename T>
class Greater
{
public:
	bool operator ()(const T& a, const T& b)
	{
		return a > b;
	}
};

//´ó¶Ñ
template<typename T, typename Compare = Less<T>>
class Heap
{
public:
	Heap() = default;
	Heap(T *a, size_t size = 0)
	{
		_a.reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		for (int j = (_a.size() - 2) / 2; j >= 0; j--)
		{
			_AdjustDown(j);
		}

	}
	void Pop()
	{
		assert(!_a.empty());
		swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		if (_a.size()!=0)
			_AdjustDown(0);
	}
	void Push(const T& d)
	{
		_a.push_back(d);
		_AdjustUp(_a.size() - 1);
	}
	const T& Top()
	{
		assert(!_a.empty());
		return _a[0];

	}
	size_t Size()
	{
		return _a.size();
	}
	bool empty()
	{
		return _a.empty();
	}
protected:
	void _AdjustDown(int root)
	{
		assert(!_a.empty());
		size_t parent = root;
		size_t child = parent * 2 + 1;
		while (parent<_a.size())
		{
			Compare com;

			if (child + 1<_a.size()
				&& com(_a[child + 1], _a[child]))
			{
				++child;
			}
			if (child<_a.size() && com(_a[child], _a[parent]))
			{
				std::swap(_a[child], _a[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void _AdjustUp(size_t child)
	{
		assert(!_a.empty());
		while (child>0)
		{
			Compare com;
			size_t parent = (child - 1) / 2;
			if (com(_a[child], _a[parent]))
			{
				std::swap(_a[child], _a[parent]);
				child = parent;
			}
			else
			{
				break;
			}
		}

	}

protected:
	std::vector<T > _a;
};




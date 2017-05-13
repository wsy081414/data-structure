#ifndef __UNIONSET__
#define __UNIONSET__
#include<iostream>
#include<stdlib.h>
#include<assert.h>
class UnionSet
{
private:
	int *_parent;
	int *_size;	  //记录没颗以这个根为节点的树的子节点的个数。
	int _count;
public:

	//进行构造并查集合
	UnionSet(int count)
		:_count(count)
		, _parent(new int [_count])			//记录了每个节点的parent
		, _size(new int [_count])			//记录了每个节点作为根节点的时候额子节点树目
	{
		for (int i = 0; i < _count; i++)
		{
			_parent[i] = i;
			_size[i] = 1;
		}
	}

	//析构删除
	~UnionSet()
	{
		delete[] _parent;
		delete[] _size;
	}

	//作为并查集树查找根节点的函数
	int find(int p)
	{
		assert(p >= 0 && p < _count);
		while (p != _parent[p])
		{
			p = _parent[p];
		}
		return p;
	}

	//用来判断是否连接
	bool isConnected(int p, int q)
	{

		//直接使用两个节点的根节点进行操作就可以了
		assert(p >= 0 && p < _count);
		assert(q >= 0 && q < _count);
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot != qRoot)
			return false;
		return true;
	}

	//用来合并
	void unionElements(int p, int q)
	{
		assert(p >= 0 && p < _count);
		assert(q >= 0 && q < _count);


		//先找到两个根
		int pRoot = find(p);
		int qRoot = find(q);

		//相等返回
		if (pRoot = qRoot)
			return;

		//在这里来说，我们所需要进行的就是把节点少的树放到节点多的树的下面，这样能够提高效率。
		if (_size[pRoot] < _size[qRoot])
		{
			_parent[pRoot] = qRoot;
			_size[qRoot] += _size[pRoot];
		}
		else
		{
			_parent[qRoot] = pRoot;
			_size[pRoot] += _size[qRoot];
		}
	}
};




#endif


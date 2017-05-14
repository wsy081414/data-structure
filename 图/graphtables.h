#ifndef __GRAPH_TABLES_H__
#define __GRAPH_TABLES_H__
#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<vector>
#include<list>
using namespace std;

//邻接表
class Graph_tables
{
private:
	int _n, _m;
	bool _directed;
	vector<vector<int>> _g;	//也可以使用list后续操作

public:
	Graph_tables(int n, bool directed)
		:_n(n)
		, _directed(directed)
	{
		for (int i = 0; i < _n; i++)
		{
			_g.push_back(vector<int >());
		}
	}
	~Graph_tables()
	{
	}

	//返回多少个点
	int V()
	{
		return _n;
	}

	//返回多少条边
	int E()
	{
		return _m;
	}

	//进行添加路径
	void addEdge(int v, int w)
	{
		assert(v >= 0 && v < _n);
		assert(w >= 0 && w < _n);

		_g[v].push_back(w);			//邻接表进行添加
		
		if (v != w && !_directed)	//排除自己指向自己的行为并且为无向图的时候
		{
			_g[w].push_back(v);
		}
		_m++;
	}
	//判断是否有路径
	bool hasEdge(int v, int w)
	{
		assert(v >= 0 && v < _n);
		assert(w >= 0 && w < _n);

		for (int i = 0; i < _g[v].size(); i++)
		{
			if (w == _g[v][i])
			{
				return true;
			}
		}

		return false;
	}

};


#endif
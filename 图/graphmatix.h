#ifndef __GRAPH_MATIX_H__
#define __GRAPH_MATIX_H__
#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<vector>

using namespace std;
//邻接矩阵使用在稠密图的情况，稠密图就是边比较多的情况
class Graph_Matix
{
private:
	int _m, _n;					//n用来记录多少个节点，m记录多少条边	
	bool _directed;				//判断图是否有向
	std::vector<vector<bool >> _g;	//绘制邻接矩阵
public:

	//构造函数进行构造。
	Graph_Matix(int n, bool directed)
		:_directed(directed)
	{
		for (int i = 0; i < _n; i++)
		{
			_g.push_back(vector<bool>(n, false));
		}
	}

	~Graph_Matix()
	{}


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

		if (hasEdge(v, w))
			return;
		
		_g[v][w] = true;

		if (!_directed)
			_g[w][v] = true;
		_m++;
	}


	//判断是否有路径
	bool hasEdge(int v, int w)
	{
		return _g[v][w];
	}
};


#endif
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

	class Travseadjacent
	{
	private:
		Graph_Matix& _G;
		int _v;
		int _index;
	public:
		Travseadjacent(Graph_Matix& g, int v)
			:_G(g)
			, _v(v)
			, _index(-1)
		{
		}
		~Travseadjacent(){}

		int begin()
		{
			_index = -1;
			return next();
		}

		int next()
		{
			for (int i = _index+1; i < _G._g[_v].size(); i++)		//返回邻接矩阵存在的下一项
			{
				if (_G._g[_v][i] == true)
					return _G._g[_v][i];
			}
			return -1;
		}

		bool end()
		{
			if (_index >= _G._g[_v].size())
				return false;
			return true;
		}


	};
};

template<typename Graph>
class compent
{
private:
	Graph &G;
	bool *visited;
	int *id;
	int ccount;
	void dfs(int i)
	{
		visited[i] = true;
		id[i] = ccount;

		typename Graph::Travseadjacent a(G, i);			//使用前面使用的迭代器进行遍历操作
		for (int i = a.begin(); i < a.end(); i = a.next())
		{
			if (!visited[i])							//没有访问过，那么就采用深度优先的方式
				dfs(i);
		}
	}
public:
	compent(Graph g)
		:G(g)
		, visited( new bool [G.V()])
		, id(new int [G.V()])
		, ccount(0)
	{
		for (int i = 0; i < G.V(); i++)
		{
			visited[i] = false;
			id[i] = -1;
		}

		for (int j = 0; j < G.V(); j++)
		{
			if (!visited[j])
			{
				dfs(i);
				ccount++;
			}
		}
	}

	~compent()
	{
		delete[] visited;
		delete[] id;
	}

};


#endif
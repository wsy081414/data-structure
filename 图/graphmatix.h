#ifndef __GRAPH_MATIX_H__
#define __GRAPH_MATIX_H__
#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<vector>

using namespace std;
//�ڽӾ���ʹ���ڳ���ͼ�����������ͼ���Ǳ߱Ƚ϶�����
class Graph_Matix
{
private:
	int _m, _n;					//n������¼���ٸ��ڵ㣬m��¼��������	
	bool _directed;				//�ж�ͼ�Ƿ�����
	std::vector<vector<bool >> _g;	//�����ڽӾ���
public:

	//���캯�����й��졣
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


	//���ض��ٸ���
	int V()
	{
		return _n;
	}

	//���ض�������
	int E()
	{
		return _m;
	}
	
	//�������·��
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


	//�ж��Ƿ���·��
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
			for (int i = _index+1; i < _G._g[_v].size(); i++)		//�����ڽӾ�����ڵ���һ��
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

		typename Graph::Travseadjacent a(G, i);			//ʹ��ǰ��ʹ�õĵ��������б�������
		for (int i = a.begin(); i < a.end(); i = a.next())
		{
			if (!visited[i])							//û�з��ʹ�����ô�Ͳ���������ȵķ�ʽ
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
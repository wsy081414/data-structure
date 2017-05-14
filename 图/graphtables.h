#ifndef __GRAPH_TABLES_H__
#define __GRAPH_TABLES_H__
#include<iostream>
#include<stdlib.h>
#include<assert.h>
#include<vector>
#include<list>
using namespace std;

//�ڽӱ�
class Graph_tables
{
private:
	int _n, _m;
	bool _directed;
	vector<vector<int>> _g;	//Ҳ����ʹ��list��������

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

		_g[v].push_back(w);			//�ڽӱ�������
		
		if (v != w && !_directed)	//�ų��Լ�ָ���Լ�����Ϊ����Ϊ����ͼ��ʱ��
		{
			_g[w].push_back(v);
		}
		_m++;
	}
	//�ж��Ƿ���·��
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

	//�����ڱ�

	class Travseadjacent
	{
	private:
		Graph_tables& _g;		//�����Ǹ�ͼ
		int _v;					//����
		int _index;				//index
	public:
		Travseadjacent(Graph_tables& g, int v)	//���г�ʼ��
			:_g(g)
			, _v(v)
			, _index(-1)
		{}
		~Travseadjacent()
		{}

		int begin()								//begin������
		{
			_index = 0;
			if (_g._g[_v].size())
				return _g._g[_v][_index];
			return -1;
		}

		int next()				
		{
			_index++;
			if (_index < _g._g[_v].size())		//�����ڽӱ����һ��
				return _g._g[_v][_index];
			return -1;
		}

		bool end()
		{
			if (_index >= _g._g[_v].size())
				return false;
			return true;
		}


	};

};


#endif
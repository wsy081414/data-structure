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
};


#endif
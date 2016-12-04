#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>
#include<vector>
#include"unionset.hpp"
#include<string>
using namespace std;

template<typename V, typename W>
class GraphLink
{
public:
	struct Node
	{
		W _w;
		size_t _dst;
		size_t _src;
		Node* _next;
		Node(size_t& src, size_t& dst, const W& w)
			:_w(w)
			, _dst(dst)
			, _src(src)
			, _next(NULL)
		{
		}
	};

	GraphLink(V* vertexs, int size, bool isDirected = false)
		:_vertexs(vertexs,vertexs+size)
		, _isDirected(isDirected)
		, _tables(size, NULL)
	{
	}

	~GraphLink()
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			Node* cur = _tables[i];
			Node* del = NULL;
			while (cur)
			{
				del = cur;
				cur = cur->_next;
				delete del;
			}
		}
		
	}
	void InsertVertexs(const V& v)
	{
		_vertexs.push_back(v);
	}
	bool InsertEdge(const V& v1, const V& v2, const W& w = w())
	{
		size_t src = 0;
		size_t dst = 0;
		try
		{
			src = GetVertexPos(v1);
			dst = GetVertexPos(v2);
		}
		catch (const invalid_argument& e)
		{
			cout << e.what() << endl;
			cout << "----64行----" << endl;
		}
		if (_isDirected)
		{
			Node* cur = new Node(src, dst, w);
			cur->_next = _tables[src];
			_tables[src] = cur;
			
		}
		else
		{
			Node* cur = new Node(src, dst, w);
			Node* dcur = new Node(dst, src, w);

			cur->_next = _tables[src];
			_tables[src] = cur;

			dcur->_next = _tables[dst];
			_tables[dst] = dcur;
		}
		return true;
	}
	//用来在顶点集合当中来找v，找到返回顶点集合的下标，这样就可以确定在矩阵当中的位置。
	size_t GetVertexPos(const V &v)
	{
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			if (_vertexs[i] == v)
			{
				return i;
			}
		}

		throw std::invalid_argument("参数有问题");
	}
	void DFS(const V& v)
	{
		//给出一个vector，来记录标记是否对节点进行访问。
		vector<bool>visited(_vertexs.size(), false);
		_DFS(GetVertexPos(v), visited);
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			if (visited[i] == false)
				_DFS(i, visited);
		}
		cout << endl;
	}

	void BFS(const V& v)
	{
		vector <bool >visited(_vertexs.size(), false);
		queue<int > q;
		int top = GetVertexPos(v);
		q.push(top);
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			if (visited[cur] == false)
			{
				cout << _vertexs[cur] << ":" << cur << "->";
				visited[cur] = true;
			}
			Node* p = _tables[cur];
			while (p)
			{
				if (visited[p->_dst]==false)
					q.push(p->_dst);
				p = p->_next;
			}
		}
	}
	//最小生成树
	bool MinTree(GraphLink<V, W>& mintree)
	{
		//第一步先判断是否为无项图，如果为有向图，那么就没有最小生成树的概念。
		if (_isDirected == true)
		{
			return flase;
		}
		//然后把所有的邻接表的顶点放入最小生成树当中去。
		mintree._vertexs = _vertexs;
		//设置最小生成树的邻接表
		mintree._tables.resize(_tables.resize());
		
		struct Compare
		{
			bool operator()(Node* l, Node* r)
			{
				return l->_weight < r->_weight;
			}

		};
		vector<Node* >minheap;
		for (int i = 0; i < _tables.size(); i++)
		{
			Node* cur = _tables[i];
			while (cur)
			{
				minheap.push_back(cur);
				cur = cur->_next;
			}
		}
		//生成小堆，方便每次取出最短路径
		make_heap(minheap.begin(), minheap end, Compare());
		//使用并查集
		UnionSet s(_vertexs.size());
		size_t n = 0;
		while (n < _vertexs.size() - 1)
		{
			//如果堆为空。这个时候说明存在那种单独的点。
			if (!minheap.empty())
			{
				return false;
			}

			pop_heap(minheap.begin(), minheap.end(), Compare());
			Node * minedge = minheap.back();
			minheap.pop_back();
			size_t root1 = s.CountRoot(minedge->_dst);
			size_t root2 = s.CountRoot(minedge->_src);
			if (root1 != root2)
			{
				s.Union(minedge->_dst, minedge->_src);
				mintree.InsertEdge(minedge->_src, minedge->_src, minedge->_w);
				n++;
			}
		}
		return true;


	}
protected:
	void _DFS(size_t src, vector<bool>& visited)
	{
		cout << _vertexs[src] << ":" << src << "->";
		visited[src] = true;
		Node *cur = _tables[src];
		while (cur)
		{
			if (visited[cur->_dst] == false)
			{
				_DFS(cur->_dst, visited);
			}
			cur = cur->_next;
		}
	}

protected:
	std::vector<V>_vertexs;	//顶点
	bool _isDirected;

	vector<Node* >_tables;	//邻接表
};
void TestGraphLink()
{
	string v[] = { "西安", "西宁", "北京", "上海", "成都" };
	GraphLink<string, size_t> gm(v, 5);
	gm.InsertEdge("西安", "西宁", 1200);
	gm.InsertEdge("西宁", "北京", 1000);
	gm.InsertEdge("西安", "成都", 400);
	gm.InsertEdge("成都", "上海", 500);
	gm.BFS("西安");

}
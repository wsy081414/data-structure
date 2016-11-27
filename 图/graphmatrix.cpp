#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>
#include<vector>
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
			cout << "----64��----" << endl;
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
	//�����ڶ��㼯�ϵ�������v���ҵ����ض��㼯�ϵ��±꣬�����Ϳ���ȷ���ھ����е�λ�á�
	size_t GetVertexPos(const V &v)
	{
		for (size_t i = 0; i < _vertexs.size(); i++)
		{
			if (_vertexs[i] == v)
			{
				return i;
			}
		}

		throw std::invalid_argument("����������");
	}
	void DFS(const V& v)
	{
		//����һ��vector������¼����Ƿ�Խڵ���з��ʡ�
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
	std::vector<V>_vertexs;	//����
	bool _isDirected;

	vector<Node* >_tables;	//�ڽӱ�
};
void TestGraphLink()
{
	string v[] = { "����", "����", "����", "�Ϻ�", "�ɶ�" };
	GraphLink<string, size_t> gm(v, 5);
	gm.InsertEdge("����", "����", 1200);
	gm.InsertEdge("����", "����", 1000);
	gm.InsertEdge("����", "�ɶ�", 400);
	gm.InsertEdge("�ɶ�", "�Ϻ�", 500);
	gm.BFS("����");

}
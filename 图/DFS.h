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
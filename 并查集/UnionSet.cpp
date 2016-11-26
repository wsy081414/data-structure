#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>

using namespace std;

/*������֪��n���˺�m�Ժ��ѹ�ϵ����������r����
�����������ֱ�ӻ��ӵĺ��ѣ����ѵĺ��ѵĺ���...����
����Ϊ��������ͬһ������Ȧ����д���������n������һ���ж��ٸ�����Ȧ��
���磺n = 5��m = 3��r = {{1 , 2} , {2 , 3} , {4 , 5}}��
��ʾ��5���ˣ�1��2�Ǻ��ѣ�2��3�Ǻ��ѣ�4��5�Ǻ��ѣ�
��1��2��3����һ������Ȧ��4��5������һ������Ȧ�����Ϊ2������Ȧ��*/


//˼·���������ò��鼯�����������⡣

//���鼯
class UnionSet
{
public:
	UnionSet(int n)
		:_size(n + 1)
	{
		//����һ�����飬�������ȫΪ-1����Ϊ��-1.����ʹ��memset�Ϳ����ˣ����򣬿���forѭ��
		_parent = new int[n + 1];
		memset(_parent, -1, sizeof(int)*(n + 1));

	}
	//�ϲ����鼯
	void Union(int r1, int r2)
	{
		//�õ��������鼯�ĸ�
		int root1 = Find(r1);
		int root2 = Find(r2);
		//�ѵڶ������鼯�ӵ���һ���ϣ��Ѹ��ڵ�ŵ����ݡ�
		if (root1 != root2)
		{
			_parent[root1] += _parent[root2];
			_parent[root2] = root1;
		}
	}
	int Find(int index)
	{
		int root = index;
		while (_parent[root] >= 0)
		{
			root = _parent[root];
		}
		return root;
	}

	int CountRoot()
	{
		int count = 0;
		for (int i = 1; i < _size; i++)
		{
			if (_parent[i] <0)
				count++;
		}
		return count;
	}
protected:
	int *_parent;
	int _size;
};
int friends(int n, int m, int arr[][2])
{
	UnionSet a(n);
	for (int i = 0; i < m; i++)
	{
		a.Union(arr[i][0], arr[i][1]);
	}
	int rootcount = a.CountRoot();
	return rootcount;
}
void test1()
{
	int n = 5;
	int m = 3;
	int arr[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };

	int count = friends(n,m, arr);
}

int main()
{
	test1();
	system("pause");
	return 0;
}
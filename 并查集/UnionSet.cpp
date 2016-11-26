#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>

using namespace std;

/*假如已知有n个人和m对好友关系（存于数字r）。
如果两个人是直接或间接的好友（好友的好友的好友...），
则认为他们属于同一个朋友圈，请写程序求出这n个人里一共有多少个朋友圈。
假如：n = 5，m = 3，r = {{1 , 2} , {2 , 3} , {4 , 5}}，
表示有5个人，1和2是好友，2和3是好友，4和5是好友，
则1、2、3属于一个朋友圈，4、5属于另一个朋友圈，结果为2个朋友圈。*/


//思路：我们利用并查集来解决这个问题。

//并查集
class UnionSet
{
public:
	UnionSet(int n)
		:_size(n + 1)
	{
		//开辟一个数组，这个数组全为-1，因为是-1.所以使用memset就可以了，否则，考虑for循环
		_parent = new int[n + 1];
		memset(_parent, -1, sizeof(int)*(n + 1));

	}
	//合并并查集
	void Union(int r1, int r2)
	{
		//得到两个并查集的根
		int root1 = Find(r1);
		int root2 = Find(r2);
		//把第二个并查集加到第一个上，把父节点放到内容。
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
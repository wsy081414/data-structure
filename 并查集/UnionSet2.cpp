#ifndef __UNIONSET__
#define __UNIONSET__
#include<iostream>
#include<stdlib.h>
#include<assert.h>
class UnionSet
{
private:
	int *_parent;
	int *_size;	  //��¼û���������Ϊ�ڵ�������ӽڵ�ĸ�����
	int _count;
public:

	//���й��첢�鼯��
	UnionSet(int count)
		:_count(count)
		, _parent(new int [_count])			//��¼��ÿ���ڵ��parent
		, _size(new int [_count])			//��¼��ÿ���ڵ���Ϊ���ڵ��ʱ����ӽڵ���Ŀ
	{
		for (int i = 0; i < _count; i++)
		{
			_parent[i] = i;
			_size[i] = 1;
		}
	}

	//����ɾ��
	~UnionSet()
	{
		delete[] _parent;
		delete[] _size;
	}

	//��Ϊ���鼯�����Ҹ��ڵ�ĺ���
	int find(int p)
	{
		assert(p >= 0 && p < _count);
		while (p != _parent[p])
		{
			p = _parent[p];
		}
		return p;
	}

	//�����ж��Ƿ�����
	bool isConnected(int p, int q)
	{

		//ֱ��ʹ�������ڵ�ĸ��ڵ���в����Ϳ�����
		assert(p >= 0 && p < _count);
		assert(q >= 0 && q < _count);
		int pRoot = find(p);
		int qRoot = find(q);
		if (pRoot != qRoot)
			return false;
		return true;
	}

	//�����ϲ�
	void unionElements(int p, int q)
	{
		assert(p >= 0 && p < _count);
		assert(q >= 0 && q < _count);


		//���ҵ�������
		int pRoot = find(p);
		int qRoot = find(q);

		//��ȷ���
		if (pRoot = qRoot)
			return;

		//��������˵����������Ҫ���еľ��ǰѽڵ��ٵ����ŵ��ڵ����������棬�����ܹ����Ч�ʡ�
		if (_size[pRoot] < _size[qRoot])
		{
			_parent[pRoot] = qRoot;
			_size[qRoot] += _size[pRoot];
		}
		else
		{
			_parent[qRoot] = pRoot;
			_size[pRoot] += _size[qRoot];
		}
	}
};




#endif


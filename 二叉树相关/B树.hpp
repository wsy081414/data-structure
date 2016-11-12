#pragma once
#include<iostream>
#include<cstdlib>
#include<cassert>

using namespace std;

template <typename K,int M>
struct BTreeNode
{
	K _keys[M];						//���������ֵ��
	BTreeNode<K, M>* _sub[M + 1];	//���������ӡ�
	BTreeNode<K, M>* _parent;
	size_t _size;
	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		int i = 0;
		for ( i = 0; i < M; i++)
		{
			_keys[i] = K();
			_sub[i] = K();
		}
		_sub[i] = K();
	}
};


template<typename K,int M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{
	}

	~BTree()
	{}

	
	bool Insert(const K &key)
	{
		//���������ǿ��������
		if (_root == NULL)
		{
			//������ڵ������key��������size++��
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size++;
			return true;
		}
		//ʹ��ͨ�õ�key-value�ṹ���������ҵ���key���ڵĽڵ㡣

		pair<Node*,int > ret=Find(key);

		//��������������ڵ��Ƿ���ڣ����ھ�ֱ��return false��
		if (ret.second == -1)
		{
			return false;
		}

		Node* cur = ret.first;
		K newKey = key;
		Node *sub = NULL;
		//��ʱ��ʾ���ǲ��롣
		while (1)
		{
			//��cur������в��룬���û�����룬���˾ͽ��з��ѡ�
			InsetKey(cur, newKey, sub);

			//С��M�������Ϳ���ֱ�Ӳ���
			if (cur->_size < M)
			{
				return true;
			}

			//���==M����ô��Ӧ�ý��з���
			//�����ҵ��м�Ľڵ�
			size_t mid = cur->_size / 2;
			//����һ���ڵ㣬���������м�ڵ��ұ����еĽڵ㡣
			Node * tmp = new Node;

			size_t j = 0;
			//�����ƶ�sub�Լ����е��ӽӵ㡣
			for (size_t i = mid + 1; i < cur->_size; i++)
			{
				tmp->_keys[j] = cur->_keys[i];
				cur->_keys[i] = K();
				cur->_size--;
				tmp->_size++;
				j++;
			}

			//�ƶ��Ӵ�
			for (j = 0; j < tmp->_size; j++)
			{
				tmp->_sub[j] = cur->_sub[mid + 1 + j];
				cur->_sub[mid + 1 + j] = NULL;
			}


			//�����������ƶ�

			//���Ѿ���
			if (cur->_parent == NULL)
			{
				_root = new Node();
				_root->_keys[0] = cur->_keys[mid];
				cur->_keys[mid] = K();
				cur->_size--;
				_root->_size++;

				_root->_sub[0] = cur;
				cur->_parent = _root;

				_root->_sub[1] = tmp;
				tmp->_parent = _root;
				return true;
			}
			else
			{
				newKey = cur->_keys[mid];
				cur->_keys[mid] = K();
				cur->_size--;
				cur = cur->_parent;
				sub = tmp;
				sub->_parent = cur;

			}
		}
	
	}
	
protected:
	//��ǰ�ڵ�������в���ڵ㡣
	void InsetKey(Node* cur, const K &key, Node* sub)
	{
		int i = cur->_size - 1;
		while (i>=0)
		{
			//���в���
			if (key > cur->_keys[i])
			{
				break;
			}
			//�����ƶ�
			else
			{
				cur->_keys[i + 1] = cur->_keys[i];
				cur->_sub[i + 2] = cur->_sub[i + 1];
			}
			i--;
		}
		//���в���
		cur->_keys[i + 1] = key;
		//������
		cur->_sub[i + 2] = sub;
	
		//���û����ֻ��Ҫ��size++��
		if (cur->_size < M)
		{
			cur->_size++;
		}
	}
	pair <Node*,int > Find(const K &key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			while (i < cur->_size)
			{
				//���С�ڵ�ǰ�����
				if (cur->_keys[i] < key)
				{
					i++;
				}
				//������ڣ�
				else if (cur->_keys[i]>key)
				{
					cur = cur->_sub[i];
					parent = cur;
					break;
				}
				//��ȣ���������ڵ�
				else
				{
					return pair<Node *, int>(NULL, -1);
				}
			}


			//Ϊ�˷�ֹ�����ҷ��ؿ�ָ�����������ǿ�ָ�룬��ô�ͷ��ظ���
			if (cur != NULL && i == cur->_size)
			{
				parent = cur;
				cur = cur->_sub[i];
			}

		}
		return pair<Node *, int>(parent, 1);
		
	}
protected:
	Node* _root;
};

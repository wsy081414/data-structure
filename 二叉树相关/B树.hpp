#pragma once
#include<iostream>
#include<cstdlib>
#include<cassert>

using namespace std;

template <typename K,int M>
struct BTreeNode
{
	K _keys[M];						//用来保存键值。
	BTreeNode<K, M>* _sub[M + 1];	//用来保存子。
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
		//首先来考虑空树的情况
		if (_root == NULL)
		{
			//给这个节点中添加key，并且让size++。
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size++;
			return true;
		}
		//使用通用的key-value结构体来保存找到的key所在的节点。

		pair<Node*,int > ret=Find(key);

		//在这里来看这个节点是否存在，存在就直接return false。
		if (ret.second == -1)
		{
			return false;
		}

		Node* cur = ret.first;
		K newKey = key;
		Node *sub = NULL;
		//此时表示考虑插入。
		while (1)
		{
			//向cur里面进行插入，如果没满插入，满了就进行分裂。
			InsetKey(cur, newKey, sub);

			//小于M，这样就可以直接插入
			if (cur->_size < M)
			{
				return true;
			}

			//如果==M，那么就应该进行分裂
			//首先找到中间的节点
			size_t mid = cur->_size / 2;
			//创建一个节点，用来保存中间节点右边所有的节点。
			Node * tmp = new Node;

			size_t j = 0;
			//进行移动sub以及所有的子接点。
			for (size_t i = mid + 1; i < cur->_size; i++)
			{
				tmp->_keys[j] = cur->_keys[i];
				cur->_keys[i] = K();
				cur->_size--;
				tmp->_size++;
				j++;
			}

			//移动子串
			for (j = 0; j < tmp->_size; j++)
			{
				tmp->_sub[j] = cur->_sub[mid + 1 + j];
				cur->_sub[mid + 1 + j] = NULL;
			}


			//进行其他的移动

			//分裂就是
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
	//向当前节点里面进行插入节点。
	void InsetKey(Node* cur, const K &key, Node* sub)
	{
		int i = cur->_size - 1;
		while (i>=0)
		{
			//进行插入
			if (key > cur->_keys[i])
			{
				break;
			}
			//进行移动
			else
			{
				cur->_keys[i + 1] = cur->_keys[i];
				cur->_sub[i + 2] = cur->_sub[i + 1];
			}
			i--;
		}
		//进行插入
		cur->_keys[i + 1] = key;
		//插入子
		cur->_sub[i + 2] = sub;
	
		//如果没满，只需要对size++；
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
				//如果小于当前，向后
				if (cur->_keys[i] < key)
				{
					i++;
				}
				//如果大于，
				else if (cur->_keys[i]>key)
				{
					cur = cur->_sub[i];
					parent = cur;
					break;
				}
				//相等，返回这个节点
				else
				{
					return pair<Node *, int>(NULL, -1);
				}
			}


			//为了防止出现我返回空指针操作，如果是空指针，那么就返回父亲
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

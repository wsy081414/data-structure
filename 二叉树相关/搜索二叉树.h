#pragma once

#include<iostream>
#include<cstdlib>
#include<cassert>
using namespace std;

template<typename K, typename V>
struct SearchBinaryTreeNode
{
	typedef SearchBinaryTreeNode<K, V> Node;
	SearchBinaryTreeNode()
		:_left(NULL)
		, _right(NULL)
		, _key(0)
	{}
	SearchBinaryTreeNode(const K& key)
		: _left(NULL)
		, _right(NULL)
		, _key(key)

	{
	}


	V _value;
	Node* _left;
	Node* _right;
	K _key;

};

template<typename K, typename V>
class SearchBinaryTree
{
protected:
	typedef SearchBinaryTreeNode<K, V>  Node;

public:
	SearchBinaryTree(const K* arr, size_t size)
	{
		assert(arr);
		for (size_t i = 0; i < size; i++)
		{
			InsertP(arr[i]);
		}

	}
	~SearchBinaryTree()
	{
		_root = _DestorySBT(_root);

	}

	//查找最近的两个公共节点
	Node *FindTwoCommonNode(Node* p1,Node* p2)
	{
		K minkey = 0;
		K maxkey = 0;
		if (p1->_key > p2->_key)
		{
			maxkey = p1->_key;
			minkey = p2->_key;
		}
		else
		{
			maxkey = p2->_key;
			minkey = p1->_key;
		}
		Node* cur = _root;
		while (cur)
		{
			//考虑两类情况，一种是在符合的节点
			if (cur->_key >= minkey&&cur->_key <= maxkey)
			{
				return cur;
			}
			//此时cur所指向节点比两个节点都大。所以两个节点都在左子树
			else if (cur->_key > minkey&&cur->_key > maxkey)
			{
				cur = cur->_left;
			}
			//对比上一步
			else
			{
				cur = cur->_right;
			}

		}

		return NULL;
	}

	//BST转换排序的双向链表
	Node* CovertSortList()
	{
		if (_root == NULL)
		{
			return NULL;
		}
		Node* newlist = NULL;
		Node* prenode = NULL;
		newlist = _CovertSortList(_root,prenode);

		return newlist;
	}
	//递归插入
	bool InsertP(const K& key)
	{
		return _InsertP(_root, key);
	}
	//非递归插入
	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			return true;
		}
		Node *cur = _root;
		Node *parent = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (curcur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		Node *tmp = new Node(key);
		if (key > parent->_key)
		{

			parent->_right = tmp;
		}
		else
		{
			parent->_left = tmp;
		}
		return true;
	}
	//递归删除
	bool RemoveP(const K& key)
	{
		return _RemoveP(_root, key);
	}
	//非递归删除
	bool Remove(const K& key)
	{
		Node *cur = _root;
		Node *parent = NULL;
		Node *del = NULL;
		while (cur&&cur->_key != key)
		{
			if (cur->_key < key)
			{

				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				break;
			}
		}
		//没找到进行处理
		if (cur == NULL)
		{
			return false;
		}
		//对左为空进行处理
		if (cur->left == NULL)
		{

			del = cur;
			if (parent == NULL)
			{
				_root = cur->_right;
			}
			else
			{

				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}
		}
		//对右为空进行处理
		else if (cur->_right == NULL)
		{
			del = cur;
			if (parent == NULL)
			{
				cur = cur->_left;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_right;
				}
			}

		}
		//两个都不为空进行处理
		else
		{
			Node *swapnode = cur->_right;
			while (swapnode->_left)
			{
				parent = swapnode;
				swapnode = swapnode->_left;
			}
			del = swapnode;
			cur->_key = swapnode->_key;
			cur->_value = swapnode->_value;

			if (parent->_left == swapnode)
				parent->_left = swapnode->_right;
			else
				parent->_right = swapnode->_right;
		}
		delete del;
		del = NULL;
		return true;
	}
	//中序打印
	void Inorderprint()
	{
		_Inorderprint(_root);
		cout << endl;
	}
	//判断BST是否为空
	bool Empty()
	{
		return _root == NULL;
	}
	//查找结点
	Node* Find(const K &key)
	{
		if (_root == NULL)
			return NULL;
		Node *cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return NULL;
	}
	//递归查找结点
	bool FindP(const K &key)
	{
		return _FindP(_root, key);
	}
	//返回BST根的键值
	const K& Top()
	{
		return _root->_key;
	}
	//返回BST最小值
	const K& Minvalue()
	{
		assert(_root);
		Node* cur = _root;
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return cur->_value;
	}
	//返回BST最大值
	const K& Maxvalue()
	{
		assert(_root);
		Node *cur = _root;
		while (cur->_right)
		{
			cur = cur->_right;
		}
		return cur->_value;
	}
protected:
	Node* _DestorySBT(Node *&root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root != NULL)
		{
			root->_left = _DestorySBT(root->_left);
			root->_right = _DestorySBT(root->_right);
			delete root;
			root = NULL;
		}
		return root;
	}
	void _Inorderprint(Node *root)
	{
		if (root == NULL)
			return;
		_Inorderprint(root->_left);
		cout << root->_key << " ";
		_Inorderprint(root->_right);
	}
	bool _InsertP(Node *&root, const K& key)
	{
		if (root == NULL)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key > key)
		{
			_InsertP(root->_left, key);
		}
		else if (root->_key < key)
		{
			_InsertP(root->_right, key);
		}
		else
		{
			return false;
		}
		return true;
	}
	bool _RemoveP(Node *&root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->_key < key)
		{
			_RemoveP(root->_right, key);
		}
		else if (root->_key > key)
		{
			_RemoveP(root->_left, key);
		}
		else
		{
			Node* del = root;


			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{

				Node* parent = root;
				Node *swapnode = root->_right;
				while (swapnode->_left)
				{
					parent = swapnode;
					swapnode = swapnode->_left;
				}
				root->_key = swapnode->_key;
				root->_value = swapnode->_value;
				if (parent->_right == swapnode)
					parent->_right = swapnode->_right;
				else
					parent->_left = swapnode->_right;
				del = swapnode;
			}
			delete del;
			return true;
		}
		return false;
	}
	bool _FindP(Node * root, const K& key)
	{
		if (root == NULL)
		{
			return false;
		}
		if (key < root->_key)
		{
			return _FindP(root->_left, key);
		}
		else if (key>root->_key)
		{
			return _FindP(root->_right, key);
		}
		else
		{
			return true;
		}
		return false;
	}

	//BST转换排序的双向链表
	Node* _CovertSortList(Node *root,Node *&prenode)
	{
		if (root==NULL)
			return NULL;
		Node* cur = root;

		//先要找到BST的最小键值点，也就是最左节点。寻找最左节点的时候切记prenode是不能变的。
		if (root->_left)
			_CovertSortList(cur->_left, prenode);
		//找到以后，这个最左节点的左边链上prenode
		cur->_left = prenode;
		//这个时候考虑给前一个节点的右链上节点
		if (prenode != NULL)
			prenode->_right = cur;
		//改变前一个节点为当前节点
		prenode = cur;
		//考虑右子树的问题
		if (cur->_right)
			_CovertSortList(cur->_right,prenode);
		return root;
	}
protected:
	Node * _root;
};
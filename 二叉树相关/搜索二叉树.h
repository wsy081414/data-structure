#pragma once

#include<iostream>
#include<cstdlib>
#include<cassert>
using namespace std;

template<typename K,typename V>
struct SearchBinaryTreeNode
{
	typedef SearchBinaryTreeNode<K,V> Node;
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

template<typename K,typename V>
class SearchBinaryTree
{
protected:
	typedef SearchBinaryTreeNode<K,V>  Node;

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
		_root=_DestorySBT(_root);

	}
	bool InsertP(const K& key)
	{
		return _InsertP(_root, key);
	}
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
	bool RemoveP(const K& key)
	{
		return _RemoveP(_root, key);
	}
	bool Remove(const K& key)
	{
		Node *cur = _root;
		Node *parent = NULL;
		Node *del = NULL;
		while (cur&&cur->_key!=key)
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
		else if (cur->_right==NULL)
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
	void Inorderprint()
	{
		_Inorderprint(_root);
		cout << endl;
	}
	bool Empty()
	{
		return _root == NULL;
	}
	V& Find(const K &key)
	{
		if (_root == NULL)
			return false;
		Node *cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				cur = cur->_left;
			}
			else if (key < cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur->_value;
			}
		}
		return false;
	}
	bool FindP(const K &key)
	{
		return _FindP(_root, key);
	}
	const K& Top()
	{
		return _root->_key;
	}
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
	Node* _DestorySBT(Node *root)
	{
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
		cout << root->_key <<" ";
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
			_RemoveP(root->_right,key);
		}
		else if (root->_key > key)
		{
			_RemoveP(root->_left,key);
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
	bool _FindP(Node * root,const K& key)
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
protected:
	Node * _root;
};
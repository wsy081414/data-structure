#pragma once

#include<iostream>
#include<cstdlib>
#include<cassert>
using namespace std;

template<typename K>
struct SearchBinaryTreeNode
{
	typedef SearchBinaryTreeNode<K> Node;
	SearchBinaryTreeNode(const K& key)
		: left(NULL)
		, right(NULL)
		, value(key)

	{
		
	}

	K value;
	Node* left;
	Node* right;

};

template<typename K>
class SearchBinaryTree
{
protected:
	typedef SearchBinaryTreeNode<K> Node;

public:
	SearchBinaryTree(const K* arr, size_t size)
	{
		assert(arr);
		for (size_t i = 0; i < size; i++)
		{
			Insert(arr[i]);
		}
	
	}
	~SearchBinaryTree()
	{
		_root=_DestorySBT(_root);

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
			if (cur->value < key)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (cur->value>key)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				return false;
			}
		}
		Node *tmp = new Node(key);
		if (key > parent->value)
		{

			parent->right = tmp;
		}
		else
		{
			parent->left = tmp;
		}
		return true;
	}
	bool Remove(const K& key)
	{
		Node *cur = _root;
		Node *parent = NULL;
		Node *del = NULL;
		while (cur&&cur->value!=key)
		{
			if (cur->value < key)
			{
				
				parent = cur;
				cur = cur->right;
			}
			else if (cur->value>key)
			{
				parent = cur;
				cur = cur->left;
			}
			else
			{
				break;
			}
		}
		if (cur == NULL)
		{
			return false;	
		}
		if (cur->left == NULL)
		{

			del = cur;
			if (parent == NULL)
			{
				_root = cur->right;
			}
			else
			{

				if (parent->left == cur)
				{
					parent->left = cur->right;
				}
				else
				{
					parent->right = cur->right;
				}
			}
		}
		else if (cur->right==NULL)
		{
			del = cur;
			if (parent == NULL)
			{
				cur = cur->left;
			}
			else
			{
				if (parent->left == cur)
				{
					parent->left = cur->left;
				}
				else
				{
					parent->right = cur->right;
				}
			}
		
		}
		else
		{
			Node *swapnode = cur->right;
			while (swapnode->left)
			{
				parent = swapnode;
				swapnode = swapnode->left;
			}
			del = swapnode;
			swap(swapnode->value, cur->value);
			if (parent->left = swapnode)
				parent->left = swapnode->right;
			else
				parent->right = swapnode->right;
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
	bool Find(const K &key)
	{
		if (_root == NULL)
			return false;
		Node *cur = _root;
		while (cur)
		{
			if (key > cur->value)
			{
				cur = cur->left;
			}
			else if (key < cur->value)
			{
				cur = cur->right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	const K& Top()
	{
		return _root->value;
	}
	const K& Minvalue()
	{
		assert(_root);
		Node* cur = _root;
		while (cur->left)
		{
			cur = cur->left;
		}
		return cur->value;
	}
	const K& Maxvalue()
	{
		assert(_root);
		Node *cur = _root;
		while (cur->right)
		{
			cur = cur->right;
		}
		return cur->value;
	}
protected:
	Node* _DestorySBT(Node *root)
	{
		if (root != NULL)
		{
			root->left = _DestorySBT(root->left);
			root->right = _DestorySBT(root->right);
			delete root;
			root = NULL;
		}
		return root;
	}
	void _Inorderprint(Node *root)
	{
		if (root == NULL)
			return;
		_Inorderprint(root->left);
		cout << root->value << " ";
		_Inorderprint(root->right);
	}

protected:
	Node * _root;
};
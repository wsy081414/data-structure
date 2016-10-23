#pragma once

#include<iostream>
#include<cstdlib>
#include<cassert>

using namespace std;

template<typename K,typename V>
struct AVLBinaryTreeNode
{
	typedef AVLBinaryTreeNode<K, V> Node;
	AVLBinaryTreeNode(const K& key,const V& value)
		:_left(NULL)
		,_right(NULL)
		, _parent(NULL)
		,_key(key)
		, _pf(0)
		, _value(value)
	{}
	Node* _left;
	Node* _right;
	Node* _parent;

	int _pf;	//来保存左右子树的高度差,平衡因子。
	K _key;
	V _value;
};

template<typename K, typename V>
class AVLBinaryTree
{
public:
	typedef AVLBinaryTreeNode<K, V> Node;
public:
	//构造函数
	AVLBinaryTree()
		:_root(NULL)
	{
	}
	//析构函数
	~AVLBinaryTree()
	{
		_DestoryTree(_root);
	}
	//拷贝构造
	AVLBinaryTree(const AVLBinaryTree<K, V> & a)
	{
		_root = _Copy(_root);
	}
	//现代写法赋值
	AVLBinaryTree<T >operator =(const AVLBinaryTree<K,V>& d)
	{
		if (this != &d)
		{
			AVLBinaryTree<K，V> tmp(d);
			std::swap(tmp._root,_root);
		}
			return *this;
	}
	//插入节点
	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
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
				return false;
			}
		}
		cur = new Node(key, value);
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		while (parent)
		{
			if (parent->_left == cur)
			{
				parent->_pf--;
			}
			else
			{
				parent->_pf++;
			}
			if (parent->_pf == 0)
			{
				return true;
			}
			else if (parent->_pf == 1 || parent->_pf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_pf == 2||parent->_pf == -2)
			{
				if (parent->_pf == 2)
				{
					if (cur->_pf == 1)
					{
						_RotateL(parent);
						return true;
					}
					else
					{
 						_RotateR(cur);
						_RotateL(parent);

						parent->_pf = _Height(parent->_right) - _Height(parent->_left);

						return true;

					}
				}
				if (parent->_pf == -2)
				{
					if (cur->_pf == 1)
					{
						_RotateL(cur);
						_RotateR(parent);
						
						//旋转完以后必须进行重新对parent配置_pf
						parent->_pf = _Height(parent->_right) - _Height(parent->_left);

						return true;

					}
					else
					{
						_RotateR(parent);
						return true;

					}
				}
			}
		}
		return true;
	}
	//删除节点
	bool Remove(const K& key)
	{
		
	
	}
	//判断是否为AVL树
	bool IsAVLBinaryTree()
	{
		return _IsAVLBinaryTree(_root);

	}
	//中序遍历
	void Inorderprint()
	{
		_Inorderprint(_root); 
		cout << endl;
	}
	//得到高度
	size_t Height() const
	{
		_Height(_root);
	}



protected:
	//拷贝构造二叉树
	Node* _Copy(Node *root)
	{
		Node * NewNode = NULL;
		if (root != NULL)
		{
			NewNode = new Node(root->_value);
			NewNode->_left = _Copy(root->_left);
			NewNode->_right = _Copy(root->_right);
		}
		return NewNode;
	}
	size_t _Height(Node *root)
	{
		if (root == NULL)
			return 0;
		size_t lheight = _Height(root->_left) + 1;
		size_t rheight = _Height(root->_right) + 1;

		return lheight > rheight ? lheight : rheight;
	}

	bool _IsAVLBinaryTree(Node *root)
	{
		if (root==NULL)
		{
			return true;
		}
		int lheight = _Height(root->_left);
		int rheight = _Height(root->_right);

		int heightorder = abs(rheight - lheight);
		/*if (abs(root->_pf) != rheight - lheight)
		{
			cout << "NO AVLBinaryTree" << endl;
			return false;
		}*/


		return ((heightorder<2)
			&&(_IsAVLBinaryTree(root->_left))
			&& (_IsAVLBinaryTree(root->_right)));
	}
	//中序递归遍历
	void _Inorderprint(Node *root)
	{
		if (root == NULL)
		{
			return;
		}
		_Inorderprint(root->_left);
		cout << root->_key<<" ";
		cout << root->_pf << endl;
		_Inorderprint(root->_right);
	}
	//销毁AVL树
	Node* _DestoryTree(Node*& root)
	{
		if (root != NULL)
		{
			root->_left = _DestoryTree(root->_left);
			root->_right = _DestoryTree(root->_right);
			delete root;
			root = NULL;
		}
		return	root;
	}
	//左旋
	void _RotateL(Node *parent)
	{
		assert(parent);
		Node* SubR = parent->_right;
		Node* SubRL = SubR->_left;
		parent->_right = SubRL;
		if (SubRL)
			SubRL->_parent = parent;
		Node * ppNode = parent->_parent;
		SubR->_left = parent;
		parent->_parent = SubR;
		if (ppNode==NULL)
		{
			_root = SubR;
			SubR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = SubR;
			}
			else
			{
				ppNode->_right = SubR;
			}
			SubR->_parent = ppNode;
		}
		parent->_pf = SubR->_pf = 0;
	}
	//右旋
	void _RotateR(Node *parent)
	{
		Node *SubL = parent->_left;
		Node *SubLR = SubL->_right;
		parent->_left = SubLR;
		if (SubLR)
		{
			SubLR->_parent = parent;
		}
		Node* ppNode = parent->_parent;
		SubL->_right = parent;
		parent->_parent = SubL;
		if (ppNode == NULL)
		{
			_root = SubL;
			SubL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = SubL;
			}
			else
			{
				ppNode->_right = SubL;
			}
			SubL->_parent = ppNode;
		}
		parent->_pf = SubL->_pf = 0;
	}
protected:
	Node* _root;
};
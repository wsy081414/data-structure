#pragma once
#include<iostream>
#include<cstdlib>
#include<cassert>

enum color
{
	BLACK,
	RED
};


using namespace std;

 template<typename K, typename V>
struct RBNode
{
	typedef RBNode<K, V> Node;

	RBNode(const K& key,const V& value)
		: _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _color(RED)
	{}

	Node* _left;
	Node* _right;
	Node* _parent;

	K _key;
	V _value;

	int _color;
};


template<typename K,typename V>
class RBTree
{
	typedef RBNode<K, V> Node;
public:
	//构造函数
	RBTree()
		:_root(NULL)
	{}
	//析构函数
	~RBTree()
	{
		_root = _DestroyRBTree(_root);
	}
	//拷贝构造函数
	RBTree(const RBTree<K, V>& b)
	{
		_root = _Copy(_root);
	}
	//赋值语句
	RBTree<K, V>& operator =(const RBTree<K, V> & r)
	{
		if (*this != &r)
		{
			Node *tmp=_Copy(r->_root);
			_root = _DestroyRBTree(_root);
			_root = tmp;
		}
		return *this;
	}
	//插入函数
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return true;
		}
		Node *cur = _root;
		Node *parent = NULL;
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
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;
		//判断如果parent是根节点，那么直接结束
		
		while (parent!=NULL)
		{
			//父亲是黑色，cur是红色，符合红黑树，退出
			if (parent->_color == BLACK)
			{
				break;
			}
			//父亲和cue都是红色的情况
			Node* pparent = parent->_parent;
			Node* uncle = NULL;
			//考虑parent 是左边的情况
			if (pparent->_left == parent)
			{
				uncle = pparent->_right;
				//考虑叔叔是红色的情况
				if (uncle&&uncle->_color == RED)
				{
					pparent->_color = RED;
					uncle->_color = parent->_color = BLACK;
					cur = pparent;
					parent = cur->_parent;
					continue;
				}
				//考虑叔叔不存在或者叔叔是黑色的情况
				else if (uncle == NULL || uncle->_color == BLACK)
				{
					if (cur == parent->_left)
					{
						_BRRolateR(pparent);
						pparent->_color = RED;
						parent->_color = BLACK;
					}
					else
					{
						_BRRolateL(parent);
						std::swap(parent, cur);
						_BRRolateR(pparent);
						pparent->_color = RED;
						parent->_color = BLACK;
					}
					break;
				}
			}
			//考虑parent是右边的情况
			else
			{
				uncle = pparent->_left;
				if (uncle&&uncle->_color == RED)
				{
					pparent->_color = RED;
					uncle->_color = parent->_color = BLACK;
					cur = pparent;
					parent = cur->_parent;
				}
				else if (uncle == NULL || uncle->_color == BLACK)
				{
					if (cur == parent->_right)
					{
						_BRRolateL(pparent);
						pparent->_color = RED;
						parent->_color = BLACK;
					}
					else
					{
						//_BRRolateRL(pparent);
						_BRRolateR(parent);
						std::swap(parent, cur);
						_BRRolateL(pparent);
						pparent->_color = RED;
						parent->_color = BLACK;
					}

				}
				break;
			}
		}
		
	
		_root->_color = BLACK;
		return true;
	}
	//删除函数
	bool Remove(const K& key)
	{
		if (_root == NULL)
		{
			return false;
		}
		Node *del = NULL;
		Node *cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key<cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				
				break;
			}
		}
		Node *parent = cur->_parent;
		//此时就是没有找到需要删除的节点
		if (cur == NULL)
		{
			return false;
		}
		if (cur->_left != NULL&&cur->_right != NULL)
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
			{
				parent->_left = swapnode->_right;
			}
			else
			{
				parent->_right = swapnode->_left;
			}

		}





		delete del;
		return true;
	}
	//判断是否是红黑树
	bool IsRBTree()
	{
		//当为空树的时候，是红黑树
		if (_root == NULL)
		{
			return true;
		}
		//当根节点是红色的时候，直接可以确定不是红黑树
		if (_root->_color == RED)
		{
			return false;
		}
		//给出一个参考的路径的黑色节点的数目
		size_t count = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
				count++;
			cur = cur->_left;
		}
		//k用来记录一条路径的黑色节点的数目，和count来进行比较
		size_t k = 0;
		return _IsRBTree(_root, count, k);
	}
	//查找函数
	bool Find(const K& key)
	{
		if (_root == NULL)
			return false;
		Node *cur = _root;
		while(cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	//中序递归遍历
	void InorderPrint()
	{
		_InorderPrint(_root);
		cout << endl;
	}

protected:
	//判断是否是红黑树
	//这里的k需要进行传值，因为这里你需要对每一条路径进行对比，所以在这里，你要找寻完一条路径以后，向上回溯，
	bool _IsRBTree(Node* root, const size_t& count, size_t k)
	{
		if (root == NULL)
		{
			return true;
		}
		//当出现两个连续的红色节点的时候，可以确定不是红黑树
		if (root->_parent&&root->_color == root->_parent->_color == RED)
		{
			return false;
		}
		//如果是黑色节点，k进行++
		if (root->_color == BLACK)
		{
			k++;
		}
		//如果是叶子节点的话，进行判断k和count是否相等
		if (root->_left == NULL&&root->_right == NULL)
		{
			//k和count不相等，那么就不是红黑树。
			if (k == count)
				return true;
			else
				return false;
		}
		//对节点的左右进行检查
		return _IsRBTree(root->_left, count, k) && _IsRBTree(root->_right, count, k);
	}
	//中序遍历打印
	void _InorderPrint(Node* root)
	{
		if (root == NULL)
			return;
		_InorderPrint(root->_left);
		cout << root->_key << " ";
		_InorderPrint(root->_right);
	}
	
	//拷贝函数
	Node* _Copy(Node* root)
	{
		Node* newnode;
		if (root != NULL)
		{
			newnode = new Node(root->_key, root->_value);
			newnode->_left = _Copy(root->_left);
			newnode->_right = _Copy(root->_right);
		}
		return newnode;
	}
	//销毁树函数
	Node* _DestroyRBTree(Node *root)
	{
		if (root != NULL)
		{
			root->_left = _DestroyRBTree(root->_left);
			root->_right = _DestroyRBTree(root->_right);
			delete root;
			root = NULL;
		}
		return root;
	}
	//右旋
	void _BRRolateR(Node *parent)
	{
		assert(parent);
		Node* SubL = parent->_left;
		Node* SubLR = SubL->_right;

		parent->_left = SubLR;
		if (SubLR)
			SubLR->_parent = parent;
		Node *pparent = parent->_parent;
		SubL->_right = parent;
		parent->_parent = SubL;
		if (pparent == NULL)
		{
			_root = SubL;
			SubL->_parent = NULL;
		}
		else
		{
			if (pparent->_left == parent)
			{
				pparent->_left = SubL;
				SubL->_parent = pparent;
			}
			else
			{
				pparent->_right = SubL;
				SubL->_parent = pparent;
			}

		}
	}
	//左旋
	void _BRRolateL(Node *parent)
	{
		assert(parent);
		Node *SubR = parent->_right;
		Node *SubRL = SubR->_left;
		parent->_right = SubRL;
		if (SubRL)
			SubRL->_parent = parent;
		Node *ppnode = parent->_parent;
		SubR->_left = parent;
		parent->_parent = SubR;
		if (ppnode == NULL)
		{
			_root = SubR;
			SubR->_parent = NULL;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = SubR;
			}
			else
			{
				ppnode->_right = SubR;
			}
			SubR->_parent = ppnode;
		}
	}
	//左右双旋
	void _BRRolateLR(Node *parent)
	{
		_BRRolateL(parent->_left);
		std::swap(parent->_left, parent->_left->_left);
		_BRRolateR(parent);
	}
	//右左双旋
	void _BRRolateRL(Node *parent)
	{
		_BRRolateR(parent->_right);
		std::swap(parent->_right, parent->_right->_right);
		_BRRolateL(parent);
	}
	
protected:
	Node* _root;
};
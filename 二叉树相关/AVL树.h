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
		, _bf(0)
		, _value(value)
	{}
	Node* _left;
	Node* _right;
	Node* _parent;

	int _bf;	//来保存左右子树的高度差,平衡因子。
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
	AVLBinaryTree<K,V>operator =(const AVLBinaryTree<K,V>& d)
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
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				return true;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2||parent->_bf == -2)
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						_RotateL(parent);
						return true;
					}
					else
					{
						_RotateRL(parent);

						//parent->_bf = _Height(parent->_right) - _Height(parent->_left);
						//_RotateRL(parent);
						return true;

					}
				}
				if (parent->_bf == -2)
				{
					if (cur->_bf == 1)
					{
						_RotateLR(parent);

						
						//
						////旋转完以后必须进行重新对parent配置_bf
						//parent->_bf = _Height(parent->_right) - _Height(parent->_left);
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
		if (_root == NULL)
			return false;
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key>cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}

		//没找到进行处理
		if (cur == NULL)
			return false;
		
		//对左树为空处理
		Node* del = NULL;
		if (cur->_left == NULL)
		{
			del = cur;	
			//考虑下删除根节点的情况
			if (parent == NULL)
			{
				_root = cur->_right;
				if (cur->_right)
					cur->_right->_parent = _root;
			}
			else
			{
				//考虑删除节点是parent节点的那个孩子
				if (parent->_left == cur)
				{
					
					parent->_left = cur->_right;
				}
				else
				{

					parent->_right = cur->_right;
					
				}
				if (cur->_right)
					cur->_right->_parent = parent;
			}
			
			cur = cur->_right;
			if (cur)
			parent = cur->_parent;
		}
		else if (cur->_right == NULL)
		{
			del = cur;
			if (parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				}
				else
				{
					parent->_right = cur->_left;
				}
				if (cur->_left)
					cur->_left->_parent = parent;
			}
			
			cur = cur->_left;
			parent = cur->_parent;
		}
		else
		{
			//进行交换法删除
			del = cur;
			parent = cur;
			//首先设置为parent的右节点
			Node *swapnode = cur->_right;
			//找到最左节点
			while (swapnode->_left)
			{
				parent = swapnode;
				swapnode = swapnode->_left;
			}
			//交换key和value
			del->_key = swapnode->_key;
			del->_value = swapnode->_value;
			del = swapnode;
			//查看swapnode与parent的关系
			if (parent->_left == del)
				parent->_left = del->_right;
			else
				parent->_right = del->_right;	
			cur = del->_right;
		}
		
		while (parent)
		{
			//左树的节点删除++，右树的节点删除进行--。
			if (parent->_right == cur)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			//原来的平衡因子为0，左子树或者右子树被缩短后，平衡因子变为
			//直接结束过程，不需要平衡化。
			if (parent->_bf == 1 || parent->_bf == -1)
			{
				break;
			}
			//这时候可以确定的是所删除的节点是位于较低的子树的，需要进行平衡化
			if (parent->_bf != 0)
			{
			
				//找到较高的子树
				if (cur == NULL)
				{
					if (parent->_left==NULL)
						cur = parent->_right;
					else
						cur = parent->_left;
				}
				else
				{
					if (parent->_left == cur)
						cur = parent->_right;
					else
						cur = parent->_left;
				}
				//此时cur所指向的就是较高的子树的第一个节点

				//如果cur的平衡因子为0，执行一个单旋转处理。
				if (cur->_bf == 0)
				{
					if (parent->_bf < 0)
					{
						_RotateR(parent);
						parent->_bf = -1;
						parent->_parent->_bf = 1;
						
					}
					else
					{
						_RotateL(parent);
						parent->_bf = 1;
						parent->_parent->_bf = -1;
					}
				}
				//如果parent的bf和cue的bf正负相等，这个时候我们应该采取执行一个单旋转来恢复平衡。
				//如果不相等，那么我们进行双旋转就好了。
				else if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						_RotateL(parent);
					}
					else
					{
						_RotateRL(parent);

					}
				}
				else if (parent->_bf==-2)
				{
					if (cur->_bf == 1)
					{
						_RotateLR(parent);
					}
					else
					{
						_RotateR(parent);
					}
				}
			}
			//此时说明所删除的节点是位于较高子树的，需要向上检查父节点的平衡因子
			
				cur = parent;
				parent = parent->_parent;
			

		}
		delete del;
		return true;
	}
	//查找节点
	bool Find(const K& key)
	{
		if (_root == NULL)
			return false;
		Node *cur = _root;
		while (cur)
		{
			if (key < cur->_key)
			{
				cur = cur->_left;
			}
			else if (key>cur->_key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	//判断是否为AVL树
	//bool IsAVLBinaryTree()
	//{
	//	return _IsAVLBinaryTree(_root);
	//}
	bool IsAVLBinaryTree()
	{
		int depth = 0;
		return _IsAVLBinaryTree(_root, depth);

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
	//树的高度
	size_t _Height(Node *root)
	{
		if (root == NULL)
			return 0;
		size_t lheight = _Height(root->_left) + 1;
		size_t rheight = _Height(root->_right) + 1;

		return lheight > rheight ? lheight : rheight;
	}
	//判断二叉树是否为平衡二叉树
	/*bool _IsAVLBinaryTree(Node *root)
	{
		if (root==NULL)
		{
			return true;
		}

		int heightorder = abs((int)(_Height(root->_right) - _Height(root->_left)));

		return ((heightorder<2)
			&&(_IsAVLBinaryTree(root->_left))
			&& (_IsAVLBinaryTree(root->_right)));
	}*/
	//判断二叉树是否为平衡二叉树，优化版本
	bool _IsAVLBinaryTree(Node *root,  int & depth)
	{
		//如果为空，往父节点返
		if (root == NULL)
		{
			depth = 0;
			return true;
		}
		//记录左节点和右节点深度
		int left = 0;
		int right = 0;
		//采取传引用的方式，下层递归进行对深度修改以后会影响上一层
		if (_IsAVLBinaryTree(root->_left, left) && _IsAVLBinaryTree(root->_right, right))
		{
			//计算平衡因子
			int pf = right - left;
			//判断平衡因子是否合法
			if (pfIsInvaild(pf))
			{
	//合法就让自身加上子树的深度，然后因为是传引用，所以当递归回到上一层的时候，上层中的right和left就是左右子树的深度
				depth = 1 + (right > left ? right : left);
				return true;
			}
		}
		return false;
	}
	//判断平衡因子是否合法
	bool pfIsInvaild(const int& pf)
	{
		return abs(pf) < 2;
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
		cout << root->_bf << endl;
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
		Node * ppNode = parent->_parent;		    //记录根的父亲	
		SubR->_left = parent;		
		parent->_parent = SubR;
		if (ppNode==NULL)						//考虑根节点的情况
		{
			_root = SubR;
			SubR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)		   //判断旋转以后的根应该链接在根的父亲的那边
			{
				ppNode->_left = SubR;
			}
			else
			{
				ppNode->_right = SubR;
			}
			SubR->_parent = ppNode;
		}
	
		parent->_bf = SubR->_bf = 0;			  //重置平衡因子

	}
	//先左旋后右旋
	//void _RotateLR(Node *parent)
	//{
	//	Node* SubL = parent->_left;
	//	Node* SubLR = SubL->_right;
	//	SubL->_right = SubLR->_left;
	//	if (SubLR->_left)
	//		SubL->_right->_parent = SubL;
	//	SubLR->_left = SubL;
	//	SubL->_parent = SubLR;
	//	parent->_left = SubLR;
	//	SubLR->_parent = parent;
	//	//判断SubLR的左子树是否存在，如果存在，在调整过程当中，需要进行bf的调整
	//	//SubLR的left最后是变成了SubL的left，所以当pf为1时，这个时候调整过去，SubL的pf就是左树比右树大。
	//	if (SubLR->_bf <= 0)
	//		SubL->_bf = 0;
	//	else
	//		SubL->_bf = -1;
	//	parent->_left = SubLR->_right;
	//	if (SubLR->_right)
	//	{
	//		parent->_left->_parent = parent;
	//	}
	//	Node *ppnode = parent->_parent;
	//	SubLR->_right = parent;
	//	parent->_parent = SubLR;
	//	if (ppnode == NULL)
	//	{
	//		_root = SubLR;
	//		SubLR->_parent = NULL;
	//	}
	//	else
	//	{
	//		if (parent == ppnode->_left)
	//		{
	//			ppnode->_left = SubLR;
	//		}
	//		else
	//		{
	//			ppnode->_right = SubLR;
	//		}
	//		SubLR->_parent = ppnode;
	//	}
	//	//同上，这是看SubLR的right是否存在。
	//	if (SubLR->_bf == -1)
	//		parent->_bf = 1;
	//	else
	//		parent->_bf = 0;
	//	SubLR->_bf = 0;
	//}
	void _RotateLR(Node *parent)
	{
		//进行双旋转的时候通过在这里的旋转以后的根节点的bf进行判断
		Node* SubL = parent->_left;
		Node* SubLR = SubL->_right;
		//计算旋转以后的根节点的bf
		int bf = SubLR->_bf;

		_RotateL(SubL);
		_RotateR(parent);
		//如果bf为0，代表插入点就是这个节点，这个时候所有旋转后的bf皆为0
		if (bf == 0)
		{
			SubL->_bf = parent->_bf = 0;
		}
		//当bf为1时，这个时候相当于是在给bf的右树插入，所以插入以后subL旋转后的右边高度为h，

		else if (bf == 1)
		{
			SubL->_bf = -1;
			parent->_bf = 0;
		}
		//当bf为-1，这时相当于是给bf的左树进行插入
		else
		{
			SubL->_bf = 0;
			parent->_bf = 1;
		}
		SubLR->_bf = 0;
	}
	//先右旋后左旋
	//void _RotateRL(Node *parent)
	//{
	//	Node *SubR = parent->_right;
	//	Node *SubRL = SubR->_left;
	//	//右旋
	//	SubR->_left = SubRL->_right;
	//	if (SubRL->_right)
	//		SubR->_right->_parent = SubR;
	//	parent->_right = SubRL;
	//	SubRL->_parent = parent;
	//	SubRL->_right = SubR;
	//	SubR->_parent = SubRL;
	//	if (SubRL->_bf >= 0)
	//		SubR->_bf = 0;
	//	else
	//		SubR->_bf = 1;
	//	//左旋
	//	parent->_right = SubRL->_left;
	//	if (SubRL->_left)
	//		parent->_right->_parent = parent;
	//	Node *ppNode = parent->_parent;
	//	SubRL->_left = parent;
	//	parent->_parent = SubRL;
	//	if (ppNode == NULL)
	//	{
	//		_root = SubRL;
	//		SubRL->_parent = NULL;
	//	}
	//	else
	//	{
	//		if (ppNode->_left == parent)
	//		{
	//			ppNode->_left = SubRL;
	//		}
	//		else
	//		{
	//			ppNode->_right = SubRL;
	//		}
	//		SubRL->_parent = ppNode;
	//	}
	//	if (SubRL->_bf == 1)
	//		parent->_bf = -1;
	//	else
	//		parent->_bf = 0;
	//}
	//右旋
	void _RotateRL(Node *parent)
	{
		//双旋转根据插入不同进行调整pf，
		Node* SubR = parent->_right;
		Node* SubRL = SubR->_left;
		//根据最后的根节点的bf进行调整
		int bf = SubRL->_bf;

		_RotateR(SubR);
		_RotateL(parent);
		//当bf为0，代表插入的就是他这个节点，所有的bf都变作0
		if (bf == 0)
		{
			parent->_bf = SubR->_bf = 0;
		}
		//当bf为-1，代表这时是在这个根的左树插入，h-1高度变作h。
		else if (bf == -1)
		{
			parent->_bf = 0;
			SubR->_bf = 1;
		}
		//当bf为1时，代表是在这个旋转后的根的右树插入，h-1的高度作h。
		else
		{
			parent->_bf = -1;
			SubR->_bf = 0;
		}
		SubRL->_bf = 0;

	
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
		Node* ppNode = parent->_parent;			//记录根节点父亲
		SubL->_right = parent;
		parent->_parent = SubL;
		if (ppNode == NULL)						//考虑根节点情况
		{
			_root = SubL;
			SubL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)			//判断旋转以后的根应该链接在根的父亲的那边
			{
				ppNode->_left = SubL;
			}
			else
			{
				ppNode->_right = SubL;
			}
			SubL->_parent = ppNode;
		}
	

		parent->_bf = SubL->_bf = 0;			   //重置平衡因子
	}
protected:
	Node* _root;
};
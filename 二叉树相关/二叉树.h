#define _CRT_SECURE_NO_WARNINGS 1


#include<iostream>
#include<cstdlib>
#include<cassert>
#include<queue>
#include<stack>

using namespace std;

template<typename  T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& d)
	:_value(d)
	, _left(NULL)
	, _right(NULL)
	{

	}
	T _value;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;
};

template<typename T>
class BinaryTree
{
public:
	typedef BinaryTreeNode<T> Node;

public:
	//默认构造函数
	BinaryTree() = default;
	//构造函数
	BinaryTree(T *a, size_t size, const T& invaild)
	{
		size_t index = 0;
		_root = _CreateBinaryTree(a, size, index, invaild);
	}
	//重建二叉树
	void RebuildBinaryTree(T *preorder, T*infixorder,size_t lengh)
	{
		_root = _RebuildBinaryTree(preorder, infixorder, lengh);
	}
	//析构函数
	~BinaryTree()
	{
		_root = _Destory(_root);
	}
	//拷贝构造
	BinaryTree(const BinaryTree<T> &b)
	{
		_root = _Copy(b._root);
	}

	//传统写法赋值
	BinaryTree<T > operator=(const BinaryTree<T> &b)
	{
		if (this != &b)
		{
			Node* tmp = _Copy(b._root);
			_root = _Destory(_root);
			_root = tmp;
		}
		return *this;
	}

	//现代写法赋值
	/*BinaryTree<T >operator =(const BinaryTree<T>& d)
	{
	if (this != &d)
	{
	BinaryTree<T > tmp(d);
	std::swap(tmp._root,_root);
	}
	return *this;
	}*/
	

	//查找两个节点最近的公共节点

	//思路是：
	Node* FindTwoCommonNode(Node* p1, Node*p2)
	{
		return _FindTwoCommonNode(_root, p1, p2);
	}
	//前序遍历
	void PreorderPrint()
	{
		_PreOrder(_root);
		cout << endl;

	}
	//中序遍历
	void InfixPrint()
	{
		_InfixOrder(_root);
		cout << endl;

	}
	//后序遍历
	void PostPrint()
	{
		_PostOrder(_root);
		cout << endl;

	}
	//查找
	Node* Find(const T& x)
	{
		return _Find(_root, x);

	}
	//前序非递归遍历
	void PreorderPrintNorR()
	{
		if (_root == NULL)	//判断是否为空树
		{
			return;
		}
		else
		{
			stack<Node *> s;
			Node *cur = _root;
			while ((cur != NULL) || (!s.empty()))
			{
				while (cur)
				{
					cout << cur->_value << " ";
					s.push(cur);
					cur = cur->_left;
				}

				Node *top = s.top();
				s.pop();
				cur = top->_right;
			}
		}
		cout << endl;
	}
	//中序非递归遍历
	void InfixPrintNorR()
	{
		if (_root == NULL)
		{
			return;
		}
		else
		{
			stack<Node *> s;
			Node *cur = _root;
			while ((cur != NULL) || (!s.empty()))
			{
				while (cur)
				{
					s.push(cur);
					cur = cur->_left;
				}
				Node *top = s.top();
				s.pop();
				cout << top->_value << " ";

				cur = top->_right;
			}
		}
		cout << endl;
	}
	//后序非递归遍历
	void PostPrintNorR()
	{
		if (_root == NULL)
		{
			return;
		}
		else
		{
			stack<Node * > s;
			Node *cur = _root;
			Node *prev = NULL;	//记录上一个访问到的节点。
			while (cur || !s.empty())
			{
				while (cur)		//while循环到最左边的节点
				{
					s.push(cur);
					cur = cur->_left;
				}
				Node *top = s.top();	//取得最左边的节点
				if (top->_right == NULL || prev == top->_right)//如果这个top的右边是访问过的或者是NULL，就不进行访问；
				{
					cout << top->_value << " ";
					s.pop();
					prev = top;
				}
				else
				{
					cur = top->_right;	//访问右边
				}
			}
		}
		cout << endl;
	}
	//层序遍历
	void LevelPrint()
	{
		_LevelPrint(_root);
		cout << endl;
	}
	//输出节点个数
	size_t Size()
	{

		return _size(_root);
	}
	//输出深度
	size_t Depth()
	{
		return _Depth(_root);
	}
	//输出k层的节点个数
	size_t GetKLevel(const size_t & k)
	{
		return _GetKLevel(_root, k);
	}
	//输出叶子节点的个数
	size_t Leafsize()
	{
		return _Leafsize(_root);
	}
	//判断二叉是是否是完全二叉树

	bool IsComplateBinaryTree()
	{
		queue<Node *> q;
		Node* cur = _root;
		q.push(cur);
		//首先进行层序，把每一层的节点都入队，这个时候不存在的节点就按照NULL入队
		while (（cur=q.pop()）！=NULL)
		{

			q.push(cur->_left);
			q.push(cur->_right);
		}
		//这个时候如果是完全二叉树，那么队中就全部为空，如果为非完全二叉树的话，那么队中就会存在不为空的元素。
		while (!q.empty())
		{
			cur = q.pop();
			if (cur != NULL)
			{
				return false;
			}
		}
		return true;
	}

	//求得二叉树中最远两个节点之间的距离
	size_t MaxDistance()
	{
		size_t maxdistance = 0;
		return  _MaxDistance(_root,maxdistance);

	}


protected:
	//深度
	size_t _Depth(Node *root)
	{
		if (root == NULL)
		{
			return 0;
		}
		size_t ldepth = _Depth(root->_left);
		size_t rdepth = _Depth(root->_right);
		return (((ldepth > rdepth) ? ldepth : rdepth) + 1);
	}
	//叶子节点的个数
	size_t _Leafsize(Node * root)
	{
		if (root != NULL)
		{
			return 0;
		}
		if (root->_left == NULL&&root->_right == NULL)
		{
			return 1;
		}

		return _Leafsize(root->_left) + _Leafsize(root->_right);
	}
	//查找结点
	Node* _Find(Node *root, const T& x)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_value == x)
		{
			return root;
		}
		Node *cur = _Find(root->_left, x);
		if (cur == NULL)
		{
			cur = _Find(root->_right, x);
		}
		return cur;

	}
	
	//使用队列//层序遍历
	void _LevelPrint(Node* root)
	{
		queue q;			//实现的队列
		q.push(root);
		while (!q.empty())
		{
			Node* tmp = q.front();
			cout << tmp->_value << " ";
			q.pop();
			if (tmp->_left != NULL)
			{
				q.push(tmp->_left);
			}
			if (tmp->_right != NULL)
			{
				q.push(tmp->_right);
			}

		}
	}
	//得到K层的节点个数
	size_t _GetKLevel(Node* root, size_t k)
	{
		if (root == NULL || k == 0)		//考虑为空
		{
			return 0;
		}
		else if (k == 1)				//考虑第一层只有一个节点，不需要进行递归
		{
			return 1;
		}
		else
		{
			//递归，
			return _GetKLevel(root->_left, k - 1) + _GetKLevel(root->_right, k - 1);
		}

	}
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
	//计算节点的总个数
	size_t _size(Node *root)
	{
		if (root == NULL)
			return 0;
		return _size(root->_left) + _size(root->_right) + 1;
	}
	//创建二叉树
	Node * _CreateBinaryTree(T *a, size_t size, size_t &index, const T& invaild)
	{
		Node *newnode = NULL;
		if (index < size&&a[index] != invaild)
		{
			newnode = new Node(a[index]);
			newnode->_left = _CreateBinaryTree(a, size, ++index, invaild);
			newnode->_right = _CreateBinaryTree(a, size, ++index, invaild);
		}

		return newnode;
	}
	//销毁整颗二叉树
	Node* _Destory(Node *root)
	{
		if (root != NULL)
		{
			root->_left = _Destory(root->_left);
			root->_right = _Destory(root->_right);
			delete root;
			root = NULL;
		}
		return root;
	}
	//前序遍历
	void _PreOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_value << " ";
			_PreOrder(root->_left);
			_PreOrder(root->_right);
		}
	}
	//中序遍历
	void _InfixOrder(Node* root)
	{
		if (root != NULL)
		{
			_InfixOrder(root->_left);
			cout << root->_value << " ";
			_InfixOrder(root->_right);
		}

	}
	//后序遍历
	void _PostOrder(Node* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_value << " ";
		}
	}

	//查找最近的两个公共节点
	Node* _FindTwoCommonNode(Node* root, Node* p1, Node *p2)
	{
		if (root == NULL)
		{
			return NULL;
		}
		//判断是否找到这个节点
		if (root == p1 || root == p2)
		{
			return root;
		}
		//递归右树和左树
		Node* left = _FindTwoCommonNode(root->_left, p1, p2);
		Node* right = _FindTwoCommonNode(root->_right, p1, p2);
		//判断是否在左子树和右子树中找到
		if (left&&right)
			//左右子树都存在就返回root，此时的root就是公共节点
			return root;	
		//否则返回找到的一个
		return left ? left : right;
	
	}

	//求二叉树中最远的两个节点的距离
	size_t _MaxDistance(Node *root,size_t &depth)
	{
		if (root == NULL)
		{
			depth = 0;
			return 0;
		}
		size_t leftdepth = 0;
		size_t rightdepth = 0;
		size_t maxleft = _MaxDistance(root->_left, leftdepth);
		size_t maxright = _MaxDistance(root->_right, rightdepth);
		depth = max(leftdepth, rightdepth) + 1;
		return max(maxleft, max(maxright, leftdepth + rightdepth));

	}


	//重建二叉树

	//通过递归进行控制重建二叉树
	Node* _RebuildBinaryTree(T* preorder, T* infixorder, int lengh)
	{
		if (lengh == 0 || preorder == NULL || infixorder == NULL)
		{
			return NULL;
		}
		//首先给根
		T tmp = preorder[0];
		//创建节点
		Node *root = new Node(tmp);
		//找到对应的在中序序列当中的所对应的根节点位置
		int i = 0;
		for (i = 0; i < lengh&&infixorder[i] != tmp; i++)
			;
		//得到左子树的长度
		int leftlen = i;
		//得到右子树的长度
		int rightlen = lengh - i - 1;
		if (leftlen>0)
			//递归问题
			root->_left = _RebuildBinaryTree(preorder+1, infixorder, leftlen);
		if (rightlen > 0)
			//递归问题
			root->_right = _RebuildBinaryTree(preorder+leftlen + 1, infixorder+leftlen + 1, rightlen);

		return root;
	}

protected:
	Node* _root;

};
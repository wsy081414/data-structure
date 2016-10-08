#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>

using namespace std;


enum PointerTag
{
	LINK,//表示节点
	THREAD//表示线索


};
//线索二叉树
template<typename T>
struct BinaryTreeNode_Thd
{
	//构造函数
	BinaryTreeNode_Thd()
	: _left(NULL)
	, _right(NULL)
	, _leftTag(LINK)
	, _rightTag(LINK)
	{}
	
	BinaryTreeNode_Thd(const T& d)
	:_data(d)
	, _left(NULL)
	, _right(NULL)
	, _leftTag(LINK)
	, _rightTag(LINK)
	{}
	T _data;
	BinaryTreeNode_Thd *_left;
	BinaryTreeNode_Thd *_right;

	PointerTag _leftTag;
	PointerTag _rightTag;
};


template<typename T>
class BinaryTreeThread
{
public:
	typedef BinaryTreeNode_Thd<T> Node;
public:
	//构造线索化二叉树
	BinaryTreeThread(T* a, size_t size, const T& invaild)
	{
		size_t index = 0;
		_root = _CreateBinaryTreeThread(a, size, index, invaild);
	}
	//中序线索化。
	void InOrderThread()
	{
		Node *prev=NULL ;
		if (_root != NULL)
		{
			_InOrderThread(_root, prev);
			prev->_rightTag = LINK;
			prev->_right = NULL;
		}
	}
	//前序线索化。
	void PreOrderThread()
	{
		Node *prev = NULL;
		if (_root != NULL)
		{
			_PreOrderThread(_root, prev);
			prev->_right = NULL;
		
		}
	}
	//前序线索化的前序遍历
	void PreOrderTh()
	{
		_PreOrdert(_root);
	}
	//后序线索化。
	void PostOrderThread()
	{
		Node *prev = NULL;
		if (_root != NULL)
		{
			_PostOrderThread(_root, prev);
			
		}
	
	}
	//中序线索化后的前序遍历
	void PreOrder()
	{
		_PreOrder(_root);
	}
	//中序线索化的后序遍历
	void PostOrder()
	{
		_PostOrder(_root);
	}
	//中序线索化以后的中序遍历
	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	//前序线索化的前序遍历
	void _PreOrdert(Node *_root)
	{
		Node *cur = _root;
		while (cur)
		{
			while (cur&&cur->_leftTag==LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
		
			cur = cur->_right;
			


		}
		cout << endl;
	
	}

	//中序线索化以后的中序遍历
	void _InOrder(Node *root)
	{
		if (root == NULL)
			return;
		Node* cur = root;
		while (cur)
		{
			while (cur->_leftTag == LINK )
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data<<" ";
			}
			cur = cur->_right;
		}
	}
	//中线线索化的前序遍历
	void _PreOrder(Node * root)
	{
		if (root == NULL)
		{
			return;
		}
		Node* cur = root;
		while (cur)
		{
			cout << cur->_data << " ";

			if (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			else if (cur->_rightTag == LINK)
			{
				cur = cur->_right;
			}
			else
			{
				while (cur&&cur->_rightTag == THREAD)
				{
					cur = cur->_right;
				}
				if (cur)
					cur = cur->_right;
			}

		}
		cout << endl;
	}
	//后序线索化
	void _PostOrderThread(Node *cur, Node* &prev)
	{
		if (cur == NULL)
		{
			return;
		}
		_PostOrderThread(cur->_left, prev);
		_PostOrderThread(cur->_right, prev);
		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if (prev&&prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

		
	}
	//前序线索化
	void _PreOrderThread(Node *cur,Node *&prev)
	{
		if (cur == NULL)
		{
			return;
		}
		if (cur->_left == NULL)
		{
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if (prev&&prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
		if (cur->_leftTag == LINK)
			_PreOrderThread(cur->_left, prev);
		if(cur->_rightTag == LINK)
			_PreOrderThread(cur->_right, prev);

	}
	//中序线索化
	void _InOrderThread(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;
		_InOrderThread(cur->_left, prev);
		if (cur->_left == NULL)//线索化前驱  
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev!=NULL&&prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		_InOrderThread(cur->_right, prev);
	}
	//创建线索化二叉树
	Node* _CreateBinaryTreeThread(T* a, size_t size, size_t &index, const T& invaild)
	{
		
		Node *newnode = NULL;
		if (index < size&&a[index] != invaild)
		{
			newnode = new Node(a[index]);
			newnode->_left = _CreateBinaryTreeThread(a, size, ++index, invaild);
			newnode->_right = _CreateBinaryTreeThread(a, size, ++index, invaild);
		}

		return newnode;
	
	}
protected:
	Node* _root;
};
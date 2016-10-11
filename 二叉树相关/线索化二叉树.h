#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>

using namespace std;


enum PointerTag
{
	LINK,//��ʾ�ڵ�
	THREAD//��ʾ����


};
//����������
template<typename T>
struct BinaryTreeNode_Thd
{
	//���캯��
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
	//����������������
	BinaryTreeThread(T* a, size_t size, const T& invaild)
	{
		size_t index = 0;
		_root = _CreateBinaryTreeThread(a, size, index, invaild);
	}
	//������������
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
	//ǰ����������
	void PreOrderThread()
	{
		Node *prev = NULL;
		if (_root != NULL)
		{
			_PreOrderThread(_root, prev);
			prev->_right = NULL;
		
		}
	}
	//ǰ����������ǰ�����
	void PreOrderTh()
	{
		_PreOrdert(_root);
	}
	//������������
	void PostOrderThread()
	{
		Node *prev = NULL;
		if (_root != NULL)
		{
			_PostOrderThread(_root, prev);
			
		}
	
	}
	//�������������ǰ�����
	void PreOrder()
	{
		_PreOrder(_root);
	}
	//�����������ĺ������
	void PostOrder()
	{
		_PostOrder(_root);
	}
	//�����������Ժ���������
	void InOrder()
	{
		_InOrder(_root);
	}
protected:
	//ǰ����������ǰ�����
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

	//�����������Ժ���������
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
	//������������ǰ�����
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
	//����������
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
	//ǰ��������
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
	//����������
	void _InOrderThread(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;
		_InOrderThread(cur->_left, prev);
		if (cur->_left == NULL)//������ǰ��  
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
	//����������������
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
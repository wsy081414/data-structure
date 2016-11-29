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
	//Ĭ�Ϲ��캯��
	BinaryTree() = default;
	//���캯��
	BinaryTree(T *a, size_t size, const T& invaild)
	{
		size_t index = 0;
		_root = _CreateBinaryTree(a, size, index, invaild);
	}
	//�ؽ�������
	void RebuildBinaryTree(T *preorder, T*infixorder,size_t lengh)
	{
		_root = _RebuildBinaryTree(preorder, infixorder, lengh);
	}
	//��������
	~BinaryTree()
	{
		_root = _Destory(_root);
	}
	//��������
	BinaryTree(const BinaryTree<T> &b)
	{
		_root = _Copy(b._root);
	}

	//��ͳд����ֵ
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

	//�ִ�д����ֵ
	/*BinaryTree<T >operator =(const BinaryTree<T>& d)
	{
	if (this != &d)
	{
	BinaryTree<T > tmp(d);
	std::swap(tmp._root,_root);
	}
	return *this;
	}*/
	

	//���������ڵ�����Ĺ����ڵ�

	//˼·�ǣ�
	Node* FindTwoCommonNode(Node* p1, Node*p2)
	{
		return _FindTwoCommonNode(_root, p1, p2);
	}
	//ǰ�����
	void PreorderPrint()
	{
		_PreOrder(_root);
		cout << endl;

	}
	//�������
	void InfixPrint()
	{
		_InfixOrder(_root);
		cout << endl;

	}
	//�������
	void PostPrint()
	{
		_PostOrder(_root);
		cout << endl;

	}
	//����
	Node* Find(const T& x)
	{
		return _Find(_root, x);

	}
	//ǰ��ǵݹ����
	void PreorderPrintNorR()
	{
		if (_root == NULL)	//�ж��Ƿ�Ϊ����
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
	//����ǵݹ����
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
	//����ǵݹ����
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
			Node *prev = NULL;	//��¼��һ�����ʵ��Ľڵ㡣
			while (cur || !s.empty())
			{
				while (cur)		//whileѭ��������ߵĽڵ�
				{
					s.push(cur);
					cur = cur->_left;
				}
				Node *top = s.top();	//ȡ������ߵĽڵ�
				if (top->_right == NULL || prev == top->_right)//������top���ұ��Ƿ��ʹ��Ļ�����NULL���Ͳ����з��ʣ�
				{
					cout << top->_value << " ";
					s.pop();
					prev = top;
				}
				else
				{
					cur = top->_right;	//�����ұ�
				}
			}
		}
		cout << endl;
	}
	//�������
	void LevelPrint()
	{
		_LevelPrint(_root);
		cout << endl;
	}
	//����ڵ����
	size_t Size()
	{

		return _size(_root);
	}
	//������
	size_t Depth()
	{
		return _Depth(_root);
	}
	//���k��Ľڵ����
	size_t GetKLevel(const size_t & k)
	{
		return _GetKLevel(_root, k);
	}
	//���Ҷ�ӽڵ�ĸ���
	size_t Leafsize()
	{
		return _Leafsize(_root);
	}
	//�ж϶������Ƿ�����ȫ������

	bool IsComplateBinaryTree()
	{
		queue<Node *> q;
		Node* cur = _root;
		q.push(cur);
		//���Ƚ��в��򣬰�ÿһ��Ľڵ㶼��ӣ����ʱ�򲻴��ڵĽڵ�Ͱ���NULL���
		while (��cur=q.pop()����=NULL)
		{

			q.push(cur->_left);
			q.push(cur->_right);
		}
		//���ʱ���������ȫ����������ô���о�ȫ��Ϊ�գ����Ϊ����ȫ�������Ļ�����ô���оͻ���ڲ�Ϊ�յ�Ԫ�ء�
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

	//��ö���������Զ�����ڵ�֮��ľ���
	size_t MaxDistance()
	{
		size_t maxdistance = 0;
		return  _MaxDistance(_root,maxdistance);

	}


protected:
	//���
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
	//Ҷ�ӽڵ�ĸ���
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
	//���ҽ��
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
	
	//ʹ�ö���//�������
	void _LevelPrint(Node* root)
	{
		queue q;			//ʵ�ֵĶ���
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
	//�õ�K��Ľڵ����
	size_t _GetKLevel(Node* root, size_t k)
	{
		if (root == NULL || k == 0)		//����Ϊ��
		{
			return 0;
		}
		else if (k == 1)				//���ǵ�һ��ֻ��һ���ڵ㣬����Ҫ���еݹ�
		{
			return 1;
		}
		else
		{
			//�ݹ飬
			return _GetKLevel(root->_left, k - 1) + _GetKLevel(root->_right, k - 1);
		}

	}
	//�������������
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
	//����ڵ���ܸ���
	size_t _size(Node *root)
	{
		if (root == NULL)
			return 0;
		return _size(root->_left) + _size(root->_right) + 1;
	}
	//����������
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
	//�������Ŷ�����
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
	//ǰ�����
	void _PreOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_value << " ";
			_PreOrder(root->_left);
			_PreOrder(root->_right);
		}
	}
	//�������
	void _InfixOrder(Node* root)
	{
		if (root != NULL)
		{
			_InfixOrder(root->_left);
			cout << root->_value << " ";
			_InfixOrder(root->_right);
		}

	}
	//�������
	void _PostOrder(Node* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_value << " ";
		}
	}

	//������������������ڵ�
	Node* _FindTwoCommonNode(Node* root, Node* p1, Node *p2)
	{
		if (root == NULL)
		{
			return NULL;
		}
		//�ж��Ƿ��ҵ�����ڵ�
		if (root == p1 || root == p2)
		{
			return root;
		}
		//�ݹ�����������
		Node* left = _FindTwoCommonNode(root->_left, p1, p2);
		Node* right = _FindTwoCommonNode(root->_right, p1, p2);
		//�ж��Ƿ��������������������ҵ�
		if (left&&right)
			//�������������ھͷ���root����ʱ��root���ǹ����ڵ�
			return root;	
		//���򷵻��ҵ���һ��
		return left ? left : right;
	
	}

	//�����������Զ�������ڵ�ľ���
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


	//�ؽ�������

	//ͨ���ݹ���п����ؽ�������
	Node* _RebuildBinaryTree(T* preorder, T* infixorder, int lengh)
	{
		if (lengh == 0 || preorder == NULL || infixorder == NULL)
		{
			return NULL;
		}
		//���ȸ���
		T tmp = preorder[0];
		//�����ڵ�
		Node *root = new Node(tmp);
		//�ҵ���Ӧ�����������е��е�����Ӧ�ĸ��ڵ�λ��
		int i = 0;
		for (i = 0; i < lengh&&infixorder[i] != tmp; i++)
			;
		//�õ��������ĳ���
		int leftlen = i;
		//�õ��������ĳ���
		int rightlen = lengh - i - 1;
		if (leftlen>0)
			//�ݹ�����
			root->_left = _RebuildBinaryTree(preorder+1, infixorder, leftlen);
		if (rightlen > 0)
			//�ݹ�����
			root->_right = _RebuildBinaryTree(preorder+leftlen + 1, infixorder+leftlen + 1, rightlen);

		return root;
	}

protected:
	Node* _root;

};
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
	BinaryTree() = default;
	BinaryTree(T *a, size_t size,const T& invaild)
	{
		size_t index = 0;
		_root = _CreateBinaryTree(a,  size,  index,  invaild);
	}
	~BinaryTree()
	{
		_root=_Destory(_root);
	}
	BinaryTree(const BinaryTree<T> &b)
	{
		_root = _Copy(b._root);
	}
	
	////传统写法
	BinaryTree<T > operator=(const BinaryTree<T> &b)
	{
		if (this != &b)
		{
			Node* tmp = _Copy(b._root);
			_root=_Destory(_root);
			_root = tmp;
		}
		return *this;
	}

	//现代写法
	/*BinaryTree<T >operator =(const BinaryTree<T>& d)
	{
		if (this != &d)
		{
			BinaryTree<T > tmp(d);
			std::swap(tmp._root,_root);
		}
		return *this;

	}*/

	void PreorderPrint()
	{
		_PreOrder(_root);
		cout << endl;

	}
	void InfixPrint()
	{
		_InfixOrder(_root);
		cout << endl;

	}
	void PostPrint()
	{
		_PostOrder(_root);
		cout << endl;

	}

	//前序非递归遍历
	void PreorderPrintNorR()
	{
		if (_root == NULL)
		{
			return;
		}
		else
		{
			stack<Node *> s;
			Node *cur = _root;
			while ((cur != NULL)||(!s.empty()))
			{
				if (cur != NULL)
				{
					cout << cur->_value<<" ";
					s.push(cur);
					cur = cur->_left;
				}
				else
				{
					cur = s.top();
					s.pop();
					cur = cur->_right;
				}
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
				if (cur)
				{
					s.push(cur);
					cout << cur->_value << " ";
					cur = cur->_left;
				}
				else
				{
					s.pop();
					cur = cur->_right;
				}

			}
		}
		cout << endl;
	}
	void PostPrintNorR()
	{
		if (_root == NULL)
		{
			return;
		}
		else
		{
			stack<Node *> s;
			stack<int > ints;//1代表向左，2代表向右
			int v=0;
			Node *cur = _root;
			while ((!ints.empty())|| (!s.empty()))
			{
				if (cur != NULL&& v == 0)
				{
					s.push(cur);
					ints.push(1);
					cur = cur->_left;
				}
				else
				{
					cur = s.top();
					v = ints.top();
					s.pop();
					ints.pop();
					if (v == 1)
					{
						s.push(cur);
						ints.push(2);
						cur = cur->_right;
						v = 0;
					}
					else
					{
						cout << cur->_value << " ";
					}
				}

			}
		}
	
	}

	void LevelPrint()
	{
		_LevelPrint(_root);
		cout << endl;
	}
	size_t Size()
	{
		
		return _size(_root);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	size_t GetKLevel(const size_t & k)
	{
		return _GetKLevel(k);
	}
	size_t Leafsize()
	{
		return _Leafsize(_root);
	}
protected:
	size_t _Depth(Node *root)
	{
		size_t maxdepth = 0;
		if (root != NULL)
		{
			size_t depth = 1;
			if (root->_left != NULL)
			{
				depth += _Depth(root->_left) ;
			}
			if (depth > maxdepth)
			{
				maxdepth = depth;
			}
			if (root->_right != NULL)
			{
				depth = _Depth(root->_right) + 1;
			}
			if (depth > maxdepth)
			{
				maxdepth = depth;
			}
		}
		return maxdepth;
	}
	size_t _Leafsize(Node * root)
	{
		int size = 0;
		if (root != NULL)
		{
			if (root->_left == NULL&&root->_right == NULL)
			{
				size += 1;
			}
				size += _Leafsize(root->_left);
				size += _Leafsize(root->_right);
			
			
		}
		return size;
	}

	void _LevelPrint(Node* root)
	{
		queue<Node *> q;
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

	size_t _GetKLevel(size_t k)
	{
		
	}

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

	size_t _size(Node *root)
	{
		size_t size = 0;
		if (root != NULL)
		{
			size += 1;
			size += _size(root->_left);
			size += _size(root->_right);
		}
		return size;
	}

	Node * _CreateBinaryTree(T *a, size_t size, size_t &index,const T& invaild)
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

	Node* _Destory(Node *root)
	{
		if (root != NULL)
		{
			root->_left=_Destory(root->_left);
			root->_right=_Destory(root->_right);
			delete root;
			root = NULL;
		}
		return root;
	}

	void _PreOrder(Node* root)
	{
		if (root != NULL)
		{
			cout << root->_value << " ";
			_PreOrder(root->_left);
			_PreOrder(root->_right);
		}
	}
	void _InfixOrder(Node* root)
	{
		if (root != NULL)
		{
			_InfixOrder(root->_left);
			cout << root->_value << " ";
			_InfixOrder(root->_right);
		}

	}
	void _PostOrder(Node* root)
	{
		if (root != NULL)
		{
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_value << " ";
		}
	}

protected:
	Node* _root;

};

void test1()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int *ar = NULL;
	int arr[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTree<int > b(a, 10, (int )'#');
	BinaryTree<int > bt(arr, 15, (int )'#');
	BinaryTree<int > c(ar, 0, (int)'#');
	BinaryTree<int > d;
	

	//cout<<d.Depth()<<endl;
	b.PreorderPrintNorR();
	b.InfixPrint();
	b.PostPrintNorR();
	//bt.LevelPrint();
	//cout<<bt.Leafsize() << endl;
	//cout << bt.Depth() << endl;
	//cout << b.Leafsize() << endl;
	//
	//cout <<c.Leafsize()<< endl;

	//cout << b.Size() << endl;
	//b.Preorderprint();
	//b.InfixPrint();
	//b.PostPrint();
	//cout << endl;
	//cout << d.Size() << endl;
	//d.Preorderprint();
	//d.InfixPrint();
	//d.PostPrint();
	//cout<<c.size() << endl;
	//c.InfixPrint();
	//c.PostPrint();
	//c.Preorderprint();

	/*cout << d.size() << endl;
	d.InfixPrint();
	d.PostPrint();
	d.Preorderprint();*/
	/*cout<<bt.size() << endl;
	bt.Preorderprint();
	bt.InfixPrint();
	bt.PostPrint();*/
	cout << endl;

	/*b.Preorderprint();
	b.InfixPrint();
	b.PostPrint();
	cout << b.size() << endl;*/

}

int main()
{
	test1();
	system("pause");
	return 0;
}
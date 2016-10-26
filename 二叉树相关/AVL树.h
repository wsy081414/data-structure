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

	int _bf;	//���������������ĸ߶Ȳ�,ƽ�����ӡ�
	K _key;
	V _value;
};

template<typename K, typename V>
class AVLBinaryTree
{
public:
	typedef AVLBinaryTreeNode<K, V> Node;
public:
	//���캯��
	AVLBinaryTree()
		:_root(NULL)
	{
	}
	//��������
	~AVLBinaryTree()
	{
		_DestoryTree(_root);
	}
	//��������
	AVLBinaryTree(const AVLBinaryTree<K, V> & a)
	{
		_root = _Copy(_root);
	}
	//�ִ�д����ֵ
	AVLBinaryTree<K,V>operator =(const AVLBinaryTree<K,V>& d)
	{
		if (this != &d)
		{
			AVLBinaryTree<K��V> tmp(d);
			std::swap(tmp._root,_root);
		}
			return *this;
	}
	//����ڵ�
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
						//˫��ת���ݲ��벻ͬ���е���pf��
						Node* SubR = parent->_right;
						Node* SubRL = SubR->_left;

						int bf = SubRL->_bf;

 						_RotateR(cur);
						_RotateL(parent);

						if (bf == 0)
						{
							parent->_bf = SubR->_bf = 0; 
						}
						else if (bf == -1)
						{
							parent->_bf = 0;
							SubR->_bf = 1;
						}
						else
						{
							parent->_bf = -1;
							SubR->_bf = 0;
						}
						SubRL->_bf = 0;


						//parent->_bf = _Height(parent->_right) - _Height(parent->_left);
						//_RotateRL(parent);
						return true;

					}
				}
				if (parent->_bf == -2)
				{
					if (cur->_bf == 1)
					{
						//_RotateLR(parent);

						Node* SubL = parent->_left;
						Node* SubLR = SubL->_right;

						int bf = SubLR->_bf;

						_RotateL(cur);
						_RotateR(parent);

						if (bf == 0)
						{
							SubL->_bf = parent->_bf = 0;
						}
						else if (bf == 1)
						{
							SubL->_bf = -1;
							parent->_bf = 0;
						}
						else
						{
							SubL->_bf = 0;
							parent->_bf = 1;
						}
						SubLR->_bf = 0;
						//
						////��ת���Ժ����������¶�parent����_bf
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
	//ɾ���ڵ�
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

		//û�ҵ����д���
		if (cur == NULL)
			return false;
		
		//������Ϊ�մ���
		Node* del = NULL;
		Node* delson = NULL;
		if (cur->_left == NULL)
		{
			del = cur;
			delson = cur->_right;
			//������ɾ�����ڵ�����
			if (parent == NULL)
			{
				_root = cur->_right;
				
			}
			else
			{
				//����ɾ���ڵ���parent�ڵ���Ǹ�����
				if (parent->_left == cur)
				{
					
					parent->_left = cur->_right;
					if (parent->_left)
						parent->_left->_parent = parent;
				}
				else
				{

					parent->_right = cur->_right;
					if (parent->_right)
						parent->_right->_parent = parent;
				}
			}
		}
		else if (cur->_right == NULL)
		{
			del = cur;
			delson = cur->_left;
			if (parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
					cur->_left->_parent = parent;
				}
				else
				{
					parent->_right = cur->_left;
					cur->_left->_parent = parent;
				}
			}
		}
		else
		{
			//���н�����ɾ��
			
			//��������Ϊparent���ҽڵ�
			Node *swapnode = cur->_right;
			//�ҵ�����ڵ�
			while (swapnode->_left)
			{
				parent = swapnode;
				swapnode = swapnode->_left;
			}
			
			del = swapnode;
			//����key��value
			cur->_key = swapnode->_key;
			cur->_value = swapnode->_value;
			//�鿴swapnode��parent�Ĺ�ϵ
			delson = swapnode->_right;
			if (parent->_left == swapnode)
				parent->_left = swapnode->_right;
			else
				parent->_right = swapnode->_right;
		}
		
		while (parent)
		{
			if (parent->_right == delson)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent != NULL)
			{
				cur = parent;
				parent = parent->_parent;
			}
		}
		delete del;
		return true;
	}
	//���ҽڵ�
	V& Find(const K& key)
	{
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
				return cur->_value;
			}
		}
		return;
	}
	//�ж��Ƿ�ΪAVL��
	//bool IsAVLBinaryTree()
	//{
	//	return _IsAVLBinaryTree(_root);
	//}
	bool IsAVLBinaryTree()
	{
		int depth = 0;
		return _IsAVLBinaryTree(_root, depth);

	}
	//�������
	void Inorderprint()
	{
		_Inorderprint(_root); 
		cout << endl;
	}
	//�õ��߶�
	size_t Height() const
	{
		_Height(_root);
	}
protected:
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
	//���ĸ߶�
	size_t _Height(Node *root)
	{
		if (root == NULL)
			return 0;
		size_t lheight = _Height(root->_left) + 1;
		size_t rheight = _Height(root->_right) + 1;

		return lheight > rheight ? lheight : rheight;
	}
	//�ж϶������Ƿ�Ϊƽ�������
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
	//�ж϶������Ƿ�Ϊƽ����������Ż��汾
	bool _IsAVLBinaryTree(Node *root,  int & depth)
	{
		//���Ϊ�գ������ڵ㷵
		if (root == NULL)
		{
			depth = 0;
			return true;
		}
		//��¼��ڵ���ҽڵ����
		int left = 0;
		int right = 0;
		//��ȡ�����õķ�ʽ���²�ݹ���ж�����޸��Ժ��Ӱ����һ��
		if (_IsAVLBinaryTree(root->_left, left) && _IsAVLBinaryTree(root->_right, right))
		{
			//����ƽ������
			int pf = right - left;
			//�ж�ƽ�������Ƿ�Ϸ�
			if (pfIsInvaild(pf))
			{
	//�Ϸ��������������������ȣ�Ȼ����Ϊ�Ǵ����ã����Ե��ݹ�ص���һ���ʱ���ϲ��е�right��left�����������������
				depth = 1 + (right > left ? right : left);
				return true;
			}
		}
		return false;
	}
	//�ж�ƽ�������Ƿ�Ϸ�
	bool pfIsInvaild(const int& pf)
	{
		return abs(pf) < 2;
	}
	//����ݹ����
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
	//����AVL��
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
	//����
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
	
		parent->_bf = SubR->_bf = 0;

	}
	//������������
	void _RotateLR(Node *parent)
	{
		Node* SubL = parent->_left;
		Node* SubLR = SubL->_right;
		SubL->_right = SubLR->_left;
		if (SubLR->_left)
			SubL->_right->_parent = SubL;
		SubLR->_left = SubL;
		SubL->_parent = SubLR;
		parent->_left = SubLR;
		SubLR->_parent = parent;
		//�ж�SubLR���������Ƿ���ڣ�������ڣ��ڵ������̵��У���Ҫ����bf�ĵ���
		//SubLR��left����Ǳ����SubL��left�����Ե�pfΪ1ʱ�����ʱ�������ȥ��SubL��pf����������������
		if (SubLR->_bf <= 0)
			SubL->_bf = 0;
		else
			SubL->_bf = -1;

		parent->_left = SubLR->_right;
		if (SubLR->_right)
		{
			parent->_left->_parent = parent;
		}
		Node *ppnode = parent->_parent;
		SubLR->_right = parent;
		parent->_parent = SubLR;

		if (ppnode == NULL)
		{
			_root = SubLR;
			SubLR->_parent = NULL;
		}
		else
		{
			if (parent == ppnode->_left)
			{
				ppnode->_left = SubLR;
			}
			else
			{
				ppnode->_right = SubLR;
			}
			SubLR->_parent = ppnode;
		}

		//ͬ�ϣ����ǿ�SubLR��right�Ƿ���ڡ�
		if (SubLR->_bf == -1)
			parent->_bf = 1;
		else
			parent->_bf = 0;

		SubLR->_bf = 0;
	}
	//������������
	void _RotateRL(Node *parent)
	{
		Node *SubR = parent->_right;
		Node *SubRL = SubR->_left;
		//����
		SubR->_left = SubRL->_right;
		if (SubRL->_right)
			SubR->_right->_parent = SubR;
		parent->_right = SubRL;
		SubRL->_parent = parent;
		SubRL->_right = SubR;
		SubR->_parent = SubRL;
		if (SubRL->_bf >= 0)
			SubR->_bf = 0;
		else
			SubR->_bf = 1;
		//����
		parent->_right = SubRL->_left;
		if (SubRL->_left)
			parent->_right->_parent = parent;
		Node *ppNode = parent->_parent;
		SubRL->_left = parent;
		parent->_parent = SubRL;
		if (ppNode == NULL)
		{
			_root = SubRL;
			SubRL->_parent = NULL;

		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = SubRL;
			}
			else
			{
				ppNode->_right = SubRL;
			}
			SubRL->_parent = ppNode;
		}
		if (SubRL->_bf == 1)
			parent->_bf = -1;
		else
			parent->_bf = 0;
	}
	//����
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
	

		parent->_bf = SubL->_bf = 0;
	}
protected:
	Node* _root;
};
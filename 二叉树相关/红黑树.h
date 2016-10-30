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
	//���캯��
	RBTree()
		:_root(NULL)
	{}
	//��������
	~RBTree()
	{
		_root = _DestroyRBTree(_root);
	}
	//�������캯��
	RBTree(const RBTree<K, V>& b)
	{
		_root = _Copy(_root);
	}
	//��ֵ���
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
	//���뺯��
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
		//�ж����parent�Ǹ��ڵ㣬��ôֱ�ӽ���
		
		while (parent!=NULL)
		{
			//�����Ǻ�ɫ��cur�Ǻ�ɫ�����Ϻ�������˳�
			if (parent->_color == BLACK)
			{
				break;
			}
			//���׺�cue���Ǻ�ɫ�����
			Node* pparent = parent->_parent;
			Node* uncle = NULL;
			//����parent ����ߵ����
			if (pparent->_left == parent)
			{
				uncle = pparent->_right;
				//���������Ǻ�ɫ�����
				if (uncle&&uncle->_color == RED)
				{
					pparent->_color = RED;
					uncle->_color = parent->_color = BLACK;
					cur = pparent;
					parent = cur->_parent;
					continue;
				}
				//�������岻���ڻ��������Ǻ�ɫ�����
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
			//����parent���ұߵ����
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
	//ɾ������
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
		//��ʱ����û���ҵ���Ҫɾ���Ľڵ�
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
	//�ж��Ƿ��Ǻ����
	bool IsRBTree()
	{
		//��Ϊ������ʱ���Ǻ����
		if (_root == NULL)
		{
			return true;
		}
		//�����ڵ��Ǻ�ɫ��ʱ��ֱ�ӿ���ȷ�����Ǻ����
		if (_root->_color == RED)
		{
			return false;
		}
		//����һ���ο���·���ĺ�ɫ�ڵ����Ŀ
		size_t count = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
				count++;
			cur = cur->_left;
		}
		//k������¼һ��·���ĺ�ɫ�ڵ����Ŀ����count�����бȽ�
		size_t k = 0;
		return _IsRBTree(_root, count, k);
	}
	//���Һ���
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
	//����ݹ����
	void InorderPrint()
	{
		_InorderPrint(_root);
		cout << endl;
	}

protected:
	//�ж��Ƿ��Ǻ����
	//�����k��Ҫ���д�ֵ����Ϊ��������Ҫ��ÿһ��·�����жԱȣ������������Ҫ��Ѱ��һ��·���Ժ����ϻ��ݣ�
	bool _IsRBTree(Node* root, const size_t& count, size_t k)
	{
		if (root == NULL)
		{
			return true;
		}
		//���������������ĺ�ɫ�ڵ��ʱ�򣬿���ȷ�����Ǻ����
		if (root->_parent&&root->_color == root->_parent->_color == RED)
		{
			return false;
		}
		//����Ǻ�ɫ�ڵ㣬k����++
		if (root->_color == BLACK)
		{
			k++;
		}
		//�����Ҷ�ӽڵ�Ļ��������ж�k��count�Ƿ����
		if (root->_left == NULL&&root->_right == NULL)
		{
			//k��count����ȣ���ô�Ͳ��Ǻ������
			if (k == count)
				return true;
			else
				return false;
		}
		//�Խڵ�����ҽ��м��
		return _IsRBTree(root->_left, count, k) && _IsRBTree(root->_right, count, k);
	}
	//���������ӡ
	void _InorderPrint(Node* root)
	{
		if (root == NULL)
			return;
		_InorderPrint(root->_left);
		cout << root->_key << " ";
		_InorderPrint(root->_right);
	}
	
	//��������
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
	//����������
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
	//����
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
	//����
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
	//����˫��
	void _BRRolateLR(Node *parent)
	{
		_BRRolateL(parent->_left);
		std::swap(parent->_left, parent->_left->_left);
		_BRRolateR(parent);
	}
	//����˫��
	void _BRRolateRL(Node *parent)
	{
		_BRRolateR(parent->_right);
		std::swap(parent->_right, parent->_right->_right);
		_BRRolateL(parent);
	}
	
protected:
	Node* _root;
};
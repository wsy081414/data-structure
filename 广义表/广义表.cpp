#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>
#include<cassert>
using namespace std;

enum type
{
	HEAD,
	VALUE,
	SUB
};


struct GeneralizedNode
{
	GeneralizedNode(const type & type,const char &value=0)
	:_type(type)
	,_next(NULL)
	, _sublink(NULL)
	
	{
		_value=value;
	}
	type _type;
	GeneralizedNode *_next;
	union
	{
		char _value;
		GeneralizedNode *_sublink;
	};
};

class Generalized
{
public:
	Generalized()
		:_head(NULL)
	{}
	Generalized(const char *str)
		:_head(NULL)
	{
		_head = _Createlist(str);
	}
	Generalized(const Generalized& g)
	{
		_head=_Copyconstruction(g._head);
	
	}
	//传统写法
	Generalized& operator =(const Generalized &d)
	{
		if (this != &d)
		{
			GeneralizedNode* tmp = _Copyconstruction(d._head);
			_Destroy(_head);
			_head = tmp;
		}
			return *this;
	}
	

	//现代写法
	/*Generalized& operator =(const Generalized &d)
	{
		if (this != &d)
		{
			Generalized tmp(d);
			swap(_head, tmp._head);
		}
		return *this;
	}*/

	~Generalized()
	{
		if (_head)
		{
			_Release(_head);
		}
	}
	void print()
	{
		if (_head)
		{
			_print(_head);
		}
		cout << endl;

	}
	size_t size()
	{
		if (_head)
		{
			return _size(_head);
		}
		else
		{
			return 0;
		}
	}

	size_t Depth()
	{
		if (_head)
		{
			return _Depth(_head);
		}
		else
		{
			return 0;
		}
	}

protected:
	// GeneralizedNode* _assignment(GeneralizedNode *head)
	// {
		// assert(head);
		// GeneralizedNode *newlist = new GeneralizedNode(HEAD);
		// GeneralizedNode *cur = head->_next;
		// GeneralizedNode *newcur = newlist;
		// while (cur)
		// {
			// if (cur->_type == SUB)
			// {
				// GeneralizedNode *subnode = new GeneralizedNode(SUB);
				// subnode->_sublink = _assignment(cur->_sublink);
				// newcur->_next = subnode;
				// newcur = subnode;
				// cur = cur->_next;
			
			// }
			// else
			// {
				// GeneralizedNode *newnode = new GeneralizedNode(cur->_type, cur->_value);
				// newcur->_next = newnode;
				// newcur = newnode;
				// cur = cur->_next;
			// }

		// }
	
		// return newlist;
	// }


	GeneralizedNode* _Copyconstruction(GeneralizedNode *head)
	{
		assert(head);
		GeneralizedNode *newlist = new GeneralizedNode(HEAD);
		GeneralizedNode *cur = head->_next;
		GeneralizedNode *newcur = newlist;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				GeneralizedNode* newnode = new GeneralizedNode(cur->_type);
				
				newnode->_sublink = _Copyconstruction(cur->_sublink);
				newcur->_next = newnode;
				newcur = newnode;
				cur = cur->_next;
			}
			else
			{
				GeneralizedNode* newnode = new GeneralizedNode(cur->_type, cur->_value);
				newcur->_next = newnode;
				newcur = newcur->_next;
				cur = cur->_next;
			}
		}

		return newlist;
	}
	void _Release(GeneralizedNode *head)
	{
		assert(head);
		GeneralizedNode* cur = head;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				_Release(cur->_sublink);
			}
			GeneralizedNode *del = cur;
			cur = cur->_next;
			delete del;
			del = NULL;
		}
	}
	size_t _Depth(GeneralizedNode *head)
	{
		assert(head);
		GeneralizedNode *cur = head;
		size_t maxdep = 1;
		while (cur)
		{
			if (cur->_type == SUB)
			{
				size_t dep = 1;
				dep+=_Depth(cur->_sublink);
				if (dep > maxdep)
				{
					maxdep = dep;
				}
			}
			
				cur = cur->_next;
		}
		return maxdep;
	}
	size_t _size(GeneralizedNode *head)
	{
		assert(head);
		GeneralizedNode* cur = head;
		size_t count = 0;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				count++;
				cur = cur->_next;
			}
			else if(cur->_type==SUB)
			{
				count += _size(cur->_sublink);
				cur = cur->_next;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return count;
	}
	void _print(GeneralizedNode *& head)
	{
		assert(head);
		GeneralizedNode *cur = head;
		cout << '(';
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				cout << cur->_value;
				if (cur->_next != NULL)
				{
					cout << ',';
				}
				cur = cur->_next;
			}
			else if (cur->_type == HEAD)
			{
				cur = cur->_next;
			}
			else if (cur->_type==SUB)
			{
				_print(cur->_sublink);
				if (cur->_next != NULL)
				{
					cout << ',';
				}
				cur = cur->_next;
			}
		}
		cout << ')';
	}
	GeneralizedNode* _Createlist(const char *&str)
	{
		assert(str);
		GeneralizedNode *head = new GeneralizedNode(HEAD);
		GeneralizedNode *cur = head;
		str++;
		while (*str)
		{
			if ((*str >= '0'&&*str <= '9') || (*str >= 'a'&&*str <= 'z') || (*str >= 'A'&&*str <= 'Z'))
			{
				GeneralizedNode* node = new GeneralizedNode(VALUE,*str);
				cur->_next = node;
				cur = cur->_next;
				str++;
			}
			else if (*str=='(')
			{
				GeneralizedNode* node = new GeneralizedNode(SUB);
				cur->_next = node;
				cur = cur->_next;
				cur->_sublink = _Createlist(str);
			}
			else if (*str == ')')
			{
				cur->_next = NULL;

				str++;
				return head;
			}
			else
			{
				str++;
			}

		}
		


		return head;
	}

protected:
	GeneralizedNode* _head;

};
void test1()
{
	Generalized g1("(a,b,(a,b),c,(d,((),()),a))");
	
	Generalized g3("(((), ()))");
	Generalized g2(g3);
	Generalized g4 = g1;
	cout<<g1.Depth() << endl;
	g4.print();
	/*cout<<g2.Depth() << endl;
	cout << g2.size() << endl;
	g2.print();
	g1 = g1;*/
//	Generalized g4(g3);
	//g3.print();
	/*g1.print();
	cout << g1.Depth() << endl;
	cout << g3.Depth() << endl;*/
	//g4.print();
	cout << g1.size() << endl;
	//cout << g3.size() << endl;
	//cout << g4.size() << endl;

}

int main()
{
	test1();
	system("pause");
	return 0;
}
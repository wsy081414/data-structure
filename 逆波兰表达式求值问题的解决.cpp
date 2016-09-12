#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>
#include<stack>
using namespace std;

enum Type
{
	OP_SYMBOL,
	OP_NUMBER,
	ADD,
	SUB,
	MUL,
	DIV,
};

struct Cell
{
	Type _type;
	int _value;
};

Cell RPNArray[] = 
{
	{ OP_NUMBER , 12 },
	{ OP_NUMBER , 4 },
	{ OP_NUMBER , 3 },
	{ OP_SYMBOL , ADD },
	{ OP_SYMBOL , MUL },
	{ OP_NUMBER, 5 },
	{ OP_SYMBOL, SUB }
};

int CalRPN(Cell a[],size_t size)
{
	stack<int> s;
	for (size_t i = 0; i < size; ++i)
	{
		if (a[i]._type == OP_NUMBER)
		{
			s.push(a[i]._value);
		}
		else
		{
			int left = s.top();
			s.pop();
			int right = s.top();
			s.pop();

			switch (a[i]._value )
			{
			case ADD:
				s.push(right + left );
				break;
			case SUB:
				s.push(right - left);

				break;
			case MUL:
				s.push(right * left);

				break;
			case DIV:
				s.push(right / left);

				break;
			default:

				break;
			} 
			
		}
	}
	return s.top(); 
}
void test1()
{
	cout << "¼ÆËã½á¹û£º" << CalRPN(RPNArray, sizeof(RPNArray) / sizeof(Cell));
}
int main()
{
	test1();
	system("pause");
	return 0;
}
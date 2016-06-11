#define _CRT_SECURE_NO_WARNINGS 1

#include"cal.h"



/*******************栈的基本操作********************************/
int init_stack(SqStack *s)
{
	s->top = -1;
	return 1;
}

int clear_stack(SqStack *s)
{
	s->top = -1;
	return 1;
}

int stack_empty(SqStack s)
{
	if (s.top == -1)
		return 1;
	else
		return 0;
}

int stack_length(SqStack *s)
{
	return s->top + 1;
}

int push(SqStack *s, SElemType e)
{
	if (s->top == MAXSIZE - 1)
		return 0;
	s->top++;
	s->data[s->top] = e;
	return 1;
}

int pop(SqStack *s, SElemType *e)
{
	if (s->top == -1)
		return 0;
	*e = s->data[s->top];
	s->top--;
	return 1;
}

/*******************中序表达式转换为后续表达式********************************/
int To_PostFix(char *infix, char *postfix)
{
	SqStack s;
	int e = 0;//进行出栈入栈操作
	int i = 0, j = 0;//分别进行循环数组的下标
	int flag = 0;//

	if (init_stack(&s) != 1)   //判断栈是否为空，
		return 0;

	while (infix[i] != '\0')   //说明栈中有元素。
	{

		while (infix[i] >= '0' && infix[i] <= '9')    //如果是数字则输出
		{
			if (flag) //考虑负数的情况
			{
				flag = 0;
				postfix[j++] = '-';
			}
			postfix[j++] = infix[i];//让存放后缀表达式的数组存放字符
			i++;
			if (infix[i]<'0' || infix[i]>'9') //判断是否为操作符，如果是，让后缀表达式中存放一个' '
				postfix[j++] = ' ';
		}
		if (infix[i] == ')' )       //如果是关于括号的符号，则进行栈操作
		{
			pop(&s, &e);
			while (e != '(' )
			{
				postfix[j++] = e;
				postfix[j++] = ' ';
				pop(&s, &e);
			}
		}
		else if (infix[i] == '+' || infix[i] == '-') //对于同运算级的+和-操作
		{
			if (infix[i] == '-' && (i == 0 || (i != 0 && (infix[i - 1]<'0' || infix[i - 1]>'9'))))  //当'-'号处于第一位，或前面是符号时，为负号标志
				flag = 1;
			else if (stack_empty(s))
				push(&s, infix[i]);
			else
			{
				do
				{
					pop(&s, &e);
					if (e == '(' )	//（优先级最大，比较以后要入栈
						push(&s, e);
					else
					{
						postfix[j++] = e;  //进行后缀表达式的添加，
						postfix[j++] = ' ';  //最后添加‘ ’字符
					}
				} while (!stack_empty(s) && e != '(' );
				push(&s, infix[i]);
			}
		}
		else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '(' )//对于乘除以及括号的开始进行压栈
			push(&s, infix[i]);
		else if (infix[i] == '\0')
			break;
		else
			return 0;
		i++;
	}

	while (!stack_empty(s))
	{
		pop(&s, &e);
		postfix[j++] = e;
		postfix[j++] = ' ';
	}

	clear_stack(&s);
	return 1;
}

/*******************根据后续表达式计算结果********************************/
int  Calculator(char *postfix, int *result)
{
	SqStack s;
	char *op; //存放后缀表达式中的每个因数或运算符  
	char *buf = postfix; //声明bufhe saveptr两个变量，是strtok_r函数的需要。  
	char *saveptr = NULL;
	int d, e, f;

	if (init_stack(&s) != 1)
		return 0;

	while ((op = strtok(buf, " ")) != NULL)//利用字符串分割函数
	{
		buf = NULL;						//把指针置空
		switch (op[0])
		{
		case '+':
			pop(&s, &d);
			pop(&s, &e);
			f = d + e;
			push(&s, f);
			break;
		case '-':
			if (op[1] >= '0' && op[1] <= '9')    //是负号而不是减号
			{
				d = atoi(op);
				push(&s, d);
				break;
			}
			pop(&s, &d);
			pop(&s, &e);
			f = e - d;
			push(&s, f);
			break;
		case '*':
			pop(&s, &d);
			pop(&s, &e);
			f = e*d;
			push(&s, f);
			break;
		case '/':
			pop(&s, &d);
			pop(&s, &e);
			f = e / d;
			push(&s, f);
			break;
		default:				//考虑数字的情况，进行atoi函数进行转化
			d = atoi(op);
			push(&s, d);		//进行压栈
			break;
		}
	}
	pop(&s, result);
	clear_stack(&s);
	return 0;
}

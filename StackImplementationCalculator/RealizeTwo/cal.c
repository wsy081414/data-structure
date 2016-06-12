#define _CRT_SECURE_NO_WARNINGS 1

#include"cal.h"

char h[6] = { '+', '-', '*', '/', '(', ')' };

//优先级判断
char Precede(char a, char b)
{
	int i, c, d;
	char bijiao[6][6] =
	{
		{ '>', '>', '<', '<', '<', '>' },
		{ '>', '>', '<', '<', '<', '>' },
		{ '>', '>', '>', '>', '<', '>' },
		{ '>', '>', '>', '>', '<', '>' },
		{ '<', '<', '<', '<', '<', '=' },
		{ '>', '>', '>', '>', ' ', '>' },

	};

	for (i = 0; i <6; i++)
	{
		if (a == h[i])
			c = i;
		if (b == h[i])
			d = i;
	}

	return bijiao[c][d];
}
/*******************栈的基本操作********************************/
int InitStack(SqStack *s)
{
	s->top = -1;
	return 1;
}

int CreateStack(SqStack *s)
{
	s->top = -1;
	return 1;
}

void Gettop(SqStack* S, SElemType *e)
{
	if (S->top == -1)
		return;
	else
		*e = S->data[S->top];
}

int stack_empty(SqStack *s)
{
	if (s->top == -1)
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
/*******************中缀表达式转换为后缀表达式*******************************/
int TransmitExpression(char *NifixExpression, char *PostfixExpression)
{
	SqStack s;
	SElemType e = 0;
	int i = 0, j = 0;
	SElemType ch = 0;

	InitStack(&s);
	while (NifixExpression[i] != '\0')    //说明栈中有元素
	{

		while (NifixExpression[i] >= '0' && NifixExpression[i] <= '9')     //如果是数字则输出
		{

			PostfixExpression[j++] = NifixExpression[i]; //让存放后缀表达式的数组存放字符
			i++;
			if (NifixExpression[i]<'0' || NifixExpression[i]>'9') //判断是否为操作符，如果是，让后缀表达式中存放一个''
				PostfixExpression[j++] = ' ';
		}
		if (NifixExpression[i] == '\0')
		{
			break;
		}
		if (stack_empty(&s) == 1)
		{
			push(&s, NifixExpression[i]);
			i++;
		}
		else
		{
			Gettop(&s, &ch);
			switch (Precede(ch, NifixExpression[i]))
			{
			case '<':                              //如果栈顶的优先级低。则直接入栈
				push(&s, NifixExpression[i]);
				i++;
				break;
			case '>':                             //如果读取的优先级高，则栈顶先退栈
				pop(&s, &ch);
				PostfixExpression[j++] = ch;
				PostfixExpression[j++] = ' ';
				break;
			case '=':
				pop(&s, &ch);
				i++;
				break;
			}

		}
	}
	while (stack_empty(&s) != 1)
	{
		pop(&s, &e);
		PostfixExpression[j++] = e;
		PostfixExpression[j++] = ' ';
	}

	InitStack(&s);
	return 1;
}

int judge_type(char c)                             //判断读取的是数字还是字符
{
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		if (h[i] == c)
			return SYMBOL;                        //符号
	}
	if (c == ' ')
		return SPACE;                           //空格
	return NUM;                                 //数字
}
/*******************根据后缀表达式计算结果*******************************/
int  EvaluateExpression(char *PostfixExpression, int *result)
{
	SqStack s;
	int ret = 0;
	int d, e, f;
	int i = 0;
	InitStack(&s);

	while (PostfixExpression[i] != '\0')//利用字符串分割函数
	{

		switch (judge_type(PostfixExpression[i]))
		{
		case SYMBOL:                                     //读取的是符号
			switch (PostfixExpression[i])
			{
			case '+':
				pop(&s, &d);
				pop(&s, &e);
				f = d + e;
				push(&s, f);
				break;
			case '-':
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
			default:
				break;
			}
			//对这两个数进行运算
			//将运算结果入站
			i++;
			ret = 0;
			break;
		case NUM:
			while (judge_type(PostfixExpression[i]) == 1)
			{
				/*ret = atoi(PostfixExpression[i]);*/
				ret = ret * 10 + PostfixExpression[i] - '0';        //将字符数字转换成对应的整数
				i++;
			}
			push(&s, ret);                        //将这个数字进行压栈
			ret = 0;
			break;
		case SPACE:                                    //读取的是空格
			i++;
			break;
		}

	}
	pop(&s, &ret);
	*result = ret;
	InitStack(&s);
	return 0;
}

void Menu()
{
	printf("*^-^*********计算器**********^-^*\n");
	printf("*^-^*       0.exit          *^-^*\n");
	printf("*^-^*    1.Create_Expr      *^-^*\n");
	printf("*^-^*    2.Transmit_Expr    *^-^*\n");
	printf("*^-^*    3.Evaluate_Expr    *^-^*\n");
	printf("*^-^*******( ●—● )********^-^*\n");
	printf("请选择(^-^):");
}


[100000]
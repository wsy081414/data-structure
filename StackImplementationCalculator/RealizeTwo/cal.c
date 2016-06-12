#define _CRT_SECURE_NO_WARNINGS 1

#include"cal.h"

char h[6] = { '+', '-', '*', '/', '(', ')' };

//���ȼ��ж�
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
/*******************ջ�Ļ�������********************************/
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
/*******************��׺���ʽת��Ϊ��׺���ʽ*******************************/
int TransmitExpression(char *NifixExpression, char *PostfixExpression)
{
	SqStack s;
	SElemType e = 0;
	int i = 0, j = 0;
	SElemType ch = 0;

	InitStack(&s);
	while (NifixExpression[i] != '\0')    //˵��ջ����Ԫ��
	{

		while (NifixExpression[i] >= '0' && NifixExpression[i] <= '9')     //��������������
		{

			PostfixExpression[j++] = NifixExpression[i]; //�ô�ź�׺���ʽ���������ַ�
			i++;
			if (NifixExpression[i]<'0' || NifixExpression[i]>'9') //�ж��Ƿ�Ϊ������������ǣ��ú�׺���ʽ�д��һ��''
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
			case '<':                              //���ջ�������ȼ��͡���ֱ����ջ
				push(&s, NifixExpression[i]);
				i++;
				break;
			case '>':                             //�����ȡ�����ȼ��ߣ���ջ������ջ
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

int judge_type(char c)                             //�ж϶�ȡ�������ֻ����ַ�
{
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		if (h[i] == c)
			return SYMBOL;                        //����
	}
	if (c == ' ')
		return SPACE;                           //�ո�
	return NUM;                                 //����
}
/*******************���ݺ�׺���ʽ������*******************************/
int  EvaluateExpression(char *PostfixExpression, int *result)
{
	SqStack s;
	int ret = 0;
	int d, e, f;
	int i = 0;
	InitStack(&s);

	while (PostfixExpression[i] != '\0')//�����ַ����ָ��
	{

		switch (judge_type(PostfixExpression[i]))
		{
		case SYMBOL:                                     //��ȡ���Ƿ���
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
			//������������������
			//����������վ
			i++;
			ret = 0;
			break;
		case NUM:
			while (judge_type(PostfixExpression[i]) == 1)
			{
				/*ret = atoi(PostfixExpression[i]);*/
				ret = ret * 10 + PostfixExpression[i] - '0';        //���ַ�����ת���ɶ�Ӧ������
				i++;
			}
			push(&s, ret);                        //��������ֽ���ѹջ
			ret = 0;
			break;
		case SPACE:                                    //��ȡ���ǿո�
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
	printf("*^-^*********������**********^-^*\n");
	printf("*^-^*       0.exit          *^-^*\n");
	printf("*^-^*    1.Create_Expr      *^-^*\n");
	printf("*^-^*    2.Transmit_Expr    *^-^*\n");
	printf("*^-^*    3.Evaluate_Expr    *^-^*\n");
	printf("*^-^*******( �񡪡� )********^-^*\n");
	printf("��ѡ��(^-^):");
}


[100000]
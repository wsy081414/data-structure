#define _CRT_SECURE_NO_WARNINGS 1

#include"cal.h"



/*******************ջ�Ļ�������********************************/
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

/*******************������ʽת��Ϊ�������ʽ********************************/
int To_PostFix(char *infix, char *postfix)
{
	SqStack s;
	int e = 0;//���г�ջ��ջ����
	int i = 0, j = 0;//�ֱ����ѭ��������±�
	int flag = 0;//

	if (init_stack(&s) != 1)   //�ж�ջ�Ƿ�Ϊ�գ�
		return 0;

	while (infix[i] != '\0')   //˵��ջ����Ԫ�ء�
	{

		while (infix[i] >= '0' && infix[i] <= '9')    //��������������
		{
			if (flag) //���Ǹ��������
			{
				flag = 0;
				postfix[j++] = '-';
			}
			postfix[j++] = infix[i];//�ô�ź�׺���ʽ���������ַ�
			i++;
			if (infix[i]<'0' || infix[i]>'9') //�ж��Ƿ�Ϊ������������ǣ��ú�׺���ʽ�д��һ��' '
				postfix[j++] = ' ';
		}
		if (infix[i] == ')' )       //����ǹ������ŵķ��ţ������ջ����
		{
			pop(&s, &e);
			while (e != '(' )
			{
				postfix[j++] = e;
				postfix[j++] = ' ';
				pop(&s, &e);
			}
		}
		else if (infix[i] == '+' || infix[i] == '-') //����ͬ���㼶��+��-����
		{
			if (infix[i] == '-' && (i == 0 || (i != 0 && (infix[i - 1]<'0' || infix[i - 1]>'9'))))  //��'-'�Ŵ��ڵ�һλ����ǰ���Ƿ���ʱ��Ϊ���ű�־
				flag = 1;
			else if (stack_empty(s))
				push(&s, infix[i]);
			else
			{
				do
				{
					pop(&s, &e);
					if (e == '(' )	//�����ȼ���󣬱Ƚ��Ժ�Ҫ��ջ
						push(&s, e);
					else
					{
						postfix[j++] = e;  //���к�׺���ʽ����ӣ�
						postfix[j++] = ' ';  //�����ӡ� ���ַ�
					}
				} while (!stack_empty(s) && e != '(' );
				push(&s, infix[i]);
			}
		}
		else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '(' )//���ڳ˳��Լ����ŵĿ�ʼ����ѹջ
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

/*******************���ݺ������ʽ������********************************/
int  Calculator(char *postfix, int *result)
{
	SqStack s;
	char *op; //��ź�׺���ʽ�е�ÿ�������������  
	char *buf = postfix; //����bufhe saveptr������������strtok_r��������Ҫ��  
	char *saveptr = NULL;
	int d, e, f;

	if (init_stack(&s) != 1)
		return 0;

	while ((op = strtok(buf, " ")) != NULL)//�����ַ����ָ��
	{
		buf = NULL;						//��ָ���ÿ�
		switch (op[0])
		{
		case '+':
			pop(&s, &d);
			pop(&s, &e);
			f = d + e;
			push(&s, f);
			break;
		case '-':
			if (op[1] >= '0' && op[1] <= '9')    //�Ǹ��Ŷ����Ǽ���
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
		default:				//�������ֵ����������atoi��������ת��
			d = atoi(op);
			push(&s, d);		//����ѹջ
			break;
		}
	}
	pop(&s, result);
	clear_stack(&s);
	return 0;
}

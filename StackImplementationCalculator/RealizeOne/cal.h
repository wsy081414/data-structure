#define _CRT_SECURE_NO_WARNINGS 1


#ifndef __CAL_H__

#define __CAL_H__

//����˳��ջʵ�ּ�����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 50


typedef int SElemType;

//����һ��˳��洢ջ
typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}SqStack;


int To_PostFix(char *infix, char *postfix);

int  Calculator(char *postfix, int *result);



#endif // !__CAL_H__

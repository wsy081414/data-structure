#define _CRT_SECURE_NO_WARNINGS 1


#ifndef __CAL_H__

#define __CAL_H__

//利用顺序栈实现计算器

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 50


typedef int SElemType;

//定义一个顺序存储栈
typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}SqStack;


int To_PostFix(char *infix, char *postfix);

int  Calculator(char *postfix, int *result);



#endif // !__CAL_H__

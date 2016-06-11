#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __CAL_H__
#define __CAL_H__



//利用顺序栈实现计算器

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 50
#define NUM 1
#define SYMBOL 0
#define SPACE -1


typedef int SElemType;

//定义一个顺序存储栈
typedef struct
{
	SElemType data[MAXSIZE];
	int top;
}SqStack;





char Precede(char a, char b);
int InitStack(SqStack *s);
int CreateStack(SqStack *s);
int  EvaluateExpression(char *PostfixExpression, int *result);
void Gettop(SqStack* S, SElemType *e);
int stack_empty(SqStack *s);
int stack_length(SqStack *s);
int push(SqStack *s, SElemType e);
int pop(SqStack *s, SElemType *e);
int TransmitExpression(char *NifixExpression, char *PostfixExpression);
int judge_type(char c);                            
void Menu();





#endif //!__CAL_H__
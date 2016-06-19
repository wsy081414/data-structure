#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __SCHOOL_SYSTEM_C__
#define __SCHOOL_SYSTEM_C__


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#define MAX_INF 40
#define MAX_SIZE 40
#define PERSON_SIZE 35

typedef  char Datatype;

typedef struct system
{
	Datatype data[MAX_INF];
	Datatype infor[MAX_INF];
	struct system *next, *prev, *child;//childָ��ָ������Ӳ��ţ�nextָ�����ͬ�����ţ�prevָ����Ǹ��ڵ�
} BITNODE,*BITREE;


static enum a
{
	QUIT,
	CREATE,
	FINDALLCHILD,
	FINDPARENT,
	FINDPERSON,
	FINDCOLLEGE,
	INIT,
	SHOW
	
};

void printf_menu();

void Quit();

BITREE CreateTRee();

void pretraversal_binary_tree(BITREE node);//������б���
void intraversal_binary_tree(BITREE node);//������б���
void postraversal_binary_tree(BITREE node);//������б���


void FindAllCHild(BITREE root);

void FindParent(BITREE root);

void FindPerson(BITREE root);

void Quit();

void FindCollege(BITREE root);

void BTreeSetNull(BITREE tree);

#endif // !__SCHOOL_SYSTEM_C__

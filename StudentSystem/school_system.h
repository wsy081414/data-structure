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
	struct system *next, *prev, *child;//child指针指向的是子部门，next指向的是同级部门，prev指向的是父节点
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

void pretraversal_binary_tree(BITREE node);//先序进行遍历
void intraversal_binary_tree(BITREE node);//中序进行遍历
void postraversal_binary_tree(BITREE node);//后序进行遍历


void FindAllCHild(BITREE root);

void FindParent(BITREE root);

void FindPerson(BITREE root);

void Quit();

void FindCollege(BITREE root);

void BTreeSetNull(BITREE tree);

#endif // !__SCHOOL_SYSTEM_C__

#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __LINKLIST_H__
#define __LINKLIST_H__


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int datatype;

typedef struct LinkNode
{
	datatype data;
	struct LinkNode *next;
}LinkNode,*pLinkNode;

typedef struct LinkList
{
	LinkNode *pHead;
}LinkList,*pLinkList;


static enum A
{
	EXIT,
	INIT,
	PUSHBACK,
	POPBACK,
	PUSHFRONT,
	POPFRONT,
	INSERT,
	REMOVE,
	REMOVEALL,
	BUBBLESORT,
	ERASE,
	PRINTLIST,
	ERASENOTTAIL,
	REVERSE,
	INSERTFRONTNODE,
	FINDMIDNODE,
	DELKNODE
};

void InitLinkList(pLinkList pList);
void DestroyList(pLinkList pList);
void PushBack(pLinkList pList,datatype x);
void PopBack(pLinkList pList);
void PushFront(pLinkList pList, datatype x);
void PopFront(pLinkList pList);
void PrintList(pLinkList pList);
pLinkNode Find(pLinkList pList, datatype x);
void Insert(pLinkList pList, pLinkNode pos, datatype x);
void Remove(pLinkList pList,datatype x);
void RemoveAll(pLinkList pList, datatype x);
void Erase(pLinkList pList,pLinkNode pos);
void BubbleSort(pLinkList pList);
void meau();

void EraseNotTail(pLinkNode pos);
void InsertFrontNode(pLinkNode pos, datatype x);
void Reverse(pLinkList plist);
pLinkNode FindMidNode(pLinkList pList);

void DelKNode(pLinkList pList, int k);
#endif //!__LINKLIST_H__
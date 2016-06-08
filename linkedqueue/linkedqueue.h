#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __QUEUE_H__
#define __QUEUE_H__


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int datatype;

typedef struct queue
{
	datatype data;
	struct queue *next;
}Quenode,*PtrQueue;

typedef struct queue_list
{
	PtrQueue Head;
	PtrQueue Tail;
}LinkQueue, *pLinkQueue;

enum  
{
	EXIT,
	INIT,
	DESTORY,
	CLEAR,
	LENGTH,
	ENQUEUE,
	DEQUEUE,
	PRINTQUEUE
};

void InitQueue(pLinkQueue q);

void DestoryQueue(pLinkQueue q);

void ClearQueue(pLinkQueue q);

int QueueIsEmpty(pLinkQueue q);

int QueueLength(pLinkQueue q);

void GetHead(pLinkQueue q, datatype *p);

void EnQueue(pLinkQueue q ,datatype x);

void Dequeue(pLinkQueue q);

void PrintQueue(pLinkQueue q);

void menu();

#endif //£¡__QUEUE_H__



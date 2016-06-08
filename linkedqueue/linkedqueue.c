#define _CRT_SECURE_NO_WARNINGS 1

#include"linkedqueue.h"


void menu()
{
	printf("$$$$$$$$$$$$$$    QUEUE    $$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$￥$$$$$$$$$$$$$$$$$$$$\n");
	printf("$$$  1.init            2.destory        $$$\n");
	printf("$$$  3.clear           4.length         $$$\n");
	printf("$$$  5.enqueue         6.dequeue        $$$\n");
	printf("$$$  7.printqueue      0.EXIT           $$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

}
void InitQueue(pLinkQueue q)
{
	assert(q);
	q->Head = q->Tail = (PtrQueue)malloc(sizeof(Quenode));
	if (q->Head == NULL)
	{
		printf("out of memory");
		exit(EXIT_FAILURE);
	}
	q->Head->next = NULL;

}

void DestoryQueue(pLinkQueue q)
{
	assert(q);
	while (q->Head != NULL)
	{
		q->Tail = q->Head->next;
		free(q->Head);
		q->Head = q->Tail;
	}
}

void ClearQueue(pLinkQueue q)
{
	assert(q);
	PtrQueue p = q->Head->next;
	while (p != NULL)
	{
		PtrQueue tmp = p;
		p = p->next;
		free(tmp);
		tmp = NULL;
	}
	p = q->Head;
	q->Head = q->Tail = NULL;
	free(p);
}

int QueueIsEmpty(pLinkQueue q)
{
	assert(q);

	if (q->Head == q->Tail)
		return 1;
	else
		return 0;

}

int QueueLength(pLinkQueue q)
{
	assert(q);

	PtrQueue cur = q->Head->next;
	int count = 0;
	while (cur != NULL)
	{
		count++;
		cur = cur->next;
	}
	return count;
}

void GetHead(pLinkQueue q, datatype *p)
{
	assert(q);

	if (QueueIsEmpty(q))
	{
		printf("队列为空队列！\n");
	}
	*p = q->Head->data;

}

void EnQueue(pLinkQueue q , datatype x)
{
	assert(q);
	PtrQueue cur = q->Head;
	PtrQueue newnode = (PtrQueue)malloc(sizeof(Quenode));
	if (newnode == NULL)
	{
		printf("out of memory");
		exit(EXIT_FAILURE);
	}
	newnode->data = x;
	newnode->next = NULL;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur ->next= newnode;
	q->Tail = newnode;
}

void Dequeue(pLinkQueue q)
{
	assert(q);
	PtrQueue del = NULL,cur=NULL;
	if (q->Head == q->Tail)
	{
		printf("队列为空\n");
		return;
	}
	cur = q->Head->next;
	del = cur;
	q->Head ->next= cur->next;
	free(del);
	del = NULL;

}

void PrintQueue(pLinkQueue q)
{
	assert(q);
	PtrQueue cur = q->Head->next;
	if (q->Head == q->Tail)
		return;

	while (cur != NULL)
	{
		printf("%3d", cur->data);
		cur = cur->next;
	}
	printf("\n");
}
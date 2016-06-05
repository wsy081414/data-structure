#define _CRT_SECURE_NO_WARNINGS 1


#include"linklist.h"


void meau()
{
	printf("$$$$$$$$$$$$$$    SEQLIST    $$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$￥$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$$$  1.init              2.push_back      $$$\n");
	printf("$$$  3.pop_back          4.push_front     $$$\n");
	printf("$$$  5.pop_front         6.insert         $$$\n");
	printf("$$$  7.remove            8.removeall      $$$\n");
	printf("$$$  9.bubblesort        10.earse         $$$\n");
	printf("$$$  11.printlist         0.EXIT          $$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
}

void InitLinkList(pLinkList pList)
{
	assert(pList);
	pList->pHead = NULL;

}
void DestroyList(pLinkList pList)
{
	assert(pList);
	pLinkNode p = NULL;
	pLinkNode cur = NULL;
	cur = pList->pHead;
	if (NULL == pList->pHead)
	{
		return;
	}
	while (cur != NULL)
	{
		p = cur;
		cur = cur->next;
		free(p);
	}
	pList->pHead = NULL;
}
void judgement(pLinkNode newnode)
{
	if (NULL == newnode)
	{
		printf("out of memory");
		exit(EXIT_FAILURE);
	}
}

void PushBack(pLinkList pList, datatype x)
{
	assert(pList);
	pLinkNode cur= NULL;
	pLinkNode prev = NULL;
	pLinkNode newnode = (pLinkNode)malloc(sizeof(LinkNode));
	newnode->data = x;
	newnode->next = NULL;
	judgement(newnode);
	if (NULL == pList->pHead)
	{
		pList->pHead = newnode;
		return;
	}
	else 
	{
		cur = pList->pHead;
		while (cur != NULL)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = newnode;
	}
}
void PopBack(pLinkList pList)
{
	pLinkNode cur = NULL;
	pLinkNode del = NULL;
	assert(pList);
	cur = pList->pHead;
	if (pList->pHead == NULL)
	{
		printf("此链表为空链表");
		return;
	}
	else if (NULL==pList->pHead->next)
	{
		free(cur);
		pList->pHead = NULL;
		return;
	}
	else
	{
		while (cur->next != NULL)
		{
			del = cur;
			cur = cur->next;
		}
		free(cur);
		del->next = NULL;
		
	}
}
void PushFront(pLinkList pList, datatype x)
{
	assert(pList);
	pLinkNode newnode = (pLinkNode)malloc(sizeof(LinkNode));
	newnode->data = x;
	newnode->next = NULL;
	judgement(newnode);
	newnode->next = pList->pHead;
	pList->pHead = newnode;
	
}
void PopFront(pLinkList pList)
{
	pLinkNode cur = NULL;
	pLinkNode del = NULL;
	assert(pList);
	if (pList->pHead == NULL)
	{
		printf("此链表为空链表");
		return;
	}
	else
	{
		cur = pList->pHead->next;
		del = pList->pHead;
		free(del);
		pList->pHead = cur;
	}
}
void PrintList(pLinkList pList)
{
	pLinkNode cur = NULL;
	assert(pList);
	cur = pList->pHead;
	while (cur != NULL)
	{
		printf("%d  ", cur->data);
		cur = cur->next;
	}
	printf("\n");

}
pLinkNode Find(pLinkList pList, datatype x)
{
	pLinkNode cur = NULL;
	pLinkNode find = NULL;
	assert(pList);
	cur = pList->pHead;
	while (cur != NULL)
	{
		if (x == cur->data)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
void Insert(pLinkList pList, pLinkNode pos, datatype x)
{
	assert(pList);
	pLinkNode cur = pList->pHead;
	pLinkNode front =NULL;
	pLinkNode newnode = (pLinkNode)malloc(sizeof(LinkNode));
	judgement(newnode);
	newnode->data = x;
	newnode->next = NULL;
	while (cur != NULL)
	{
		if (cur == pos)
		{

			break;
		}
		front = cur;
		cur = cur->next;
	}
	if (NULL == front)
	{
		pList->pHead = newnode;
		newnode->next = cur;
	}
	else
	{
		front->next = newnode;
		newnode->next = cur;
	}
}
void Remove(pLinkList pList, datatype x)
{
	pLinkNode cur = NULL;
	pLinkNode del = NULL;
	pLinkNode front = NULL;
	assert(pList);
	if (pList->pHead == NULL)
	{
		printf("此链表为空链表");
		return;
	}
	cur = pList->pHead;
	front = cur;
	while (cur != NULL)
	{
		
		if (cur->data == x)
		{
			del = cur;
			cur = cur->next;
			front->next = cur;
			free(del);
			del = NULL;	
			break;
		}
		front = cur;
		cur = cur->next;
	}
	printf("没有值为%d的节点\n", x);
}
void RemoveAll(pLinkList pList, datatype x)
{
	pLinkNode cur = NULL;
	pLinkNode del = NULL;
	pLinkNode front = NULL;
	assert(pList);
	if (pList->pHead == NULL)
	{
		printf("此链表为空链表");
		return;
	}
	cur = pList->pHead;
	front = cur;
	while (cur != NULL)
	{

		if (cur->data == x)
		{
			del = cur;
			cur = cur->next;
			front->next = cur;
			free(del);
			del = NULL;
			continue;
		}
		front = cur;
		cur = cur->next;
	}
}
void Erase(pLinkList pList, pLinkNode pos)
{
	pLinkNode cur = NULL;
	pLinkNode erase = NULL;
	pLinkNode front =pList->pHead ;
	assert(pList);
	cur = pList->pHead;
	if (pList->pHead == NULL)
	{
		printf("此链表为空链表");
		return;
	}
	while (cur != NULL)
	{
	
		if (pos == cur)
		{
			cur = cur->next;
			erase = pos;
			free(erase);
			erase->next = NULL;
			front->next = cur;
			return;
		}
		front = cur;
		cur = cur->next;
	}

}
void BubbleSort(pLinkList pList)
{
	assert(pList);
	pLinkNode p = NULL;
	pLinkNode q = NULL;
	int flag = 0;

	for (p=pList->pHead; p!=NULL ; p=p->next)
	{
		flag = 1;
		for (q = p->next; q != NULL;q=q->next)
		{	
			if (p->data > q->data)
			{
				datatype tmp = p->data;
				p->data = q->data;
				q->data = tmp;
				flag = 0;
			}
		}
		if (flag == 1)
		{
			break;
		}
	}

}


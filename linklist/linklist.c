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
		printf("此链表为空链表\n");
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
		printf("此链表为空链表\n");
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
	if (pos == NULL)
	{

		printf("没有这样一个元素，无法插入\n");
		return;
	}
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
		printf("此链表为空链表\n");
		return;
	}
	cur = pList->pHead;
	front = cur;
	while (cur != NULL)
	{
		
		if (cur->data == x)
		{
			if (cur == pList->pHead)	//考虑第一个节点的情况
			{
				del = cur;
				pList->pHead = cur->next;
				free(del);
			}
			else                        //删除非第一个节点
			{
				del = cur;
				front->next = cur->next;
				free(del);
			}
			return;
		}
		else
		{
			front = cur;
			cur = cur->next;
		}
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
		printf("此链表为空链表\n");
		return;
	}
	cur = pList->pHead;
	front = cur;
	while (cur != NULL)
	{

		if (cur->data == x)
		{
			if (cur == pList->pHead)	//考虑第一个节点的情况
			{
				del = cur;
				front = cur->next;			//记得要移动front
				pList->pHead = cur->next;
				free(del);
			}
			else                        //删除非第一个节点
			{
				del = cur;
				front->next = cur->next;
				free(del);
			}
			cur = front;			//让cur移动到当前的front进行操作

		}
		else
		{
			front = cur;
			cur = cur->next;
		}
	}
	//printf("没有值为%d的节点\n", x);
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
			if (pos == pList->pHead)
			{
				erase = pos;
				pList->pHead = cur->next;
				free(erase);
				erase->next = NULL;
			}
			else
			{
				erase = pos;
				front->next = cur->next;
				free(erase);
				erase->next = NULL;
				
			}
			return;
		}
		else
		{
			front = cur;
			cur = cur->next;

		}
	}
	

}
void BubbleSort(pLinkList pList)
{

	pLinkNode cur = NULL;
	pLinkNode tail = NULL;
	assert(pList);
	cur = pList->pHead;
	if ((pList->pHead == NULL)||(pList->pHead->next==NULL))
	{
		return;
	}
	while (cur != tail)		//当尾指针不等于头指针时进行冒泡
	{
		while (cur->next != tail)	//控制cur指针最后到的位置是倒数第二个节点
		{
			
			if (cur->data > cur->next->data)
			{
				datatype tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
			}
			cur = cur->next;
		}
		tail = cur;
		cur = pList->pHead;
	}
}


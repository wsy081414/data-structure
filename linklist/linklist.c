#define _CRT_SECURE_NO_WARNINGS 1


#include"linklist.h"


void meau()
{
	printf("$$$$$$$$$$$$$$$$$$    SEQLIST    $$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$￥$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$$$  1.init              2.push_back          $$$\n");
	printf("$$$  3.pop_back          4.push_front         $$$\n");
	printf("$$$  5.pop_front         6.insert             $$$\n");
	printf("$$$  7.remove            8.removeall          $$$\n");
	printf("$$$  9.bubblesort        10.earse             $$$\n");
	printf("$$$  11.printlist        12.EraseNotTail      $$$\n");
	printf("$$$  13.reverse          14.insertfrontnode   $$$\n");
	printf("$$$  15.FindMidNode       0.EXIT              $$$\n");
	printf("$$$  16.DelKnode       0.EXIT                 $$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
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

//链表的冒泡排序
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

//删除无头非尾节点
void EraseNotTail(pLinkNode pos)
{
	pLinkNode del = NULL;
	assert(pos->next != NULL);		//断言，排除尾节点的情况

	pos->data = pos->next->data;	//让当前节点后面节点的数据赋给当前节点。
	del = pos->next;				//删除记录当前节点后的节点
	pos->next = pos->next->next;	//当前节点的nex指向删除节点的下一个节点。
	free(del);
	del = NULL;
}

//反转链表
void Reverse(pLinkList plist)
{
	pLinkNode tmp = NULL;		//记录中间节点
	pLinkNode cur = NULL;		//记录链表的第一个节点
	pLinkNode newnode = NULL;	//记录翻转后的第一个节点
	assert(plist);
	cur = plist->pHead;
	while (cur != NULL)
	{
		tmp = cur;					//	
		cur = cur->next;
		tmp->next = newnode;
		newnode = tmp;
	}
	plist->pHead = newnode;
}


//在当前节点前插入一个数据x

void InsertFrontNode(pLinkNode pos, datatype x)
{

	pLinkNode newnode = NULL;
	assert(pos);
	newnode = (pLinkNode)malloc(sizeof(LinkNode));
	if (NULL == newnode)
	{
		printf("out of memory");
		exit(EXIT_FAILURE);
	}
	newnode->data = pos->data;
	pos->data = x;
	newnode->next = pos->next;
	pos->next = newnode;

}

//查找链表的中间节点。
pLinkNode FindMidNode(pLinkList pList)
{
	pLinkNode fast = NULL;
	pLinkNode slow = NULL;
	assert(pList);
	slow = fast = pList->pHead;
	while (fast != NULL)
	{
		if (fast->next != NULL)
		{
			fast = fast->next->next;
		}
		else
		{
			break;
		}
		slow = slow->next;
	}
	return slow;
}

//删除单链表的倒数第K个节点（K>1&&K<总长度）
void DelKNode(pLinkList pList, int k)
{
	pLinkNode front = NULL;
	pLinkNode back = NULL;
	pLinkNode del = NULL;
	
	assert(pList);
	if (pList->pHead == NULL)
	{
		printf("链表为空！！\n");
		return;
	}
	if (k == 1)
	{
		printf("K应当大于1\n");
		return;
	}
	front = back = pList->pHead;
	while (front != NULL)
	{
		k--;
		if (k < 0)
		{
			back = back->next;
		}
		front = front->next;
	}
	if (k <= 0)
	{
		back->data = back->next->data;
		del = back->next;
		back->next = back->next->next;
		free(del);
	}
	

	
}


//判断链表是否带环
pLinkNode CheckCycle(pLinkList pList)
{
	pLinkNode fast = NULL;
	pLinkNode slow = NULL;
	assert(pList);
	fast = slow = pList->pHead;
	while (fast != NULL)
	{
		if (fast->next != NULL)
		{
			fast = fast->next->next;
		}
		else
		{
			break;
		}
		slow = slow->next;
		if (slow == fast)
			return slow;
	}
	return NULL;
}

//得到链表环的长度
int GetCycleLength(pLinkNode meet)
{
	pLinkNode fast = NULL;
	pLinkNode slow = NULL;
	int length = 0;
	if (meet == NULL)
	{
		printf("此链表不带环\n");
	}
	else
	{
		fast = slow = meet;
		fast = fast->next->next;
		slow = slow->next;
		length++;
		if (slow == fast)
		{
			return length;
		}
	}
	return length;

}

//获取带环的环入口
pLinkNode GetCycleEntryNode(pLinkList pList)
{
	pLinkNode fast = NULL;
	pLinkNode slow = NULL;
	assert(pList);
	fast = slow = pList->pHead;
	while (fast != NULL)
	{
		if (fast->next != NULL)
		{
			fast = fast->next->next;
		}
		else
		{
			printf("不为带环链表！\n");
			return NULL;
		}
		slow = slow->next;
		if (slow == fast)
		{
			break;
		}
	}
	fast = pList->pHead;
	while (fast != slow)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return fast;
}

//判断两个链表是否相交
int CheckCross(pLinkList pList1, pLinkList pList2)
{
	pLinkNode ptr1 = NULL;
	pLinkNode ptr2 = NULL;
	pLinkNode tail = NULL;
	assert(pList1);
	assert(pList2);
	ptr1 = pList1->pHead;
	ptr2 = pList2->pHead;
	while (ptr1 != NULL)
	{
		ptr1 = ptr1->next;
	}
	tail = ptr1;
	ptr1->next = ptr2;
	ptr1 = pList1->pHead;
	while (ptr1 != ptr2&&ptr2 != NULL&&ptr1 != NULL)
	{
		if (ptr1->next != NULL)
		{
			ptr1 = ptr1->next->next;
		}
		else
		{
			tail->next = NULL;
			return 0;		//不相交
		}
		ptr2 = ptr2->next;

	}
	if (ptr1 == ptr2)
	{
		tail->next = NULL;

		return 1;		//相交
	}
	tail->next = NULL;

	return 0;
}

pLinkNode GetCrossNode(pLinkList pList1, pLinkList pList2)
{

	pLinkNode ptr1 = NULL;
	pLinkNode ptr2 = NULL;
	pLinkNode tail = NULL;
	assert(pList1);
	assert(pList2);
	ptr1 = pList1->pHead;
	ptr2 = pList2->pHead;
	while (ptr1 != NULL)
	{
		ptr1 = ptr1->next;
	}
	tail = ptr1;
	ptr1->next = ptr2;
	ptr1 = pList1->pHead;
	while (ptr1 != ptr2&&ptr2 != NULL&&ptr1 != NULL)
	{
		if (ptr1->next != NULL)
		{
			ptr1 = ptr1->next->next;
		}
		else
		{
			break;		//不相交
		}
		ptr2 = ptr2->next;

	}
	if (ptr1 == ptr2)
	{
		ptr1 = pList1->pHead;		//相交
		while (ptr1!=ptr2)
		{
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
			
		}
		tail->next = NULL;
		return ptr1;
	}
	tail->next = NULL;
	return NULL;
}

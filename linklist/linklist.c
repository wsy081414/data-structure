#define _CRT_SECURE_NO_WARNINGS 1


#include"linklist.h"


void meau()
{
	printf("$$$$$$$$$$$$$$$$$$    SEQLIST    $$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$��$$$$$$$$$$$$$$$$$$$$$$$$$\n");
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
		printf("������Ϊ������\n");
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
		printf("������Ϊ������\n");
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

		printf("û������һ��Ԫ�أ��޷�����\n");
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
		printf("������Ϊ������\n");
		return;
	}
	cur = pList->pHead;
	front = cur;
	while (cur != NULL)
	{
		
		if (cur->data == x)
		{
			if (cur == pList->pHead)	//���ǵ�һ���ڵ�����
			{
				del = cur;
				pList->pHead = cur->next;
				free(del);
			}
			else                        //ɾ���ǵ�һ���ڵ�
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
	printf("û��ֵΪ%d�Ľڵ�\n", x);
}
void RemoveAll(pLinkList pList, datatype x)
{
	pLinkNode cur = NULL;
	pLinkNode del = NULL;
	pLinkNode front = NULL;
	assert(pList);
	if (pList->pHead == NULL)
	{
		printf("������Ϊ������\n");
		return;
	}
	cur = pList->pHead;
	front = cur;
	while (cur != NULL)
	{

		if (cur->data == x)
		{
			if (cur == pList->pHead)	//���ǵ�һ���ڵ�����
			{
				del = cur;
				front = cur->next;			//�ǵ�Ҫ�ƶ�front
				pList->pHead = cur->next;
				free(del);
			}
			else                        //ɾ���ǵ�һ���ڵ�
			{
				del = cur;
				front->next = cur->next;
				free(del);
			}
			cur = front;			//��cur�ƶ�����ǰ��front���в���

		}
		else
		{
			front = cur;
			cur = cur->next;
		}
	}
	//printf("û��ֵΪ%d�Ľڵ�\n", x);
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
		printf("������Ϊ������");
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

//�����ð������
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
	while (cur != tail)		//��βָ�벻����ͷָ��ʱ����ð��
	{
		while (cur->next != tail)	//����curָ����󵽵�λ���ǵ����ڶ����ڵ�
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

//ɾ����ͷ��β�ڵ�
void EraseNotTail(pLinkNode pos)
{
	pLinkNode del = NULL;
	assert(pos->next != NULL);		//���ԣ��ų�β�ڵ�����

	pos->data = pos->next->data;	//�õ�ǰ�ڵ����ڵ�����ݸ�����ǰ�ڵ㡣
	del = pos->next;				//ɾ����¼��ǰ�ڵ��Ľڵ�
	pos->next = pos->next->next;	//��ǰ�ڵ��nexָ��ɾ���ڵ����һ���ڵ㡣
	free(del);
	del = NULL;
}

//��ת����
void Reverse(pLinkList plist)
{
	pLinkNode tmp = NULL;		//��¼�м�ڵ�
	pLinkNode cur = NULL;		//��¼����ĵ�һ���ڵ�
	pLinkNode newnode = NULL;	//��¼��ת��ĵ�һ���ڵ�
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


//�ڵ�ǰ�ڵ�ǰ����һ������x

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

//����������м�ڵ㡣
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

//ɾ��������ĵ�����K���ڵ㣨K>1&&K<�ܳ��ȣ�
void DelKNode(pLinkList pList, int k)
{
	pLinkNode front = NULL;
	pLinkNode back = NULL;
	pLinkNode del = NULL;
	
	assert(pList);
	if (pList->pHead == NULL)
	{
		printf("����Ϊ�գ���\n");
		return;
	}
	if (k == 1)
	{
		printf("KӦ������1\n");
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


//�ж������Ƿ����
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

//�õ������ĳ���
int GetCycleLength(pLinkNode meet)
{
	pLinkNode fast = NULL;
	pLinkNode slow = NULL;
	int length = 0;
	if (meet == NULL)
	{
		printf("����������\n");
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

//��ȡ�����Ļ����
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
			printf("��Ϊ��������\n");
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

//�ж����������Ƿ��ཻ
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
			return 0;		//���ཻ
		}
		ptr2 = ptr2->next;

	}
	if (ptr1 == ptr2)
	{
		tail->next = NULL;

		return 1;		//�ཻ
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
			break;		//���ཻ
		}
		ptr2 = ptr2->next;

	}
	if (ptr1 == ptr2)
	{
		ptr1 = pList1->pHead;		//�ཻ
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

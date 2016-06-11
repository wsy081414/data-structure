#define _CRT_SECURE_NO_WARNINGS 1

#include"linklist.h"

void Test()
{
	LinkList list;
	int input = 1;
	pLinkNode pos = 0;
	datatype x = 0;
	int k = 0;
	InitLinkList(&list);
	while (input)
	{
		meau();
		printf("请选择操作：");
		scanf("%d", &input);
		fflush(stdin);
		switch (input)
		{
		case INIT:
			InitLinkList(&list);
			break;
		case PUSHBACK:
			printf("请输入你要尾插节点的数据：\n");
			scanf("%d", &x);
			fflush(stdin);
			PushBack(&list,x);
			break;
		case POPBACK:
			PopBack(&list);
			break;
		case PUSHFRONT:
			printf("请输入你要尾插节点的数据：\n");
			scanf("%d", &x);
			fflush(stdin);
			PushFront(&list, x);
			break;
		case POPFRONT:
			PopFront(&list);
			break;
		case INSERT:
			printf("请输入你所插入位置的节点元素值");
			scanf("%d", &x);
			fflush(stdin);
			pos = Find(&list, x);
			printf("请输入你所插入节点元素值");
			scanf("%d", &x);
			fflush(stdin);
			Insert(&list, pos, x);
			break;
		case REMOVE:
			printf("请输入你需要删除单一节点的值：");
			scanf("%d", &x);
			fflush(stdin);
			Remove(&list,x);
			break;
		case REMOVEALL:
			printf("请输入你需要删除节点的值：");
			scanf("%d", &x);
			fflush(stdin);
			RemoveAll(&list, x);
			break;
		case BUBBLESORT:
			BubbleSort(&list);
			break;
		case ERASE:
			printf("请输入你所要擦除的节点数据：");
			scanf("%d", &x);
			fflush(stdin);
			pos = Find(&list, x);
			Erase(&list, pos);
			break;
		case PRINTLIST:
			PrintList(&list);
			break;
		case EXIT:
			DestroyList(&list);
			break;
		case ERASENOTTAIL:
			printf("删除一个无头非尾节点\n");
			printf("请输入你所删除的节点元素值");
			scanf("%d", &x);
			fflush(stdin);
			pos = Find(&list,x);
			EraseNotTail(pos);
			break;
		case REVERSE:
			printf("进行反转链表\n");
			Reverse(&list);
			break;
		case INSERTFRONTNODE:
			printf("在当前节点前插入一个数据x\n");
			printf("请输入当前节点元素值");
			scanf("%d", &x);
			fflush(stdin);
			pos = Find(&list, x);
			printf("请输入插入节点的数据\n");
			scanf("%d", &x);
			fflush(stdin);
			InsertFrontNode(pos, x);
			break;
		case FINDMIDNODE:
			printf("查找链表的中间节点\n");
			pLinkNode ret = NULL;
			ret = FindMidNode(&list);
			printf("链表的中间节点为：%d\n", ret->data);
			break;
		case DELKNODE:
			printf("删除链表倒数第K个节点：\n");
			scanf("%d", &k);
			fflush(stdin);
			DelKNode(&list,k);

		default:
			input = 1;
			break;
		}
	}
}
int main()
{
	Test();
	system("pause");
	return 0;
}
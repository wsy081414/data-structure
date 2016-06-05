#define _CRT_SECURE_NO_WARNINGS 1

#include"linklist.h"

void Test()
{
	LinkList list;
	int input = 1;
	datatype x = 0;
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
			pLinkNode pos = Find(&list, x);
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
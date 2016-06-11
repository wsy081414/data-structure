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
		printf("��ѡ�������");
		scanf("%d", &input);
		fflush(stdin);
		switch (input)
		{
		case INIT:
			InitLinkList(&list);
			break;
		case PUSHBACK:
			printf("��������Ҫβ��ڵ�����ݣ�\n");
			scanf("%d", &x);
			fflush(stdin);
			PushBack(&list,x);
			break;
		case POPBACK:
			PopBack(&list);
			break;
		case PUSHFRONT:
			printf("��������Ҫβ��ڵ�����ݣ�\n");
			scanf("%d", &x);
			fflush(stdin);
			PushFront(&list, x);
			break;
		case POPFRONT:
			PopFront(&list);
			break;
		case INSERT:
			printf("��������������λ�õĽڵ�Ԫ��ֵ");
			scanf("%d", &x);
			fflush(stdin);
			pos = Find(&list, x);
			printf("��������������ڵ�Ԫ��ֵ");
			scanf("%d", &x);
			fflush(stdin);
			Insert(&list, pos, x);
			break;
		case REMOVE:
			printf("����������Ҫɾ����һ�ڵ��ֵ��");
			scanf("%d", &x);
			fflush(stdin);
			Remove(&list,x);
			break;
		case REMOVEALL:
			printf("����������Ҫɾ���ڵ��ֵ��");
			scanf("%d", &x);
			fflush(stdin);
			RemoveAll(&list, x);
			break;
		case BUBBLESORT:
			BubbleSort(&list);
			break;
		case ERASE:
			printf("����������Ҫ�����Ľڵ����ݣ�");
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
			printf("ɾ��һ����ͷ��β�ڵ�\n");
			printf("����������ɾ���Ľڵ�Ԫ��ֵ");
			scanf("%d", &x);
			fflush(stdin);
			pos = Find(&list,x);
			EraseNotTail(pos);
			break;
		case REVERSE:
			printf("���з�ת����\n");
			Reverse(&list);
			break;
		case INSERTFRONTNODE:
			printf("�ڵ�ǰ�ڵ�ǰ����һ������x\n");
			printf("�����뵱ǰ�ڵ�Ԫ��ֵ");
			scanf("%d", &x);
			fflush(stdin);
			pos = Find(&list, x);
			printf("���������ڵ������\n");
			scanf("%d", &x);
			fflush(stdin);
			InsertFrontNode(pos, x);
			break;
		case FINDMIDNODE:
			printf("����������м�ڵ�\n");
			pLinkNode ret = NULL;
			ret = FindMidNode(&list);
			printf("������м�ڵ�Ϊ��%d\n", ret->data);
			break;
		case DELKNODE:
			printf("ɾ����������K���ڵ㣺\n");
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
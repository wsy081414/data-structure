#define _CRT_SECURE_NO_WARNINGS 1

#include"dynamic_seqlist.h"
void Test()
{
	Seqlist seq;
	int input = 1;
	int x = 0;
	int pos = 0;
	int search = 0;
	InitSqlist(&seq);
	while (input)
	{
		meau();
		printf("��ѡ��:");
		scanf("%d", &input);
		fflush(stdin);
		switch (input)
		{
		case INIT:
			InitSqlist(&seq);
			break;
		case PUSHBACK:
			fflush(stdin);
			printf("����������Ҫβ��push��Ԫ�أ�\n");
			scanf("%d", &x);
			PushBack(&seq, x);
			break;
		case POPBACK:
			PopBack(&seq);
			break;
		case PUSHFRONT:
			fflush(stdin);
			printf("����������Ҫͷ��push��Ԫ�أ�\n");
			scanf("%d", &x);
			PushFront(&seq, x);
			break;
		case POPFRONT:
			PopFront(&seq);
			break;
		case INSERT:
			fflush(stdin);
			printf("����������Ҫ�����Ԫ�أ�\n");
			scanf("%d", &x);
			fflush(stdin);
			printf("����������Ҫ�����λ�ã�\n");
			scanf("%d", &pos);
			Insert(&seq, pos, x);
			break;
		case REMOVE:
			fflush(stdin);
			printf("������Ҫɾ����Ԫ��\n");
			scanf("%d", &x);
			Remove(&seq, x);
			break;
		case REMOVEALL:
			fflush(stdin);
			printf("������Ҫɾ����Ԫ��\n");
			scanf("%d", &x);
			RemoveAll(&seq, x);
			break;
		case BUBBLESORT:
			BubbleSort(&seq);
			break;
		case SELECTSORT:
			SelectSort(&seq);
			break;
		case INSERTIONSORT:
			InsertionSort(&seq);
			break;
		case ERASE:
			fflush(stdin);
			printf("����������Ҫɾ��Ԫ�ص�λ��");
			scanf("%d", &pos);
			Erase(&seq,pos);
			break;
		case BINARYSEARCH:
			printf("������Ҫ���ֲ��ҵ�Ԫ��\n");
			fflush(stdin);
			scanf("%d", &x);
			search = BinarySearch(&seq, x);
			printf("%d���ڵ�λ���ǣ�%d", x, search);
			break;
		case EXIT:
			DestorySeqlist(&seq);
			input = 0;
			break;
		case PRINTFSEQLIST:
			PrintSeqlist(&seq);
			break;
		default:
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
#define _CRT_SECURE_NO_WARNINGS 1


#include"seqlist.h"
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
		printf("请选择:");
		scanf("%d", &input);
		fflush(stdin);
		switch (input)
		{
		case INIT:
			InitSqlist(&seq);
			break;
		case PUSHBACK:
			fflush(stdin);
			printf("请输入你所要尾部push的元素：\n");
			scanf("%d", &x);
			PushBack(&seq, x);
			break;
		case POPBACK:
			PopBack(&seq);
			break;
		case PUSHFRONT:
			fflush(stdin);
			printf("请输入你所要头部push的元素：\n");
			scanf("%d", &x);
			PushFront(&seq, x);
			break;
		case POPFRONT:
			PopFront(&seq);
			break;
		case INSERT:
			fflush(stdin);
			printf("请输入你所要插入的元素：\n");
			scanf("%d", &x);
			fflush(stdin);
			printf("请输入你所要插入的位置：\n");
			scanf("%d", &pos);
			Insert(&seq, pos, x);
			break;
		case REMOVE:
			fflush(stdin);
			printf("请输入要删除的元素\n");
			scanf("%d", &x);
			Remove(&seq, x);
			break;
		case REMOVEALL:
			fflush(stdin);
			printf("请输入要删除的元素\n");
			scanf("%d", &x);
			RemoveAll(&seq, x);
			break;
		case SORT:
			Sort(&seq);
			break;
		case BINARYSEARCH:
			fflush(stdin);
			printf("请输入要二分查找的元素\n");
			scanf("%d", &x);
			search = BinarySearch(&seq, x);
			printf("%d所在的位置是：%d", x, search);
			break;
		case EXIT:
			InitSqlist(&seq);
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
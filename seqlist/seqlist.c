#define _CRT_SECURE_NO_WARNINGS 1

#include"seqlist.h"


void meau()
{
	printf("$$$$$$$$$$$$$$   SEQLIST  $$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$$$  1.init       2.push_back      $$$\n");
	printf("$$$  3.pop_back   4.push_front     $$$\n");
	printf("$$$  5.pop_front  6.insert         $$$\n");
	printf("$$$  7.remove     8.removeall      $$$\n");
	printf("$$$  9.sort       10.binary_search $$$\n");
	printf("$$$  11.print     12.EXIT          $$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

}
//打印顺序表
void PrintSeqlist(pSeqlist pSeq)
{
	int i = 0;
	for (i = 0; i < pSeq->sz; i++)
	{
		printf("%3d", pSeq->data[i]);
	}
	printf("\n");
}
//初始化
void InitSqlist(pSeqlist pSeq)
{
	pSeq->sz = 0;
	memset(pSeq->data, 0, sizeof(datatype)*MAX_SIZE);
}
//尾插
void PushBack(pSeqlist pSeq, datatype x)
{
	if ((pSeq->sz) >= MAX_SIZE)
	{
		printf("顺序表已经满了。\n");
		return;
	}
	pSeq->data[pSeq->sz] = x;
	pSeq->sz++;
}
//尾出
void PopBack(pSeqlist pSeq)
{
	if (pSeq->sz <= 0)
	{
		printf("顺序表已空\n");
		return;
	}
	pSeq->sz--;
}
//头插
void PushFront(pSeqlist pSeq, datatype x)
{
	if ((pSeq->sz) >= MAX_SIZE)
	{
		printf("顺序表已经满了。\n");
		return;
	}

	for (int i = 0; i < pSeq->sz; i++)
	{
		pSeq->data[i + 1] = pSeq->data[i];
	}
	pSeq->data[0] = x;
	pSeq->sz++;
}
//头出
void PopFront(pSeqlist pSeq)
{
	if (pSeq->sz <= 0)
	{
		printf("顺序表已空\n");
		return;
	}
	for (int i = 0; i < pSeq->sz; i++)
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->sz--;
}
//插入
void Insert(pSeqlist pSeq, int pos, datatype x)
{
	if ((pSeq->sz) >= MAX_SIZE)
	{
		printf("顺序表已经满了。\n");
		return;
	}
	for (int i = pos; i < pSeq->sz; i++)
	{
		pSeq->data[i + 1] = pSeq->data[i];
	}
	pSeq->data[pos] = x;
	pSeq->sz++;
}
//删除第一个元素为x的元素
void Remove(pSeqlist pSeq, datatype x)
{
	if (pSeq->sz <= 0)
	{
		printf("顺序表已空,无法删除\n");
		return;
	}
	for (int i = 0; i < pSeq->sz; i++)
	{
		if (pSeq->data[i] == x)
		{
			for (int j = i; j < pSeq->sz - i; j++)
			{
				pSeq->data[j] = pSeq->data[j + 1];
			}
			pSeq->sz--;
			return;
		}
	}

}
//删除所有元素为x的元素
void RemoveAll(pSeqlist pSeq, datatype x)
{
	if (pSeq->sz <= 0)
	{
		printf("顺序表已空,无法删除\n");
		return;
	}
	for (int i = 0; i < pSeq->sz; i++)
	{
		if (pSeq->data[i] == x)
		{
			for (int j = i; j < pSeq->sz ; j++)
			{
				pSeq->data[j] = pSeq->data[j + 1];
			}
			pSeq->sz--;
		}
	}
}
//排序
void Sort(pSeqlist pSeq)
{

	char ch = 0;
	int i = 0;
	int j = 0;
	if (pSeq->sz <= 0)
	{
		printf("顺序表已空,无法排序\n");
		return;
	}
	printf("请选择排序类型（>:从大到小），（<:从小到大）：\n");
	fflush(stdin);
	scanf("%c", &ch);
	
	switch (ch)
	{
	case'>':
		for (i = 0; i < pSeq->sz-1; i++)
		{
			for (j = 0; j < pSeq->sz - i - 1; j++)
			{
				if (pSeq->data[j] < pSeq->data[j + 1])
				{
					int tmp = pSeq->data[j];
					pSeq->data[j] = pSeq->data[j + 1];
					pSeq->data[j + 1] = tmp;
				}
			}
		}
		break;
	case'<':
		for (i = 0; i < pSeq->sz - 1; i++)
		{
			for (j = i; j < pSeq->sz - i - 1; j++)
			{
				if (pSeq->data[j] > pSeq->data[j + 1])
				{
					int tmp = pSeq->data[j];
					pSeq->data[j] = pSeq->data[j + 1];
					pSeq->data[j + 1] = tmp;
				}
			}
		}
		break;
	default:
		printf("所给出排序类型有问题！\n");
		break;
	}
}
//二分查找
int BinarySearch(pSeqlist pSeq, datatype x)
{
	int left = 0;
	int right = pSeq->sz - 1;
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) >> 1;
		if (pSeq->data[mid] < x)
		{
			left = mid + 1;
		}
		else if (pSeq->data[mid]>x)
		{
			right = mid - 1;
		}
		else
			return mid;
	}
	return -1;

}



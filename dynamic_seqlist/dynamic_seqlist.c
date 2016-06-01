#define _CRT_SECURE_NO_WARNINGS 1

#include"dynamic_seqlist.h"

void meau()
{
	printf("$$$$$$$$$$$$$$    SEQLIST    $$$$$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$￥$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$$$  1.init              2.push_back      $$$\n");
	printf("$$$  3.pop_back          4.push_front     $$$\n");
	printf("$$$  5.pop_front         6.insert         $$$\n");
	printf("$$$  7.remove            8.removeall      $$$\n");
	printf("$$$  9.bubblesort        10.selectsort    $$$\n");
	printf("$$$  11.insertionsort    12.earse         $$$\n");
	printf("$$$  13.binarysearch     14.printseqlist  $$$\n");
	printf("$$$                       0.EXIT          $$$\n");
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

}

void InitSqlist(pSeqlist pseq)
{
	pseq->data = (datatype *)malloc(sizeof(datatype)*INIT_SIZE);
	if (NULL == pseq->data)
	{
		perror("out of memory");
		exit(-1);
	}
	pseq->size = 0;
	pseq->capacity = INIT_SIZE;
}

void DestorySeqlist(pSeqlist pSeq)
{
	free(pSeq->data);
	pSeq->data = NULL;
	pSeq->size = 0;
	pSeq->capacity = 0;
}

void PrintSeqlist(pSeqlist pSeq)
{
	int i = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		printf("%3d", pSeq->data[i]);
	}
	printf("\n");
}
void check(pSeqlist pSeq)
{
	datatype *tmp = NULL;
	if (pSeq->size == pSeq->capacity)
	{
		tmp = (datatype *)realloc(pSeq->data, sizeof(datatype)*(pSeq->size + CAPACITY_SIZE));
		if (tmp == NULL)
		{
			perror("out of memory");
			exit(-1);
		}
		else
		{
			pSeq->data = tmp;
			pSeq->capacity += CAPACITY_SIZE;
		}
	}
}
void PushBack(pSeqlist pSeq, datatype x)
{
	check(pSeq);
	pSeq->data[pSeq->size] = x;
	pSeq->size++;
}

void PopBack(pSeqlist pSeq)
{
	if (pSeq->size <= 0)
	{
		printf("顺序表已空\n");
		return;
	}
	pSeq->size--;
}
void PushFront(pSeqlist pSeq, datatype x)
{
	check(pSeq);
	for (int i = pSeq->size; i >= 0; i--)
	{
		pSeq->data[i + 1] = pSeq->data[i];
	}
	pSeq->data[0] = x;
	pSeq->size++;
}

void PopFront(pSeqlist pSeq)
{
	if (pSeq->size <= 0)
	{
		printf("顺序表已空\n");
		return;
	}
	for (int i = 0; i < pSeq->size; i++)
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->size--;
}
void Insert(pSeqlist pSeq, int pos, datatype x)
{
	check(pSeq);
	for (int i = pSeq->size; i >= pos; i--)
	{
		pSeq->data[i + 1] = pSeq->data[i];
	}
	pSeq->data[pos] = x;
	pSeq->size++;

}
void Remove(pSeqlist pSeq, datatype x)
{
	if (pSeq->size <= 0)
	{
		printf("顺序表已空,无法删除\n");
		return;
	}
	for (int i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] == x)
		{
			for (int j = i; j < pSeq->size - i; j++)
			{
				pSeq->data[j] = pSeq->data[j + 1];
			}
			pSeq->size--;
			return;
		}
	}
}
void RemoveAll(pSeqlist pSeq, datatype x)
{
	if (pSeq->size <= 0)
	{
		printf("顺序表已空,无法删除\n");
		return;
	}
	for (int i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] == x)
		{
			for (int j = i; j <pSeq->size; j++)
			{
				pSeq->data[j] = pSeq->data[j + 1];
			}
			pSeq->size--;
		}
	}
}
void BubbleSort(pSeqlist pSeq)
{
	
	char ch = 0;
	int i = 0;
	int j = 0;
	if (pSeq->size <= 0)
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
		for (i = 0; i < pSeq->size - 1; i++)
		{
			for (j = 0; j < pSeq->size - i - 1; j++)
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
		for (i = 0; i < pSeq->size - 1; i++)
		{
			for (j = i; j < pSeq->size - i - 1; j++)
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
	};
}
void SelectSort(pSeqlist pSeq)
{
	datatype min = 0;
	int i = 0;
	int j = 0;
	if (pSeq->size <= 0)
	{
		printf("顺序表已空,无法排序\n");
		return;
	}
	for (i = 0; i < pSeq->size - 1; i++)
	{
		min = i ;
		for (j = i + 1; j < pSeq->size; j++)
		{
			if (pSeq->data[min]>pSeq->data[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			datatype tmp = pSeq->data[i];
			pSeq->data[i] = pSeq->data[min];
			pSeq->data[min] = tmp;
		}
	}
}
void InsertionSort(pSeqlist pSeq)
{
	int i = 0;
	int j = 0;
	if (pSeq->size <= 0)
	{
		printf("顺序表已空,无法排序\n");
		return;
	}
	for (i = 1; i < pSeq->size; i++)
	{
		datatype tmp = pSeq->data[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (pSeq->data[j]>tmp)
			{
				pSeq->data[j + 1] = pSeq->data[j];
			}
			else
			{
				break;
			}
		}
		pSeq->data[j + 1] = tmp;
	}

}
void Erase(pSeqlist pSeq, int pos)
{
	int i = 0;
	if (pSeq->size <= 0)
	{
		printf("顺序表已空,无法删除\n");
		return;
	}
	else if (pos<0 || pos>=pSeq->size)
	{
		printf("输入位置不合法");
		return;
	}
	for (i = pos; i <pSeq->size-1; i++)
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->size--;
}
int BinarySearch(pSeqlist pSeq, datatype x)
{
	int left = 0;
	int right = pSeq->size - 1;
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
	return -1;;
}

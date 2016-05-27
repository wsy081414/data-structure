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
//��ӡ˳���
void PrintSeqlist(pSeqlist pSeq)
{
	int i = 0;
	for (i = 0; i < pSeq->sz; i++)
	{
		printf("%3d", pSeq->data[i]);
	}
	printf("\n");
}
//��ʼ��
void InitSqlist(pSeqlist pSeq)
{
	pSeq->sz = 0;
	memset(pSeq->data, 0, sizeof(datatype)*MAX_SIZE);
}
//β��
void PushBack(pSeqlist pSeq, datatype x)
{
	if ((pSeq->sz) >= MAX_SIZE)
	{
		printf("˳����Ѿ����ˡ�\n");
		return;
	}
	pSeq->data[pSeq->sz] = x;
	pSeq->sz++;
}
//β��
void PopBack(pSeqlist pSeq)
{
	if (pSeq->sz <= 0)
	{
		printf("˳����ѿ�\n");
		return;
	}
	pSeq->sz--;
}
//ͷ��
void PushFront(pSeqlist pSeq, datatype x)
{
	if ((pSeq->sz) >= MAX_SIZE)
	{
		printf("˳����Ѿ����ˡ�\n");
		return;
	}

	for (int i = 0; i < pSeq->sz; i++)
	{
		pSeq->data[i + 1] = pSeq->data[i];
	}
	pSeq->data[0] = x;
	pSeq->sz++;
}
//ͷ��
void PopFront(pSeqlist pSeq)
{
	if (pSeq->sz <= 0)
	{
		printf("˳����ѿ�\n");
		return;
	}
	for (int i = 0; i < pSeq->sz; i++)
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->sz--;
}
//����
void Insert(pSeqlist pSeq, int pos, datatype x)
{
	if ((pSeq->sz) >= MAX_SIZE)
	{
		printf("˳����Ѿ����ˡ�\n");
		return;
	}
	for (int i = pos; i < pSeq->sz; i++)
	{
		pSeq->data[i + 1] = pSeq->data[i];
	}
	pSeq->data[pos] = x;
	pSeq->sz++;
}
//ɾ����һ��Ԫ��Ϊx��Ԫ��
void Remove(pSeqlist pSeq, datatype x)
{
	if (pSeq->sz <= 0)
	{
		printf("˳����ѿ�,�޷�ɾ��\n");
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
//ɾ������Ԫ��Ϊx��Ԫ��
void RemoveAll(pSeqlist pSeq, datatype x)
{
	if (pSeq->sz <= 0)
	{
		printf("˳����ѿ�,�޷�ɾ��\n");
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
//����
void Sort(pSeqlist pSeq)
{

	char ch = 0;
	int i = 0;
	int j = 0;
	if (pSeq->sz <= 0)
	{
		printf("˳����ѿ�,�޷�����\n");
		return;
	}
	printf("��ѡ���������ͣ�>:�Ӵ�С������<:��С���󣩣�\n");
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
		printf("�������������������⣡\n");
		break;
	}
}
//���ֲ���
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



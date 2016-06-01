#define _CRT_SECURE_NO_WARNINGS 1
#ifndef __DYNAMIC_SEQLIST_H__
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>


#define INIT_SIZE 3
#define CAPACITY_SIZE 3
typedef int datatype;

typedef struct seqlist
{
	datatype *data;
	int size;
	int capacity;
}Seqlist,*pSeqlist;


static enum seq
{
	EXIT,
	INIT,
	PUSHBACK,
	POPBACK,
	PUSHFRONT,
	POPFRONT,
	INSERT,
	REMOVE,
	REMOVEALL,
	BUBBLESORT,
	SELECTSORT,
	INSERTIONSORT,
	ERASE,
	BINARYSEARCH,
	PRINTFSEQLIST

};

void PrintSeqlist(pSeqlist pSeq);
void InitSqlist(pSeqlist pSeq);
void DestorySeqlist(pSeqlist pSeq);
void PushBack(pSeqlist pSeq, datatype x);
void PopBack(pSeqlist pSeq);
void PushFront(pSeqlist pSeq, datatype x);
void PopFront(pSeqlist pSeq);
void Insert(pSeqlist pSeq, int pos, datatype x);
void Remove(pSeqlist pSeq, datatype x);
void RemoveAll(pSeqlist pSeq, datatype x);
void BubbleSort(pSeqlist pSeq);
void SelectSort(pSeqlist pSeq);
void InsertionSort(pSeqlist pSeq);
void Erase(pSeqlist pSeq, int pos);
int BinarySearch(pSeqlist pSeq, datatype x);


void meau();


#endif // !__DYNAMIC_SEQLIST_H__

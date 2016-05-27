#define _CRT_SECURE_NO_WARNINGS 1


#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#define MAX_SIZE 100 //顺序表最大大小

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int datatype;
typedef struct seqlist
{
	datatype data[MAX_SIZE];
	int sz;
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
	SORT,
	BINARYSEARCH,
	PRINTFSEQLIST

};

void PrintSeqlist(pSeqlist pSeq);
void InitSqlist(pSeqlist pSeq);
void PushBack(pSeqlist pSeq, datatype x);
void PopBack(pSeqlist pSeq);
void PushFront(pSeqlist pSeq,datatype x);
void PopFront(pSeqlist pSeq);
void Insert(pSeqlist pSeq,int pos,datatype x);
void Remove(pSeqlist pSeq,datatype x);
void RemoveAll(pSeqlist pSeq,datatype x);
void Sort(pSeqlist pSeq);
int BinarySearch(pSeqlist pSeq,datatype x);

void meau();

void Exit_seq();
#endif //！__SEQLIST_H__
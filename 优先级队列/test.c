#define _CRT_SECURE_NO_WARNINGS 1
#include"priorityqueue.h"

void test1()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	PriorityQueue<int, Greater<int>> p1(a, 10);

	
}

int main()
{ 
	test1();
	system("pause");
	return 0;
}
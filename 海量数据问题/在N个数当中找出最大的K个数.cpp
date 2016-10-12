

#define _CRT_SECURE_NO_WARNINGS 1
#define N 10000
#define K 10


#include<iostream>
#include<cstdlib>
#include<cassert>

//������Ҫע��Ѱ����С��K����Ҫ���ô�ѣ�Ѱ������K����Ҫ����С��
//ԭ����ֻ���������ſ��Կ��ٺͶѶ���Ԫ�ؽ��н�����Ȼ��������µ���
//��������½��ѣ������⸴�ӻ���

using namespace std;
template<typename T>
void Adjustdown(T *top, size_t root)
{
	assert(root < K);
	size_t parent = root;
	size_t child = parent * 2 + 1;
	while (parent<K)
	{
		if (child + 1 < K&&top[child + 1] < top[child])
		{
			child++;
		}
		if (child<K&&top[child]<top[parent])
		{
			std::swap(top[child], top[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

//ʱ�临�Ӷȣ����Ƚ����ѵ�ʱ�临�Ӷ��� K *logK
//����ĺ�ջ���ıȽ���(N-K)* logK
//����������N*logK
template<typename T>
void GetKNum(T *arr, T *top)
{
	assert(K < N);
	for (size_t i = 0; i < K; i++)
	{
		top[i] = arr[i];
	}
	for (int j = (K - 2) / 2; j >= 0; j--)
	{
		Adjustdown(top, j);
	}
	for (size_t i = K; i < N; i++)
	{
		if (arr[i]>top[0])
		{
			std::swap(arr[i], top[0]);
			Adjustdown(top, 0);
		}
	}
}
template<typename T>
void Print(T *top)
{
	for (size_t i=0; i < K; i++)
	{
		cout << top[i] << " ";

	}
	cout << endl;
}
void test1()
{
	int arr[N] = { 0 };
	int top[K] = { 0 };
	for (size_t i = 0; i < N; i++)
	{
		arr[i] = i;
	}
	GetKNum(arr, top);
	print(top);
}

int main()
{
	test1();
	system("pause");
	return 0;
}
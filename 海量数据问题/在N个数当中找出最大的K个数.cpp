

#define _CRT_SECURE_NO_WARNINGS 1
#define N 10000
#define K 10


#include<iostream>
#include<cstdlib>
#include<cassert>

//在这里要注意寻找最小的K个数要利用大堆，寻找最大的K个数要利用小堆
//原因是只有这样，才可以快速和堆顶的元素进行交换，然后进行向下调整
//否则会重新建堆，把问题复杂化。

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

//时间复杂度：首先建立堆的时间复杂度是 K *logK
//后面的和栈顶的比较是(N-K)* logK
//所以最后就是N*logK
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
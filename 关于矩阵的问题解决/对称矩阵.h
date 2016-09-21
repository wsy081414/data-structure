#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include<iostream>
#include<cstdlib>

using namespace std;
template <typename T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* a, size_t size);
	~SymmetricMatrix();
	T& Access(size_t i, size_t j); //访问矩阵
	void Display();		//显示矩阵
protected:
	size_t _size;	//设置一维数组大小
	T* _a;	//保存对称矩阵所需要的数组
	size_t _n;	//对称矩阵的维数

};
template<typename T>
SymmetricMatrix<T>::SymmetricMatrix(T* a, size_t size)
:_size((size*(size + 1)) / 2)
, _a(new T[(size*(size + 1)) / 2])
, _n(size)
{
	int index = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i >= j)
			{
				_a[index] = a[i*size + j];
				index++;
			}
			else
			{
				break;
			}

		}
	}
}
template<typename T>
SymmetricMatrix<T>::~SymmetricMatrix()
{
	if (_a)
	{
		delete[] _a;
	}
}
template<typename T>
T& SymmetricMatrix<T>::Access(size_t i, size_t j)
{
	if (i < j)
	{
		std::swap(i, j);
	}
	return _a[(i*(i + 1)) / 2 + j];
}
template<typename T>
void SymmetricMatrix<T>::Display()
{
	for (size_t i = 0; i < _n; i++)
	{
		for (size_t j = 0; j < _n; j++)
		{
			if (i < j)
			{
				cout << _a[(j*(j + 1)) / 2 + i] << " ";
			}
			else
			{
				cout << _a[(i*(i + 1)) / 2 + j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;

}
void TestSymmetricMatrix()
{
	int a[5][5] = {
		{ 0, 1, 2, 3, 4 },
		{ 1, 0, 1, 2, 3 },
		{ 2, 1, 0, 1, 2 },
		{ 3, 2, 1, 0, 1 },
		{ 4, 3, 2, 1, 0 }
	};
	SymmetricMatrix<int > s((int *)a, 5);
	cout << s.Access(1, 3) << endl;
	s.Display();

}

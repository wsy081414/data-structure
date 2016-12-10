
#define _CRT_SECURE_NO_WARNINGS 1

#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

template<typename T>
struct Triple
{
	Triple()
	{

	}
	Triple(const T& d, size_t row, size_t col)
		:_value(d)
		, _row(row)
		, _col(col)
	{}
	T _value;
	size_t _row;
	size_t _col;
};

template<typename T>
class SparseMatrix
{
public:
	SparseMatrix(T* a, size_t row, size_t col, const T& invaild);
	SparseMatrix()
	{
	}
	void display();
	SparseMatrix<T> transport();
	SparseMatrix<T> Fasttransport();


protected:
	size_t _rowsize;
	size_t _colsize;
	vector<Triple<T> >_a;
	T _invaild;
};

template<typename T>
SparseMatrix<T>::SparseMatrix(T* a, size_t row, size_t col, const T& invaild)
:_rowsize(row)
, _colsize(col)
, _invaild(invaild)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			//行乘上列数
			if (a[i*_colsize + j] != _invaild)
			{
				Triple<T> tmp(a[i*_colsize + j], i, j);
				_a.push_back(tmp);

			}
		}

	}
}
template<typename T>
void SparseMatrix<T>::display()
{
	int index = 0;
	for (size_t i = 0; i < _rowsize; i++)
	{
		for (size_t j = 0; j < _colsize; j++)
		{
			if (index != _a.size() && _a[index]._row == i&&_a[index]._col == j)
			{
				cout << _a[index]._value << " ";
				index++;
			}
			else
			{
				cout << _invaild << " ";
			}
		}
		cout << endl;
	}
}

template<typename T>
SparseMatrix<T> SparseMatrix<T>::transport()
{
	SparseMatrix<T> tmp;
	tmp._colsize = _rowsize;
	tmp._rowsize = _colsize;
	tmp._invaild = _invaild;
	tmp._a.reserve(_a.size());
	for (size_t i = 0; i < _colsize; i++)
	{
		for (size_t index = 0; index < _a.size(); index++)
		{
			if (_a[index]._col == i)
			{
				Triple<T> st(_a[index]._value, _a[index]._col, _a[index]._row);
				tmp._a.push_back(st);
			}

		}

	}
	return tmp;
}


template<typename T>
SparseMatrix<T> SparseMatrix<T>::Fasttransport()
{
	SparseMatrix<T> tmp;
	tmp._colsize = _rowsize;
	tmp._rowsize = _colsize;
	tmp._invaild = _invaild;
	size_t *count = new size_t[_colsize];
	memset(count, 0, sizeof(size_t)*_colsize);
	size_t *start = new size_t[_colsize];
	tmp._a.resize(_a.size());
	size_t index = 0;
	while (index<_a.size())
	{
		count[_a[index]._col]++;
		index++;
	}
	start[0] = 0;
	for (size_t i = 1; i < _colsize; i++)
	{
		start[i] = start[i - 1] + count[i - 1];

	}
	for (index = 0; index < _a.size(); index++)
	{
		Triple<T> st(_a[index]._value, _a[index]._col, _a[index]._row);


		tmp._a[start[_a[index]._col]++] = st;
	}

	delete[] start;
	delete[] count;
	return tmp;
}

void test()
{
	int a[4][5] =
	{
		{ 1, 0, 0, 0, 0 },
		{ 0, 2, 0, 3, 0 },
		{ 0, 0, 4, 0, 1 },
		{ 0, 4, 1, 0, 0 }
	};

	SparseMatrix<int > sm((int *)a, 4, 5, 0);
	sm.display();
	cout << endl;

	SparseMatrix<int > t;


	t = sm.Fasttransport();
	t.display();

}

int main()
{


	test();

	system("pause");
	return 0;
}
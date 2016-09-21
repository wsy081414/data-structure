

#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

template<typename T>
struct Triple
{
	Triple(const T& d,size_t row,size_t col)
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
	void display();


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
			if (a[i*_rowsize + j] != _invaild)
			{
				Triple<T> tmp(a[i*_rowsize + j],i, j);
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
				cout << _a[index]._value<<" ";
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

void testSparseMatrix()
{
	int a[4][5] = 
	{
		{1,0,0,0,0},
		{0,2,0,3,0},
		{0,0,4,0,1},
		{0,4,1,0,0}
	};

	SparseMatrix<int > sm((int *)a, 4, 5, 0);

	sm.display();
}


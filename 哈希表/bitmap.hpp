#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cassert>
using namespace std;


//ʵ��λͼ��ʵ�ֹ��̵��У��Ѵ�����������ÿ��������һ��λ����0��1����ʾ״̬��

class BitMap
{
public:
	BitMap(const size_t& range)
	{
		//�������ر�Ҫע�����ȼ������⣬>>�����ȼ�Ҫ��+���ȼ�Ҫ�͡�
		_bitmap.resize((range >> 5) + 1);
	}
	//����λ״̬Ϊ1
	void Set(const size_t& x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		_bitmap[index] |= (1 << num);
	}
	//����λ״̬
	void Reset(const size_t& x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		_bitmap[index] &= (~(1 << num));
	}
	//����λ״̬
	bool test(const size_t& x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;

		return _bitmap[index] & (1 << num);
	}
protected:
	std::vector<size_t> _bitmap;
};





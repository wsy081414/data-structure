#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include<cassert>
using namespace std;


//实现位图，实现过程当中，把大数据整数，每个数看作一个位，用0，1来表示状态。

class BitMap
{
public:
	BitMap(const size_t& range)
	{
		//在这里特别要注意优先级的问题，>>的优先级要比+优先级要低。
		_bitmap.resize((range >> 5) + 1);
	}
	//设置位状态为1
	void Set(const size_t& x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		_bitmap[index] |= (1 << num);
	}
	//重置位状态
	void Reset(const size_t& x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;
		_bitmap[index] &= (~(1 << num));
	}
	//返回位状态
	bool test(const size_t& x)
	{
		size_t index = x >> 5;
		size_t num = x % 32;

		return _bitmap[index] & (1 << num);
	}
protected:
	std::vector<size_t> _bitmap;
};





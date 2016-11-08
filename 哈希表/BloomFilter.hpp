#define _CRT_SECURE_NO_WARNINGS 1

#pragma once
#include<iostream>
#include<cstdlib>
#include<cassert>
#include"BitMap.hpp"
using namespace std;

template <typename K>
struct _Funcpos1
{
	size_t BKDRHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
			// 有人说将乘法分解为位运算及加减法可以提高效率，如将上式表达为：hash = hash << 7 + hash << 1 + hash + ch;  
			// 但其实在Intel平台上，CPU内部对二者的处理效率都是差不多的，  
			// 我分别进行了100亿次的上述两种运算，发现二者时间差距基本为0（如果是Debug版，分解成位运算后的耗时还要高1/3）；  
			// 在ARM这类RISC系统上没有测试过，由于ARM内部使用Booth's Algorithm来模拟32位整数乘法运算，它的效率与乘数有关：  
			// 当乘数8-31位都为1或0时，需要1个时钟周期  
			// 当乘数16-31位都为1或0时，需要2个时钟周期  
			// 当乘数24-31位都为1或0时，需要3个时钟周期  
			// 否则，需要4个时钟周期  
			// 因此，虽然我没有实际测试，但是我依然认为二者效率上差别不大          
		}
		return hash;
	}

	size_t operator()(const string& key)
	{
		return BKDRHash(key.c_str());
	}
};
template<typename K>
struct _Funcpos2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return SDBMHash(key.c_str());
	}
};
template<typename K>
struct _Funcpos3
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};
template<typename K>
struct _Funcpos4
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};

template<typename K>
struct _Funcpos5
{
	size_t RSHash(const char *str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
	size_t operator()(const string& key)
	{
		return RSHash(key.c_str());
	}
};

template<typename K = string, 
	typename Funcpos1 = _Funcpos1<K>,
	typename Funcpos2 = _Funcpos2<K>,
	typename Funcpos3 = _Funcpos3<K>,
	typename Funcpos4 = _Funcpos3<K>,
	typename Funcpos5 = _Funcpos3<K> >
class BloomFilter
{
public:
	//构造函数
	BloomFilter(const size_t range)
		: _size(range)
		, _bl(range)
	{	
	}
	//布隆过滤器进行设置，根据原理，对通过字符串函数所计算的K个位进行设置状态。
	 void Set(const K& key)
	{
		size_t index1 = Funcpos1()(key.c_str())%_size;
		size_t index2 = Funcpos2()(key.c_str())%_size;
		size_t index3 = Funcpos3()(key.c_str())%_size;
		size_t index4 = Funcpos4()(key.c_str())%_size;
		size_t index5 = Funcpos5()(key.c_str())%_size;

		_bl.Set(index1);
		cout << index1 << endl;

		_bl.Set(index2);
		cout << index2 << endl;

		_bl.Set(index3);
		cout << index3 << endl;

		_bl.Set(index4);
		cout << index4 << endl;

		_bl.Set(index5);
		cout << index5 << endl<<endl;

	}

	
	 bool Test(const K& key)
	 {
		 size_t index1 = Funcpos1()(key.c_str() )% _size;
		 if (_bl.test(index1) == 0)
		 {
			 return false;
		 }
		 size_t index2 = Funcpos2()(key.c_str()) % _size;
		 if (_bl.test(index2) == 0)
		 {
			 return false;
		 }
		 size_t index3 = Funcpos3()(key.c_str()) % _size;
		 if (_bl.test(index3) == 0)
		 {
			 return false;
		 }
		 size_t index4 = Funcpos4()(key.c_str() )% _size;
		 if (_bl.test(index4) == 0)
		 {
			 return false;
		 }
		 size_t index5 = Funcpos5()(key.c_str() )% _size;
		 if (_bl.test(index5) == 0)
		 {
			 return false;
		 }
		 return true;
	 }

protected:
	BitMap _bl;
	size_t _size;
};




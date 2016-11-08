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
			hash = hash * 131 + ch;   // Ҳ���Գ���31��131��1313��13131��131313..  
			// ����˵���˷��ֽ�Ϊλ���㼰�Ӽ����������Ч�ʣ��罫��ʽ���Ϊ��hash = hash << 7 + hash << 1 + hash + ch;  
			// ����ʵ��Intelƽ̨�ϣ�CPU�ڲ��Զ��ߵĴ���Ч�ʶ��ǲ��ģ�  
			// �ҷֱ������100�ڴε������������㣬���ֶ���ʱ�������Ϊ0�������Debug�棬�ֽ��λ�����ĺ�ʱ��Ҫ��1/3����  
			// ��ARM����RISCϵͳ��û�в��Թ�������ARM�ڲ�ʹ��Booth's Algorithm��ģ��32λ�����˷����㣬����Ч��������йأ�  
			// ������8-31λ��Ϊ1��0ʱ����Ҫ1��ʱ������  
			// ������16-31λ��Ϊ1��0ʱ����Ҫ2��ʱ������  
			// ������24-31λ��Ϊ1��0ʱ����Ҫ3��ʱ������  
			// ������Ҫ4��ʱ������  
			// ��ˣ���Ȼ��û��ʵ�ʲ��ԣ���������Ȼ��Ϊ����Ч���ϲ�𲻴�          
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
		if (!*str)        // �����ɱ�����ӣ��Ա�֤���ַ������ع�ϣֵ0  
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
	//���캯��
	BloomFilter(const size_t range)
		: _size(range)
		, _bl(range)
	{	
	}
	//��¡�������������ã�����ԭ����ͨ���ַ��������������K��λ��������״̬��
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




#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;
enum Status
{
	EMPTY,
	DELETE,
	EXIST
};
template<typename K,typename V>
struct HashNode
{
	HashNode() = default;
	HashNode(const K &key = K(), const V&value = V())//给出默认实参
		: _key(key)
		, _value(value)
		, _status(EMPTY)
	{
	}

	K _key;
	V _value;
	Status _status;

};


template<typename K,typename V>
class Hashtable
{
	typedef HashNode<K, V> Node;
	typedef Hashtable<K, V> HashTable;
	
public:
	Hashtable()
		:_size(0) 
	{
		_ht.resize(_PrimeList[0]);
	}
	~Hashtable()
	{
		;
	}
	bool Insert(const K& key, const V& value)
	{
		//进行是否增容的检查。
		_CheckCapacity();
		size_t index = _HashFunc(key);
		while (_ht[index]._status==EXIST)
		{
			if (_ht[index]._key == key)
				return false;
			++index;
			if (index == _size)
				index = 0;
		}
		_size++;
		_ht[index]._status = EXIST;
		_ht[index]._key = key;
		_ht[index]._value = value;
		return true;
	}
	bool Delete(const K& key)
	{
		size_t index = _HashFunc(key);
		size_t pos = index;
		while (_ht[index]._status != EMPTY)
		{
			if (_ht[index]._key == key)
			{
				_ht[index]._status = DELETE;
				_size--;
				return true;
			}
			++index;
			if (pos == index)
			{
				break;
			}
			
		}
		return false;	
	}
	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);
		size_t pos = index;
		while (_ht[index]._status != EMPTY)
		{
			if (_ht[index]._key == key)
			{
				return &_ht[index];
			}
			index++;
			if (pos == index)
			{
				break;
			}
		}
		return NULL;
	}
protected:
	void _CheckCapacity()
	{
		//判断负载因子是否小于0.8
		if (_ht.size()==0 ||_size * 10 / _ht.size() >= 8)
		{
			size_t newindex = 0;
			
			size_t newsize = _PrimeList[newindex];
			HashTable tmp;
			tmp._ht.resize(newsize);
			for (size_t i = 0; i < _size; i++)
			{
				if (_ht[i]._status== EXIST)
				{
					tmp.Insert(_ht[i]._key,_ht[i]._value);
				}
			}
			this->Swap(tmp);
		}
		else
			return;
	}
	void Swap(Hashtable & t)
	{
		_ht.swap(t._ht);
		swap(_size, t._size);
	}
	size_t _HashFunc(const K& key)
	{
		return key%_ht.size();
	}
	size_t GetNewSize()
	{
		const int _PrimeSize = 28;

		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		}
		for (size_t i = 0; i < _PrimeSize; ++i)
		{
			if (_ht.size() < _PrimeList[i])
			{
				newindex = i;
				break;
			}
		}

	}
protected:
	std::vector<Node> _ht;
	size_t _size;
	
};


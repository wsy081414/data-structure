#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>



using namespace std;

namespace open
{
	enum Status
	{
		EMPTY,
		DELETE,
		EXIST
	};

	template<typename K, typename V>
	struct HashNode
	{

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
	template<typename K>
	struct _Hashfunc
	{
		size_t operator ()(const K &key)
		{
			return key;
		}
	};
	template<>
	struct _Hashfunc<string>
	{
		static size_t BKDRHash(const char*str)
		{
			unsigned int seed = 131;// 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash*seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
		size_t operator ()(const string &key)
		{
			return BKDRHash(key.c_str());
		}
	};

	template<typename K, typename V, typename HashFunc = _Hashfunc<K>>
	class Hashtable
	{
		typedef HashNode<K, V> Node;
		typedef Hashtable<K, V, HashFunc> HashTable;

	public:
		Hashtable()
			:_size(0)
		{
			_ht.resize(GetNewSize());
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
			while (_ht[index]._status == EXIST)
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
				if (_ht[index]._key == key&&_ht[index]._status == EXIST)
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
			if (_ht.size() == 0 || _size * 10 / _ht.size() >= 8)
			{
				size_t newindex = 0;

				size_t newsize = GetNewSize();
				HashTable tmp;
				tmp._ht.resize(newsize);
				for (size_t i = 0; i < _size; i++)
				{
					if (_ht[i]._status == EXIST)
					{
						tmp.Insert(_ht[i]._key, _ht[i]._value);
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
			//利用仿函数进行处理其他像string和结构体带来的问题。
			HashFunc hf;
			return hf(key) % _ht.size();
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
			};
			for (size_t i = 0; i < _PrimeSize; ++i)
			{
				if (_ht.size() < _PrimeList[i])
				{
					return _PrimeList[i];
				}
			}
			return 0;
		}
	protected:
		std::vector<Node> _ht;
		size_t _size;

	};


}


namespace link
{
	template<typename K,typename V>
	struct KVNode
	{
		KVNode(const K& key=K(),const V& value=V())
		: _key(key)
		, _value(value)
		, _next(NULL)
		{}
		
		K _key;
		V _value;
		KVNode<K, V> *_next;
	};
	
	template<typename K>
	struct __Hashfunc
	{
		size_t operator() (const K &key)
		{
			return key;
		}
	};
	template<>
	struct __Hashfunc<string>
	{
		static size_t BKDRHash(const char*str)
		{
			unsigned int seed = 131;// 31 131 1313 13131 131313
			unsigned int hash = 0;
			while (*str)
			{
				hash = hash*seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
		size_t operator ()(const string &key)
		{
			return BKDRHash(key.c_str());
		}
	
	};

	template<typename K,typename V,typename HashFunc=__Hashfunc<K> >
	class HashTable
	{
		typedef KVNode<K, V> Node;
		typedef HashTable<K, V, HashFunc> Hashtable;


	public:
		HashTable()
			:_size(0)
		{
			_ht.resize(GetNewSize());
		}
		~HashTable()
		{	
			Node* cur = NULL;
			Node* del = NULL;
			for (size_t i = 0; i < _ht.size(); i++)
			{
				cur = _ht[i]; 
				if (_ht[i] == NULL)
					continue;
				while (cur)
				{
					del = cur;
					cur = cur->_next;
					delete del;
					del = NULL;
				}
			}

		}
		HashTable(const HashTable& ht)
		{
			_Copy();
		}
		bool Insert(const K& key,const V& value)
		{
			CheckCapacity();
			size_t index = Funcpos(key,_ht.size());
			
			Node* newnode = new Node(key,value);
			if (_ht[index])
			{
				Node* cur = _ht[index];
				while (cur)
				{
					if (cur->_key == key)
						return false;
					cur = cur->_next;
				}
			}
			_size++;
			newnode->_next = _ht[index];
			_ht[index] = newnode;

			return true;
		}
		bool Delete(const K& key)
		{
			size_t index = Funcpos(key,_ht.size());
			Node* cur = _ht[index];
			Node* prev = NULL;
			Node* del = NULL;
			while (cur)
			{
				if (cur->_key == key)
				{
					if (prev == NULL)
					{
						del = cur;
						delete cur;
						_ht[index] = NULL;
					}
					else
					{
						prev->_next = cur->_next;
						delete cur;
					}
					_size--;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}

			return false;
		}
		Node* Find(const K& key)
		{
			size_t index = Funcpos(key,_ht.size());
			Node *cur = _ht[index];
			if (_ht.empty())
			{
				return NULL;
			}
			
			while (cur)
			{
				if (cur->_key == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return NULL;
		}
	protected:
		void CheckCapacity()
		{
			if (_ht.size() == 0 || _size == _ht.size())
			{
				size_t newsize = GetNewSize();
				Hashtable tmp;
				tmp._ht.resize(newsize);
				Node* cur = NULL;
				Node* NewInsert = NULL;
				for (size_t i = 0; i < _ht.size(); i++)
				{
					//采用移动法进行交换
					//就是把原来的vector上面的节点进行移动到新的vector上面。
					cur = _ht[i];
					if (cur == NULL)
						continue;
					while (cur)
					{
						size_t newpos = Funcpos(cur->_key, tmp._ht.size());
						NewInsert = cur;
						cur = cur->_next;
						NewInsert->_next = tmp._ht[newpos];
						tmp._ht[newpos] = NewInsert;

					}
				
					_ht[i] = NULL;

				}
				NewSwap(tmp);
			}
		}
		void Getnew()
		{
			Hash
		
		}
		void NewSwap( Hashtable &h)
		{
			_ht.swap(h._ht);
			//std::swap(_size, h._size);
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
			};
			for (size_t i = 0; i < _PrimeSize; ++i)
			{
				if (_ht.size() < _PrimeList[i])
				{
					return _PrimeList[i];
				}
			}
			return 0;
		}
		size_t Funcpos(const K& key,const size_t &size)
		{
			HashFunc h;
			return h(key) % size;
		}
	protected:
		std::vector<Node*> _ht;
		size_t _size;

	};



}

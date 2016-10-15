#define _CRT_SECURE_NO_WARNINGS 1


#pragma once
#include<iostream>
#include<cstdlib>
#include"heap.h"
using namespace std;


template<typename T>
struct HuffmanTreeNode
{
	typedef HuffmanTreeNode<T> Node;
	HuffmanTreeNode(const T& weight =0)
		:_left(NULL)
		, _right(NULL)
		, _wight(weight)
	{}

	Node *_left;
	Node *_right;
	Node *_parent;
	size_t _wight;
};


template<typename T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;

public:
	HuffmanTree()=default;
	HuffmanTree(const T* arr, size_t size)
	{
		assert(arr);
		_CreateHuffmanTree(arr, size);


	}
protected:
	void _CreateHuffmanTree(const T* arr, size_t size)
	{
		assert(arr);
		
		struct NodeCompare
		{
			bool operator ()(const Node* a,const Node *b)
			{
				return a < b;
			}
		};
		Heap<Node*, NodeCompare> h;

		for (size_t i = 0; i < size; i++)
		{
			h.Push(new Node(arr[i]));
		}

		while (h.Size() > 1)
		{
			Node *left = h.Top();
			h.Pop();
			Node *right = h.Top();
			h.Pop();

			Node* parent=new Node(left->_wight + right->_wight);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;

			h.Push(parent);
		}
		_root = h.Top();
		h.Pop();
	}
protected:
	Node *_root;
};



#define _CRT_SECURE_NO_WARNINGS 1

#pragma once


//实现一个栈，要求实现Push（入栈）、Pop（出栈）、Min（返回最小值的操作）的时间复杂度为O(1)
#include<iostream>
#include<cstdlib>
#include<cassert>
#include<stack>
#include<vector>

using namespace std;

template<typename T>
class Stack
{
public:
	void push(const T& d);
	void pop();
	T& min();
	
private:
	stack<T>DataStack;
	stack<T>MinStack;

};

template<typename T>
void Stack<T>::push(const T& d)
{
	DataStack.push(d);
	if (MinStack.empty() || d <= MinStack.top())
	{
		MinStack.push(d);
	}

}
template<typename T>
void Stack<T>::pop()
{
	assert(!DataStack.empty());
		
	if (DataStack.top() == MinStack.top())
	{
		DataStack.pop();
		MinStack.pop();
	}
	DataStack.pop();
}
template<typename T>
T& Stack<T>::min()
{
	return MinStack.top();
}

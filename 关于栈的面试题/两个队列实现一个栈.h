

#pragma once

#include<iostream>
#include<cstdlib>
#include<cassert>
#include<queue>

using namespace std;

template<typename T>
class Stack
{
public:
	void push(const T & d);
	void pop();
	size_t size();
	bool empty();
	T& top();
private:
	queue<T> q1;
	queue<T> q2;
};

template<typename T>
void Stack<T>::push(const T& d)
{
	if (q2.empty()&&q2.empty())
	{
		q1.push(d);
	}
	else if (!q1.empty())
	{
		q2.push(d);
	}
	else
		q1.push(d);
	
}
template <typename T>
void Stack<T>::pop()
{
	assert(!q1.empty() || !q2.empty());
	if (!q1.empty())
	{
		while (q1.size()>1)
		{
			q2.push(q1.front());
			q1.pop();
		}
		q1.pop();
	}
	else
	{
		while (q2.size()>1)
		{
			q1.push(q2.front());
			q2.pop();
		}
		q2.pop();
	}
}
template <typename T>
bool Stack<T>::empty()
{
	return q1.empty() && q2.empty();
}
template <typename T>
size_t Stack<T>::size()
{
	return q1.size() + q2.size();
}
template <typename T>
T& Stack<T>::top()
{
	assert(!q1.empty() || !q2.empty());
	if (!q1.empty())
	{
		return q1.back();
	}
	else
	{
		return q2.back();
	}
}
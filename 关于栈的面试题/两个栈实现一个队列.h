#pragma once

#include<iostream>
#include<cstdlib>
#include<cassert>
#include<stack>
using namespace std;

template<typename T>
class Queue
{
public:
	void push(const T& d);
	void pop();
	size_t size();
	bool empty();
	T& front();
	T& back();



private:
	stack<T > s1;
	stack<T > s2;
};

template<typename T>
void Queue<T>::push(const T& d)
{
	s1.push(d);
}
template<typename T>
void Queue<T>::pop()
{
	assert((!s1.empty() )||(! s2.empty()));
	if (s2.empty())
	{
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
	}
	s2.pop();
}
template<typename T>
size_t Queue<T>::size()
{
	return s1.size() + s2.size();
}
template<typename T>
bool Queue<T>::empty()
{
	return s1.empty()&&s2.empty();
}
template<typename T>
T& Queue<T>::front()
{
	assert((!s1.empty()) || (!s2.empty()));

	if (s2.empty())
	{
		while (!s1.empty())
		{
			s2.push(s1.top());
			s1.pop();
		}
	}
	return s2.top();
}
template<typename T>
T& Queue<T>::back()
{
	assert((!s1.empty()) || (!s2.empty()));

	if (s1.empty())
	{
		while (!s2.empty())
		{
			s1.push(s2.top());
			s2.pop();
		}
	}
	return s1.top();
}


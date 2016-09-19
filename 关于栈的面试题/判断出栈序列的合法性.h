//判断元素出栈、入栈顺序的合法性。
//如：入栈的序列（1，2，3，4，5）
//出栈序列为（4，5，3，2，1），是合法序列
//入栈序列（1，2，3，4，5），
//出栈序列为（1，5，3，2，4）是不合法序列


#pragma once
#include<iostream>
#include<cstdlib>
#include<cassert>
#include<stack>

using namespace std;

int j = 0;
bool JudgeStackSeq(int *InArr, int *OutArr, size_t sz)
{
	stack<int > s;
	int j = 0;
	int pos=0;
	for (size_t i = 0; i < sz; i++)
	{
		s.push(InArr[i]);

		
		while (!s.empty()&&s.top()==OutArr[j])
		{
			
			
			s.pop();
			j++;
		}

	}
	
	return s.empty();
}
//�ж�Ԫ�س�ջ����ջ˳��ĺϷ��ԡ�
//�磺��ջ�����У�1��2��3��4��5��
//��ջ����Ϊ��4��5��3��2��1�����ǺϷ�����
//��ջ���У�1��2��3��4��5����
//��ջ����Ϊ��1��5��3��2��4���ǲ��Ϸ�����


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
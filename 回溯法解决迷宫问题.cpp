#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<cstdlib>
#include"stack.h"

#define N 10
struct Pos
{
	Pos(const int &row = 0, const int &col =0)
	:_row(row)
	,_col(col)
	{}
	size_t _row;
	size_t _col;
};
void GetMaze(int *arr)
{
	FILE * mz = fopen("MazeMap.txt", "r");
	assert(mz != NULL);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N;)
		{
			char ch = fgetc(mz);
			if (ch == '0' || ch == '1')
			{
				arr[i*N + j] = ch-'0';
				j++;
			}
			continue;
		}
	}
	fclose(mz);
}
void PrintMaze(int *arr)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << arr[i*N + j]<<" ";

		}
		cout << endl;
	}
}
bool CheckPath(int * maze,Pos &next)
{
	if (next._col < N&&next._row < N
		&&next._col >= 0 && next._row >= 0
		&& (maze[next._row*N + next._col] == 0))
		return true;
	else
		return false;
}
bool GetPath(int *maze, int row, int col, Stack<Pos> &path, Pos entry)
{
	Pos cur = entry;
	Pos next;
	path.Push(cur);
	while (!path.Empty())
	{
		if (cur._row != entry._row&&cur._col != entry._col && (cur._row == row - 1 || cur._row == 0 || cur._col == col - 1))
		{
			maze[cur._row*N + cur._col] = 2;
			return true;

		}

		maze[cur._row*N + cur._col] = 2;
		
		//右
		next = cur;
		++next._col;
		if (CheckPath(maze, next))
		{
			cur = next;
			path.Push(cur);
			continue;
		}


		//左
		next = cur;
		--next._col;
		if (CheckPath(maze, next))
		{
			cur = next;
			path.Push(cur);
			continue;
		}

		//上
		next = cur;
		--next._row;
		if (CheckPath(maze, next))
		{
			cur = next;
			path.Push(cur);
			continue;
		}
		
		//下
		next = cur;
		++next._row;
		if (CheckPath(maze, next))
		{
			cur = next;
			path.Push(cur);
			continue;
		}
		cur = path.Top();
		path.Pop();
	}
	return false;
}
void test3()
{
	int maze[N][N];
	GetMaze((int *)maze);
	cout << "迷宫：" << endl;
	PrintMaze((int *)maze);
	cout << endl;
	Stack<Pos> path;
	GetPath((int *)maze, N, N, path, Pos(2, 0));
	cout << "找到出口后：" << endl;
	PrintMaze((int *)maze);

}
int main()
{
	test3();
	system("pause");
	return 0;
}
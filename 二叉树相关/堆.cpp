#define _CRT_SECURE_NO_WARNINGS 1


#include"binary.h"
#include"thread.h"
#include"heap.h"

void test1()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int *ar = NULL;
	int arr[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTree<int > b(a, 10, (int )'#');
	BinaryTree<int > bt(arr, 15, (int )'#');
	BinaryTree<int > c(ar, 0, (int)'#');
	BinaryTree<int > d;
	

	//cout<<d.Depth()<<endl;
	//cout << b.Depth() << endl;
	cout << b.GetKLevel(3) << endl;
	cout << b.GetKLevel(1) << endl;
	cout << d.GetKLevel(7) << endl;

	//b.InfixPrint();
	b.PostPrintNorR();
	//b.PostPrintNorR();
	//bt.LevelPrint();
	//cout<<bt.Leafsize() << endl;
	//cout << bt.Depth() << endl;
	//cout << b.Leafsize() << endl;
	//
	//cout <<c.Leafsize()<< endl;

	//cout << b.Size() << endl;
	//b.Preorderprint();
	//b.InfixPrint();
	//b.PostPrint();
	//cout << endl;
	//cout << d.Size() << endl;
	//d.Preorderprint();
	//d.InfixPrint();
	//d.PostPrint();
	//cout<<c.size() << endl;
	//c.InfixPrint();
	//c.PostPrint();
	//c.Preorderprint();

	/*cout << d.size() << endl;
	d.InfixPrint();
	d.PostPrint();
	d.Preorderprint();*/
	/*cout<<bt.size() << endl;
	bt.Preorderprint();
	bt.InfixPrint();
	bt.PostPrint();*/
	cout << endl;

	/*b.Preorderprint();
	b.InfixPrint();
	b.PostPrint();
	cout << b.size() << endl;*/

}
void test2()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int *ar = NULL;
	int arr[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTreeThread<int > b(a, 10, (int)'#');
	
	b.PreOrderThread();
	b.PreOrderTh();
}
void testheap()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	BinaryHeap<int > t(15);
	t.CreateMinHeap(a, 10);
	t.PrintHeap();
	t.Insert(15);
	t.PrintHeap();
}

int main()
{
	testheap();
	system("pause");
	return 0;
}
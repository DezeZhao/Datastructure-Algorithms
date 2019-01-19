/*
第1行1个正整数n, 表示创建的顺序表的元素个数
第2行n个正整数，空格分割，表示n个元素值
第3行2个整数i x, 空格分割，表示在第i个位置插入新元素x,若i位置不合法，输出-1，否则输出表中全部元素
第4行1个整数j，表示删除第j个元素，若元素位置不合适，输出-1，否则输出表中全部元素
第5行1个整数y, 查找整数y在顺序表中的位置并输出该位置值，若不存在，输出-1。
注：全部数值 <= 10000，元素位置从1开始。
   每个操作都在上一个操作的基础上完成
*/
#include<iostream>
using namespace std;
#define MAX_L 10000
typedef struct 
{
	int *elem;
	int length;
}SeqList;
SeqList SL;
void InitList(SeqList &SL,int n)
{
	int x, i;
	SL.elem = new int[MAX_L];
	for (i = 0; i < n; i++)
	{
		cin >> x;
		SL.elem[i] = x;
		SL.length++;
	}
}
void PrintList(SeqList &SL, int n)
{
	for (int i = 0; i < SL.length; i++)
		if (i == 0)
			cout << SL.elem[i];
		else
			cout << " " << SL.elem[i];
	cout <<endl;
}
void  InsertList(SeqList &SL, int elem, int i)
{
	if (i<1 || i>SL.length + 1)
		cout << -1<<endl;
	else
	{
		for (int j = SL.length - 1; j >= i - 1; j--)
			SL.elem[j + 1] = SL.elem[j];
		SL.elem[i - 1] = elem;
		SL.length++;
		for (int j = 0; j< SL.length; j++)
			if (j == 0)
				cout << SL.elem[j];
			else
				cout<<" "<<SL.elem[j];
		cout << endl;
	}
}
void DelList(SeqList &SL, int j)
{
	if (j<1 || j>SL.length)
		cout << -1 << endl;
	else
	{
		for (int i =j; i <SL.length; i++)
			SL.elem[i - 1] = SL.elem[i];
		SL.length--;
		for (int i = 0; i < SL.length; i++)
			if (i == 0)
				cout << SL.elem[i];
			else
				cout << " " << SL.elem[i];
		cout << endl;
	}
}
int SearchList(SeqList &SL, int y)
{
	for (int i = 0; i < SL.length; i++)
		if (SL.elem[i] == y)
			return i + 1;
	return -1;
}
void ClrList(SeqList &SL)
{
	delete[]SL.elem;
}
int main()
{
	int n, i, j, x, y;
	cin >> n;
	InitList(SL, n);
	cin >> i >> x;
	cin >> j;
	cin >> y;
	PrintList(SL, n);
	InsertList(SL, x, i);
	DelList(SL, j);
	cout << SearchList(SL, y) << endl;
	ClrList(SL);
	return 0;
}

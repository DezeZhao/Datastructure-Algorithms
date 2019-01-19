/*
第1行1个正整数n, 表示创建的顺序表的元素个数
第2行n个正整数ai，空格分割，表示n个元素值
第3行1个整数x, 表示要删除的元素值，若表中不存在x，输出-1，否则输出删除全部x后，表中的全部元素

注：ai <= 10000, 0<n<=1,000,000
*/
#include<iostream>
using namespace std;
#define MAX_L 1000000
typedef struct 
{
	int *elem;
	int length;
}SeqList;
SeqList SL;
void InitList(SeqList &SL,int n)
{
	int x, i=0;
	SL.elem = new int[MAX_L];
	while(i<n)
	{
		cin >> x;
		SL.elem[i++] = x;
		SL.length++;
	} 
}
void PrintList(SeqList &SL)
{
	for (int i = 0; i < SL.length; i++)
		if (SL.elem[i] != 0 && SL.elem[i] > 0)
			cout << SL.elem[i] << " ";
	cout << endl;
}
void DelList(SeqList &SL, int e)
{
	int flag = 0;
	for (int i = 0; i < SL.length; i++)
	{
		flag = 0;
		if (SL.elem[i] == e)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		for (int i = 0; i < SL.length; i++)
			if (SL.elem[i] == e)
				SL.elem[i] = 0;
		PrintList(SL);
	}
	if (flag == 0)
		cout << -1 << endl;
}
void ClrList(SeqList &SL)
{
	delete[]SL.elem;
}
int main()
{
	int n;
	cin >> n;
	InitList(SL,n);
	int e;
	cin >> e;
	DelList(SL, e);
	ClrList(SL);
	return 0;
}

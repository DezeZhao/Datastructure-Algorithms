/*第1行n个整数,当为0时结束，表示LA中的元素。 
第2行m个整数，为0表示结束，表示LB中的元素。
假定全部数值 <= 10000*/
#include<iostream>
using namespace std;
#define MAX_L 10000
#define MAX_LC 20000
typedef struct 
{
	int *elem;
	int length;
}SeqList;
SeqList SLA,SLB,SLC;
int c = 0;
void InitList(SeqList &SL)
{
	int x, i=0;
	SL.elem = new int[MAX_L];
	while(1)
	{
		cin >> x;
		if (x == 0)
			break;
		SL.elem[i] = x;
		SL.length++;
		i++;
	} 
}
void SortList(SeqList &SL)
{
	int temp;
	for (int i = 0; i < SL.length - 1; i++)
		for (int j = 0; j < SL.length - i - 1; j++)
			if ((SL.elem[j] > SL.elem[j + 1]) && SL.elem[j + 1] > 0)
			{
				temp = SL.elem[j];
				SL.elem[j] = SL.elem[j + 1];
				SL.elem[j + 1] = temp;
			}
}
void InsertList(SeqList &Lc,int e)
{
	Lc.elem[c++] = e;
	Lc.length++;
}
void CmbList(SeqList &La, SeqList &Lb, SeqList &Lc)
{
	Lc.elem = new int[MAX_LC];
	int a = 0,b=0;
	while (a<La.length&&b< Lb.length)
	{
		if (La.elem[a] < Lb.elem[b])
		{
			InsertList(Lc, La.elem[a]);
			a++;
		}
		else
		{
			InsertList(Lc, Lb.elem[b]);
			b++;
		}
	}
	while (a < La.length)
	{
		InsertList(Lc, La.elem[a]);
		a++;
	}
	while (b < Lb.length)
	{
		InsertList(Lc, Lb.elem[b]);
		b++;
	}
}
void PrintList(SeqList &SL)
{
	
	for (int i = 0; i < SL.length; i++)
		if (i == 0)
			cout << SL.elem[i];
		else
			cout << " " << SL.elem[i];
	cout << endl;
}
void ClrList(SeqList &SL)
{
	delete[]SL.elem;
}
int main()
{
	InitList(SLA);
	SortList(SLA);
	InitList(SLB);
	SortList(SLB);
	CmbList(SLA, SLB, SLC);
	PrintList(SLC);
	ClrList(SLA);
	ClrList(SLB);
	ClrList(SLC);
	return 0;
}

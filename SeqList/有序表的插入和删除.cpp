/*第1行n个正整数,当为0时结束。 
第2行一个整数，表示插入的元素值，输出插入的位置。
第3行一个整数，表示删除的元素值，输出删除的位置。
假定全部数值 <= 10000*/
#include<iostream>
using namespace std;
#define MAX_L 10000
typedef struct 
{
	int *elem;
	int length;
}SeqList;
SeqList SL;
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
void  InsertList(SeqList &SL, int e)
{
	int i = 0;
	while (SL.elem[i]>0&&SL.elem[i] < e)i++;
	if (i < SL.length)
	{
		for (int j = SL.length - 1; j >= i - 1; j--)
			SL.elem[j + 1] = SL.elem[j];
		SL.elem[i] = e;
	}
	else
		SL.elem[i] = e;
	cout << i + 1 << endl;
	SL.length++;
}
void DelList(SeqList &SL, int e)
{
	int i, flag = 0,j;
	for (i = 0; i < SL.length; i++)
	{
		flag = 0;
		if (SL.elem[i] == e)
		{
			j = i + 1;
			flag = 1;
			break;
		}
	}
	if(flag==1)
	{
		for (i =j; i <SL.length; i++)
			SL.elem[i - 1] = SL.elem[i];
		SL.length--;
		cout << j << endl;
	}
	if (flag == 0)
		cout << -1 << endl;
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
	InitList(SL);
	SortList(SL);
	int e1, e2;
	cin >> e1;
	cin >> e2;
	InsertList(SL, e1);
	DelList(SL, e2);
	PrintList(SL);
	ClrList(SL);
	return 0;
}

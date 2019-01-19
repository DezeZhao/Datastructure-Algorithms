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
void Rev_same(SeqList &SL)
{
	int *only;
	only = new int[MAX_L];
	int k = 0, t = 1, flag = 0, i, j;
	only[0] = SL.elem[0];
	for (i = 1; i < SL.length; i++)
	{
		flag = 1;
		for (j = 0; j < t; j++)
			if (only[j] == SL.elem[i])
			{
				flag = 0;
				break;
			}
		if (flag == 1)
			only[t++] = SL.elem[i];
	}
	for (int i = 0; i < t; i++)
		cout << only[i] << " ";
	delete[]only;
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
	Rev_same(SL);
	ClrList(SL);
	return 0;
}

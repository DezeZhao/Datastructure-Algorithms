/*
输入
第1行n个整数,当为0时结束，表示LA中的元素。 
第2行m个整数，为0表示结束，表示LB中的元素。

假定全部数值 <= 10000
输出
1行，合并后的结果
*/
#include<iostream>
using namespace std;
struct LNode
{
	int data;
	LNode *next;
};
void  fun(LNode *h)
{
	LNode *p;
	int *e;
	e = new int[10000];
	p = h->next;
	int i = 0;
	while (p)
	{
		p->data = e[i++];
		p = p->next;
	}
}
void CreatList(LNode *head)
{
	LNode *p;
	int x;
	head->next = NULL;
	while (1)
	{
		cin >> x;
		if (x == 0)
			break;
		p = new LNode;
		p->data = x;
		p->next = head->next;
		head->next = p;
	}
}
int Length(LNode *head)
{
	LNode *p;
	p = head->next;
	int i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	return i;
}
void SortList(LNode *h)
{
	LNode *p;
	int *e;
	e = new int[10000];
	p = h->next;
	int i = 0;
	while (p)
	{
		 e[i++]=p->data;
		p = p->next;
	}
	int t;
	for (int j = 0; j < i - 1; j++)
		for (int k = 0; k < i - 1 - j; k++)
			if (e[k] > e[k + 1]&&e[k+1]>0)
			{
				t = e[k];
				e[k] = e[k + 1];
				e[k + 1] = t;
			}
	p = h->next;
	i = 0;
	while (p)
	{
		p->data = e[i++];
		p = p->next;
	}
	delete []e;
}
void Cmb_List(LNode *ha, LNode *hb, LNode *hc)
{
	LNode *pa, *pb, *pc;
	pa = ha->next;
	pb = hb->next;
	pc = hc;
	while (pa  && pb)
	{
		if (pa->data < pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = (pa) ? pa : pb;
}
void PrintList(LNode *head)
{
	LNode *p;
	p = head->next;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
}
int main()
{
	LNode *ha, *hb, *hc;
	ha = new LNode;
	hb = new LNode;
	hc = new LNode;
	CreatList(ha);
	CreatList(hb);
	SortList(ha);
	SortList(hb);
	Cmb_List(ha, hb, hc);
	PrintList(hc);
	cout << endl;
	return 0;
}

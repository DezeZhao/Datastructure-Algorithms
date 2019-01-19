/*
描述
设有n个人围坐一圈，从第s个人开始报数，数到第m个人出列，然后从出列的下一个人开始重新报数，数到第m个人又出列，。。。。。。如此反复，直到所有人全部出列。对于任意给定的n,s,m，求按出列次序得到的n个人的序列。

输入
一行，共三个整数n,s,m 以空格分割
输出
一行，按出列次序依次输出所有人的编号，从1计数，空格分割
*/
#include<iostream>
using namespace std;
struct LNode
{
	int data;
	LNode *next;
};
LNode* CreatList(int n)
{
	LNode *h;
	h = new LNode;
	h = NULL;
	LNode *r, *p;
	r = NULL;
	for (int i = 1; i <= n; i++)
	{
		p = new LNode;
		p->data = i;
		p->next = NULL;
		if (h == NULL)
		{
			h = p;
			r = h;
		}
		else
			r->next = p;
		r = p;
	}
	r->next = h;
	return h;
}
void Josephus(LNode*h, int m, int s)
{
	LNode *q, *p1;
	p1 = h;
	q = NULL;
	int i, j;
	for (i = 1; i < s; i++)
	{
		q = p1;
		p1 = p1->next;
	}
	while (p1->next != p1)
	{
		for (j = 1; j < m; j++)
		{
			q = p1;
			p1 = p1->next;
		}
		q->next = p1->next;
		cout << p1->data << " ";
		p1 = q->next;
	}
	cout << p1->data << endl;
}
int main()
{
	int n, s, m;
	LNode *h;
	cin >> n >> s >> m;
	h = CreatList(n);
	Josephus(h, m, s);
	return 0;
}

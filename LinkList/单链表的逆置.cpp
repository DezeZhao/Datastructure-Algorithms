/*
输入
第1行1个正整数n, 表示创建的链表的元素个数
第2行n个正整数ai，空格分割，表示n个元素值
假定ai <= 10000, 0<n<1,000,000

输出
共2行
第1行，顺序输出用头插法创建的链表
第2行，顺序输出逆置后所有3的倍数
*/
#include<iostream>
using namespace std;
struct LNode
{
	int data;
	LNode *next;
};
void CreatList(LNode *head, int n)
{
	LNode *p;
	int x;
	head->next = NULL;
	for (int i = n; i > 0; i--)
	{
		p = new LNode;
		cin >> x;
		p->data = x;
		p->next = head->next;
		head->next = p;
	}
}
void PrintList(LNode *head)
{
	LNode *p;
	p = head;
	p = p->next;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
}
void Reverse(LNode *head)
{
	LNode *p, *q;
	p = head->next;
	head->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		q->next = head->next;
		head->next = q;
	}
}
void Judge_3t(LNode *head)
{
	LNode *p;
	p = head->next;
	while (p)
	{
		if (p->data % 3 == 0)
			cout << p->data << " ";
		p = p->next;
	}
}
void destroy(LNode *head)
{
	LNode *p;
	p = head->next;
	while (p)
	{
		delete p;
		p = p->next;
	}
}
int main()
{
	LNode *head;
	head = new LNode;
	int n;
	cin >> n;
	CreatList(head, n);
	PrintList(head);
	cout << endl;
	Reverse(head);
	Judge_3t(head);
	return 0;
}

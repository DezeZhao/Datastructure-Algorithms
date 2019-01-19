/*
第1行1个正整数n, 表示创建的单链表的元素个数
第2行n个正整数ai，空格分割，表示n个元素值
第3行2个整数i x, 空格分割，表示在第i个元素前插入新元素x。
第4行1个整数j，表示删除第j个元素，
第5行1个整数y, 表示查找整数y

已知：ai,n <= 10000
备注：每个操作都在上一个操作的基础上完成
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
	p = head->next;
	while (p)
	{
		cout << p->data << " ";
		p = p->next;
	}
}
void InsertList(LNode *head, int n, int i, int x)
{
	LNode *p, *q;
	q = new LNode;
	int j = 0;
	p = head;
	while (j < i - 1 && p)
	{
		p = p->next;
		j++;
	}
	if (!p || j > i - 1)
		cout << -1<<endl;
	else
	{
		q->data = x;
		q->next = p->next;
		p->next = q;
		PrintList(head);
		cout << endl;
	}
}
void DelList(LNode *head, int n, int j)
{
	LNode *p, *q;
	p = head;
	int i = 0;
	while (p->next&&i < j - 1)
	{
		p = p->next;
		i++;
	}
	if (!(p->next) || i > j - 1)
		cout << -1 << endl;
	else
	{
		q = p->next;
		p->next = q->next;
		PrintList(head);
		cout << endl;
	}
}
void SearchList(LNode *head, int y)
{
	LNode *p;
	p = head->next;
	int i = 1;
	while (p&&p->data != y)
	{
		p = p->next;
		i++;
	}
	if (p == NULL)
		cout << -1 << endl;
	else
		cout << i << endl;
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
int main()
{
	LNode *head;
	head = new LNode;
	int n;
	cin >> n;
	CreatList(head, n);
	int i, x;
	cin >> i >> x;
	int j;
	cin >> j;
	int y;
	cin >> y;
	PrintList(head);
	cout << endl;
	InsertList(head, n, i, x);
	DelList(head, n, j);
	SearchList(head, y);
	cout << Length(head) << endl;
	return 0;
}

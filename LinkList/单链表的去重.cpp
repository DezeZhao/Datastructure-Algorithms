/*输入
第1行1个正整数n, 表示创建的链表的元素个数
第2行n个正整数ai，表示表中元素。 

假定 ai <= 1,000,000,000, n<=10,000
输出
1行,去重后的所有元素。*/
#include<iostream>
using namespace std;
struct LNode
{
	int data;
	LNode *next;
};
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
void CreatList(LNode *head,int n)
{
	LNode *p, *q;
	int x;
	q = head;
	for (int i = n; i > 0; i--)
	{
		p = new LNode;
		cin >> x;
		p->data = x;
		q->next = p;
		q = p;
	}
	q->next = NULL;
}
void Rev_same(LNode *head)
{
	LNode *p, *q, *r, *s;
	p = head->next;
	r = head;
	int flag = 0;
	while (p)
	{
		if (flag == 0)
		{
			q = p;
			p = p->next;
			q->next = NULL;
			r->next = q;
			r = q;
		}
		s = head->next;
		while (s && p)
		{
			if (s->data == p->data)
			{
				p = p->next;
				flag = 1;
				break;
			}
			flag = 0;
			s = s->next;
		}
	}
}
int main()
{
	LNode *head;
	head = new LNode;
	int n;
	cin >> n;
	CreatList(head,n);
	Rev_same(head);
	PrintList(head);
	cout << endl;
	return 0;
}

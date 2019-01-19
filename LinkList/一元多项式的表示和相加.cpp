/*
描述
一元多项式是有序线性表的典型应用，用一个长度为m且每个元素有两个数据项（系数项和指数项）的线性表((p1,e1),(p2,e2),...,(pm,em))可以唯一地表示一个多项式。 本题实现多项式的表示和相加。

输入
第1行一个整数m，表示第一个一元多项式的长度
后面有m行，每行两项pi ei，中间以空格分割
一个整数n,表示第二个一元多项式
后面n行，每行两项，中间以空格分割
输出
两个多项式相加后多项式链表
*/
#include<iostream>
using namespace std;
struct poly
{
	int coef;
	int expn;
	poly *next;
};
poly *h;
void CreatL(poly *h,int n)
{
	poly *p, *q;
    q=h;
	int c, e;
	for (int i = 0; i < n; i++)
	{
		cin >> c >> e;
		p = new poly;
		p->coef = c;
		p->expn = e;
		q->next = p;
		q = p;
	}
	q->next = NULL;
}
void ADD_1_2(poly *h1, poly *h2, poly *h3)
{
	poly *p, *q, *r,*s;
	p = h1->next;
	q = h2->next;
	s = h3;
	while (p&&q)
	{
		r = new poly;
		if (p->expn == q->expn)
		{
			r->coef = p->coef + q->coef;
			r->expn = p->expn;
			p = p->next;
			q = q->next;
		}
		else if (p->expn < q->expn)
		{
			
			r = p;
			p = p->next;
		}
		else
		{
			r = q;
			q = q->next;
		}
		s->next = r;
		s = r;
	}	
	s->next = (p) ? p : q;
}
void PrintL(poly *h)
{
	poly *p;
	p = h->next;
	while (p)
	{
		if (p->coef != 0)
			cout << p->coef << " " << p->expn << endl;
		p = p->next;
	}
}
int main()
{
	int m, n;
	poly *h1, *h2, *h3;
	h1 = new poly;
	h2 = new poly;
	h3 = new poly;
	cin >> m;
	CreatL(h1, m);
	cin >> n;
	CreatL(h2, n);
	ADD_1_2(h1, h2, h3);
	PrintL(h3);
	return 0;

}

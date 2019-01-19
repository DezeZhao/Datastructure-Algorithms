/*
描述
本题练习中序遍历线索二叉树的基本操作，包括中序线索化，中序遍历线索二叉树、查找某元素的中序遍历的后继结点，前驱结点。

输入
2行
第1行，输入先序序列，内部结点用一个字符表示，空结点用#表示
第2行，输入一个字符c，查找该字符的后继结点元素和前驱结点元素
输出
第1行，输出中序遍历序列
第2~3行，输出查找字符的结果，若不存在，输出一行Not found，结束
若找到，输出2行，若无后继或前驱，用NULL。
第2行输出该字符的直接后继元素及该后继元素的RTag，格式为：succ is 字符+RTag
第3行输出该字符的直接前驱继元素及前驱元素的LTag
格式为：prev is 字符+LTag
样例输入1
abc##d##ef###
b
样例输出1
cbdafe
succ is d1
prev is c1
样例输入2
abc##d##ef###
e
样例输出2
cbdafe
succ is NULL
prev is f1
样例输入3
abc##d##ef###
g
样例输出3
Not found
*/
#include<iostream>
using namespace std;
typedef enum { Link, Thread }PointerTag;
typedef char TElemType;
typedef struct  Node
{
	TElemType  data;
	Node  *rchild, *lchild;
	PointerTag Ltag = Link, Rtag = Link;
}BiThrNode, *BiThrTree;
BiThrTree pre;
/*创建树*/
void CreatBiTree(BiThrTree &T)
{
	TElemType c;
	cin >> c;
	if (c == '#')
		T = NULL;
	else
	{
		T = new Node;
		if (!T)
			exit(-1);
		T->data = c;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}
/*中序递归线索化二叉树*/
void InOrderThreading(BiThrTree &T)
{
	if (T)
	{
		InOrderThreading(T->lchild);
		if (!T->lchild)
		{
			T->Ltag = Thread;
			T->lchild = pre;
		}
		if (!T->rchild)
			T->Rtag = Thread;
		if (pre&&pre->Rtag == Thread)
			pre->rchild = T;
		pre = T;
		InOrderThreading(T->rchild);
	}
}
/*遍历中序线索二叉树*/
void InOrderTraverse_Thrt(BiThrTree &T)
{
	BiThrTree p = T;
	while (p)
	{
		while (p->Ltag == Link)
			p = p->lchild;
		cout << p->data;
		while (p->Rtag == Thread && p->rchild)
		{
			p = p->rchild;
			cout << p->data;
		}
		p = p->rchild;
	}
}
/*寻找目标*/
BiThrNode* SearchNode(BiThrTree &T,TElemType ch,int&flag)
{
	BiThrTree p = T;
	while (p)
	{
		while (p->Ltag == Link)
		{
			p = p->lchild;
		}
		if (p->data == ch)
		{
			flag = 1;
			return p;
		}
		while (p->Rtag == Thread && p->rchild)
		{
			p = p->rchild;
			if (p->data == ch)
			{
				flag = 1;
				return p;
			}
		}
		p = p->rchild;
	}
	flag = 0;
}
/*寻找前驱*/
BiThrNode* InOrderPre(BiThrTree &p)
{
	BiThrTree pre;
	if (p->Ltag == Thread)
		return p->lchild;
	else
	{
		pre = p->lchild;
		while (pre->Rtag == Link)
			pre = pre->rchild;
		return pre;
	}
}
/*寻找后继*/
BiThrNode* InOrderSucc(BiThrTree &p)
{
	BiThrTree succ;
	if (p->Rtag == Thread)
		return p->rchild;
	else
	{
		succ = p->rchild;
		while (succ->Ltag == Link)
			succ = succ->lchild;
		return succ;
	}
}
int main()
{
	BiThrTree T, pre, succ, p;
	int flag = 0;
	TElemType ch;
	CreatBiTree(T);
	cin >> ch;
	InOrderThreading(T);
	InOrderTraverse_Thrt(T);
	cout << endl;
	p = SearchNode(T, ch, flag);
	if (flag == 1)
	{
		succ = InOrderSucc(p);
		cout << "succ is ";
		if (succ == NULL)
			cout << "NULL" << endl;
		else
			cout << succ->data << succ->Rtag << endl;
		pre = InOrderPre(p);
		cout << "prev is ";
		if (pre == NULL)
			cout << "NULL" << endl;
		else
			cout << pre->data << pre->Ltag << endl;
	}
	else
		cout << "Not found" << endl;
	return 0;
}

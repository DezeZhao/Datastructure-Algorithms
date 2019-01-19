/*
描述
本题练习用非递归完成二叉树的中序遍历。参照课本p131算法6.3

输入
一行，输入先序序列，内部结点用一个字符表示，空结点用#表示
输出
多行，每行记录对栈的一次操作。如元素1入栈,即输出push 1;出栈则输出pop;访问函数则直接输出元素。
样例输入
abc##d##ef###
样例输出
push a
push b
push c
pop
c
pop
b
push d
pop
d
pop
a
push e
push f
pop
f
pop
e
*/
#include<iostream>
using namespace std;
typedef   char TElemType;
typedef int Status;
#define  STACK_INIT_SIZE  100 
#define OK     1
#define ERROR  0
#define TRUE   1
#define FALSE  0
typedef struct Node
{
	TElemType  Data;
	Node *lchild;
	Node *rchild;
}*BiTree;
typedef struct {
	BiTree   *base;   //存放动态申请空间的首地址（栈底）
	BiTree  *top;    //栈顶指针
	int   stacksize;     //当前分配的元素个数
} SqStack;
Status InitStack(SqStack &s)
{
	s.base = new BiTree[STACK_INIT_SIZE];
	if (!s.base) exit(-1);
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status StackEmpty(SqStack s)
{
	if (s.top == s.base)
		return TRUE;
	else
		return FALSE;
}
Status Pop(SqStack &s, BiTree  &e)
{
	if (s.top == s.base)
		return ERROR;
	e = *--s.top;
	return OK;
}
Status Push(SqStack &s, BiTree &e)
{
	*s.top++= e;
	return OK;
}
void IniBiTree(BiTree &T)
{
	T = NULL;
}
void DestroyBiTree(BiTree &T)
{
	if (T)
	{
		if (T->lchild)
			DestroyBiTree(T->lchild);
		if (T->rchild)
			DestroyBiTree(T->rchild);
		delete T;
		T = NULL;	
	}
}
void CreatBiTree(BiTree &T)
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
		T->Data = c;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}
void InorderTraverse(BiTree &T)
{
	SqStack S;
	BiTree p = T;
	InitStack(S);
	while (p || !StackEmpty(S))
	{
		if (p)
		{
			Push(S, p);
			cout << "push " << p->Data<<endl;
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			cout << "pop" << endl;
			cout << p->Data << endl;
			p = p->rchild;
		}
	}


}
int main()
{
	BiTree T;
	IniBiTree(T);
	CreatBiTree(T);
	InorderTraverse(T);
	DestroyBiTree(T);
	return 0;
}

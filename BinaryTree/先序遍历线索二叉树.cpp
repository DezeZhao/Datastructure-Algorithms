/*
描述
对二叉树进行先中后遍历分别得到一个线性序列，在该序列中每个结点都只有一个直接前驱和直接后继（除第一个和最后一个结点）。用二叉链表表示二叉树，有n+1个指针域为空，若用其存储该结点的前驱或后继结点，则称该指针域为线索。线索二叉树就是对二叉树进行了某种线索化的二叉树。 本题练习线索二叉树的基本操作，包括先序线索化，先序遍历线索二叉树、输出二叉树。

输入
一行，输入先序序列，内部结点用一个字符表示，空结点用#表示
输出
多行，输出先序线索化后的二叉树的树型图(逆时针旋转90度)，每一层之间输出5个空格，每个结点的数据按照下列格式：数据元素+LTag+RTag
最后1行，输出对先序线索二叉树先序遍历的序列
样例输入
abc##d##ef###
样例输出
     e01
          f11
a00
          d11
     b00
          c11
abcdef
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
/*先序递归线索化二叉树*/
void PreOrderThreading(BiThrTree &T)
{
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
	if (T->Ltag == Link)PreOrderThreading(T->lchild);
	if (T->Rtag == Link)PreOrderThreading(T->rchild);
}
/*去线索化*/
void RemoveThreading(BiThrTree &T)
{

	if (T->Ltag==Thread)
		T->lchild = NULL;
	if (T->Rtag==Thread)
		T->rchild = NULL;
	if (T->Ltag == Link)RemoveThreading(T->lchild);
	if (T->Rtag == Link)RemoveThreading(T->rchild);
}
/*输出树形*/
void ShapeBiThrTree(BiThrTree &T, int Depth)
{
	if (T)
	{
		ShapeBiThrTree(T->rchild, Depth + 1);
		for (int i = 1; i < Depth; i++)
			cout << "     ";
		cout << T->data<<T->Ltag<<T->Rtag;
		T->Ltag = Link;
		T->Rtag = Link;
		cout << endl;
		ShapeBiThrTree(T->lchild, Depth + 1);
	}
}
/*遍历先序线索二叉树*/
void PreOrderTraverse_Thrt(BiThrTree &T)
{
	BiThrTree  p = T;
	cout << p->data;
	while (p->rchild)
	{
		if (p->Ltag == Link)
			p = p->lchild;
		else
			p = p->rchild;
		cout << p->data;
	}
}
int main()
{
	BiThrTree T;
	CreatBiTree(T);
	PreOrderThreading(T);	
	RemoveThreading(T);
	ShapeBiThrTree(T, 1);
	PreOrderThreading(T);
	PreOrderTraverse_Thrt(T);
	cout << endl;
	return 0;
}

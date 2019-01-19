/*
描述
本题练习用递归程序对二叉树进行计算，包括二叉树的叶子结点数，总结点数，高度，复制二叉树（左右互换）。

输入
一行，输入先序序列，内部结点用一个字符表示，空结点用#表示
输出
多行
第1行，一个整数，叶子结点的个数
第2行，一个整数，总结点的个数
第3行，一个整数，二叉树的高度
后面多行，输出二叉树的树型图，每一层之间间距5个空格
后面多行，输出复制后的二叉树的树型图，格式同上。
样例输入
abc##d##ef###
样例输出
3
6
3
     e
          f
a
          d
     b
          c
          c
     b
          d
a
          f
     e
*/
#include<iostream>
#include<cmath>
using namespace std;
typedef   char TElemType;
int Tdepth = 1;
int NumLeave = 0;
int NumNode = 0;
typedef struct Node
{
	TElemType  Data;
	Node *lchild;
	Node *rchild;
}*BiTree;
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
void CopyTree(BiTree &T,BiTree &S)
{
	if (T)
	{
		S = new Node;
		if (!S)
			exit(-1);
		S->lchild = S->rchild = NULL;
		S->Data = T->Data;
		CopyTree(T->lchild, S->lchild);
		CopyTree(T->rchild, S->rchild);
	}
}
void Exchange(BiTree &T)
{
	BiTree S;
	if (T)
	{
		S = T->lchild;
		T->lchild = T->rchild;
		T->rchild = S;
		Exchange(T->lchild);
		Exchange(T->rchild);
	}
}
int max(int a, int b)
{
	if (a > b) return a;
	return b;
}
/*********************************************************************
函数功能：计算二叉树
说明：利用先序递归遍历二叉树的方法，首先访问根结点，总结点个数加一，如果该结点的左右孩子都为空，则叶子结点个数加一，并且比较当前叶子结点的深度和树当前深度的大小，将大者赋给树的深度，之后运行递归函数，访问左右孩子，递归结束之后就可以得出总结点个数NumNode，叶子结点个数NumLeave，以及树的深度Tdepth.
(PS：叶子结点的深度计算在上面输出树形时已做过详细说明)
*********************************************************************/
void CalCulBiTree(BiTree &T, int Depth)
{
	if (T)
	{
		NumNode++;
		if (!T->lchild && !T->rchild)
		{
			NumLeave++;
			Tdepth = max(Tdepth, Depth);
		}
		CalCulBiTree(T->lchild, Depth + 1);
		CalCulBiTree(T->rchild, Depth + 1);
	}
}
void ShapeBiTree(BiTree &T, int Depth)
{
	if (T)
	{
		ShapeBiTree(T->rchild, Depth + 1);
		for (int i = 1; i < Depth; i++)
			cout << "     ";
		cout << T->Data;
		cout << endl;
		ShapeBiTree(T->lchild, Depth + 1);
	}
}
int main()
{
	BiTree T, S;
	IniBiTree(T);
	CreatBiTree(T);
	CalCulBiTree(T, 1);
	cout << NumLeave << endl;
	cout << NumNode << endl;
	cout << Tdepth << endl;
	CopyTree(T, S);
	Exchange(S);
	ShapeBiTree(T, 1);
	ShapeBiTree(S, 1);
	DestroyBiTree(T);
	DestroyBiTree(S);
	return 0;
}

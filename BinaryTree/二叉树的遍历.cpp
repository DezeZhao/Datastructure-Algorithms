/*
Problem 1 (二叉树)
描述
二叉树是n（n>=0）个结点的有限集合，它或为空树，或是由一个称之为根的结点加上两棵分别称为左子树和右子树的互不相交的二叉树组成。 本题练习二叉树的基本操作，包括先序遍历建立二叉树、先序遍历、中序遍历、后序遍历、层次遍历、输出二叉树。

输入
一行，输入先序序列，内部结点用一个字符表示，空结点用#表示
输出
多行
第1行，输出先序遍历序列
第2行，输出中序遍历序列
第3行，输出后序遍历序列
第4行，层次遍历序列
输出二叉树的树型图(逆时针旋转90度)，每一层之间输出5个空格
样例输入
abc##d##ef###
样例输出
abcdef
cbdafe
cdbfea
abecdf
     e
          f
a
          d
     b
          c
*/
#include<iostream>
using namespace std;
typedef   char TElemType;
#define MAXSIZE   10000
typedef struct Node
{
	TElemType  Data;
	Node *lchild;
	Node *rchild;
}*BiTree;
struct SqQueue {
	BiTree *base;
	int front, rear;
};
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
void PreOrderTraverse(BiTree &T)
{
	if (!T)
		return;
	else
	{
		cout << T->Data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}
void InOrderTraverse(BiTree &T)
{
	if (T) 
	{
		InOrderTraverse(T->lchild);
		cout << T->Data;
		InOrderTraverse(T->rchild);
	}
}
void PostOrderTraverse(BiTree &T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->Data;
	}
}
/*********************************************************************
函数功能：层次遍历二叉树
说明：在此要新增一个队列Q用来存储每次遍历访问的结点，若结点不空，首先
将根结点的数据存到队尾（队首），队尾指针后移，再利用循环，先访问该结点
数据，队首指针后移，再访问该结点的左右孩子结点每访问一个孩子结点（若孩
子结点不空），则将该节点数据入队，队尾指针后移，继续此循环，直到队尾指
针和队首指针相遇，结束循环。完成层次遍历。
*********************************************************************/
void LevelOrderTraverse(BiTree &T)
{
	BiTree p;
	SqQueue Q;
	Q.base = new BiTree[MAXSIZE]; 
	if (!Q.base) exit(-1);  
	Q.front = Q.rear = 0;
	if (T) 
	{
		Q.base[Q.rear] =T;
		Q.rear = (Q.rear + 1) % MAXSIZE;
		while (Q.front != Q.rear)
		{
			p = Q.base[Q.front];
			cout << p->Data;
			Q.front = (Q.front + 1) % MAXSIZE;
			if (p->lchild)
			{
				Q.base[Q.rear] = (p->lchild);
				Q.rear = (Q.rear + 1) % MAXSIZE;
			}
			if (p->rchild)
			{
				Q.base[Q.rear] =(p->rchild);
				Q.rear = (Q.rear + 1) % MAXSIZE;
			}
		}
	}
}
/*********************************************************************
函数功能：输出二叉树树形
说明：由题目给出的树形分析得知，每行的元素正好是中序遍历得到元素的逆序
排列由此可以将中序遍历的递归方法中的左右孩子访问次序对换，那么输出的数
据次序就是树形输出次序，空格个数是该结点的深度，所以在递归中应该加一个
Depth来计算每个结点的深度，实际上递归的层次数就是该结点所在的深度，这
样每次的访问不管是进入递归还是退出递归都会对应一个相应的Depth，那样就
很容易记录每个结点的深度，从而输出树形。
*********************************************************************/
void ShapeBiTree(BiTree &T,int Depth)
{
	if (T)
	{
		ShapeBiTree(T->rchild,Depth+1);
		for (int i = 1; i <Depth; i++)
			cout << "     ";
		cout << T->Data;
		cout << endl;
		ShapeBiTree(T->lchild,Depth+1);
	}
}
int main()
{
	BiTree T;
	IniBiTree(T);
	CreatBiTree(T);
	PreOrderTraverse(T);
	cout << endl;
	InOrderTraverse(T);
	cout << endl;
	PostOrderTraverse(T);
	cout << endl;
	LevelOrderTraverse(T);
	cout << endl;
	ShapeBiTree(T,1);
	DestroyBiTree(T);
	return 0;
}

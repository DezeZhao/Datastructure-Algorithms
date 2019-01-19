/*
描述
本题练习用双亲表示法输入哈夫曼树，给出哈夫曼编码。

输入
第1行一个正整数n, 表示叶子结点数
接着输入2*n-1行，每行3个数wi,pi,li(i从1开始)分别代表哈夫曼树中结点的权值,其双亲结点的编号,若是双亲的左孩子则li为0，否则为1
根结点的双亲用0表示。
输出
n行，每行是0和1的一串字符，代表哈夫曼编码，左子树为0,右子树为1。
样例输入1
8
5 9 1
29 14 0
7 10 0
8 11 0
14 12 0
23 13 1
3 9 0
11 11 1
8 10 1
15 12 1
19 13 0
29 14 1
42 15 0
58 15 1
100 0 0
样例输出1
1 11111
2 10
3 1110
4 000
5 110
6 01
7 11110
8 001
*/
#include<iostream>
#include<cstring>
using namespace std;
typedef struct {
	 int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char  **HuffmanCode;
void InputHuffman(HuffmanTree &HT,int &n)
{
	int i , w, pa, lc;
	int m = 2 * n - 1;
	HT = new HTNode[m + 1];
	HuffmanTree p, q;
	for (p = HT + 1, i = 1; i <= m; i++, p++)
		*p = { 0,0,0,0 };
    for (q=p = HT + 1, i = 1; i <= m; i++, p++)
	{
		cin >> w >> pa >> lc;
		p->weight = w;
		p->parent = pa;
		if (i != m)
			if (lc == 0)
				(q + pa - 1)->lchild = i;
			else
				(q + pa - 1)->rchild = i;
		else
			break;
	}
}
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int& n)
{
	int start, c, f, i;
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
	char* cd = new char[n];
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = HT[c].parent; f != 0; c = f, f = HT[f].parent)
			if (HT[f].lchild == c)cd[--start] = '0';
			else cd[--start] = '1';
		HC[i] = new char[n - start];
		strcpy(HC[i], &cd[start]);
		cout <<i<<" "<< HC[i] << endl;
	}
	delete[]cd;
}
int main()
{
	int n;
	cin >> n;
	HuffmanTree HT;
	HuffmanCode HC;
	InputHuffman(HT, n);
	HuffmanCoding(HT, HC, n);
	return 0;
}

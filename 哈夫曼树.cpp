/*
描述
哈夫曼树，又称最优树，是一类带权路径长度最短的树。本题练习构建哈夫曼树。

输入
第1行一个正整数n, 表示叶子结点数
第2行n个正整数, 表示叶子结点的权值
输出
一个整数值，表示哈夫曼树的带权路径长度
样例输入1
8
5 29 7 8 14 23 3 11
样例输出1
271
*/
#include<iostream>
#include<cstring>
using namespace std;
#define MAX 1000
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;
typedef char  **HuffmanCode;
int Min(HuffmanTree &HT, int i)
{
	int min =65535;
	int j, flag;
	for (j = 1; j <= i; j++)
		if (HT[j].weight < min && HT[j].parent == 0)
		{
			min = HT[j].weight;
			flag = j;
		}
	HT[flag].parent = 1;
	return  flag;
}

void Select(HuffmanTree &HT, int i, int &s1, int &s2)
{
	s1 = Min(HT, i);
	s2 = Min(HT, i);
	int temp=0;
	if (s1>s2)
	{
		temp = s1;
		s1 = s2;
		s2 = temp;
	}
}
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int w[], int& n, int &sum_w)
{
	if (n <= 1)
		return;
	int m;
	int s1, s2;
	m = 2 * n - 1;
	HT = new HTNode[m + 1];
	HuffmanTree p;
	int i;
	for (p = HT + 1, i = 1; i <= n; i++, p++, w++)
		*p = { *w,0,0,0 };
	for (; i <= m; i++)
		*p = { 0,0,0,0 };
	for (i = n + 1; i <= m; i++)
	{
		Select(HT,i-1,s1,s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HT[m].parent = 0;
	for (int j = n + 1; j <= m; j++)
		sum_w += HT[j].weight;
}
int main()
{
	int n, sum_w = 0;
	cin >> n;
	int *w = new int[MAX];
	HuffmanTree HT;
	HuffmanCode HC;
	for (int i = 0; i < n; i++)
		cin >> w[i];
	HuffmanCoding(HT, HC, w, n, sum_w);
	cout << sum_w << endl;
	return 0;
}

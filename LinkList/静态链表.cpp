/*
描述
静态链表（或称为数组链表），用一个一维数组S存储链表的所有结点。每个结点包含data和cur两个域，data存储数据,cur(称作游标，int类型)代替指针，存储链表的下一个结点在数组中的相对位置。 数组前两个s[0]存放链表头指针,s[1]存放闲置链表头指针；S[0].cur初始为-1，表示空表。S[1].cur初始为2，表示第1个可分配的结点位置。S[MaxSize-1]=-1表示无后继结点。初始S[i].cur=i+1, 表示所有未分配结点已形成一个备用链表，每当进行插入时，从备用链表中取得第1个结点作为待插入的新结点，删除时则将从链表中删除的结点链接到备用链表中。
静态链表实现线性表的操作与动态链表相似，执行插入和删除操作时不需移动元素，只需修改指针，因此具有链表存储结构的主要优点。 本题练习用静态链表实现线性表的基本操作，包括表的初始化，尾部追加一个元素、第i个元素位置前插入一个新的元素、删除第i个元素、查找某元素、判表空、判表满、表的遍历。 元素数据类型是字符串。 

输入
共6行
第1行2个正整数m,n, 其中m表示数组的容量,n表示首次追加到表中的元素个数（若元素个数超过数组容量，即n>m-2，多余元素不追加）
第2行n个字符串，空格分割，表示用尾部追加到表中的n个元素值，输入完毕，输出数组状态。
第3行2个数i x, 空格分割，表示在第i个元素前插入新元素x,若表满，输出"FULL",否则若i位置不合法，输出-1，否则输出链表所有元素，以空格分割;
第4行1个整数j，表示删除第j个元素，若表空，输出"EMPTY",否则若元素位置不合适，输出-1，否则输出所删除元素;
第5行1个字符串y, 查找y是表中的第几个元素，并输出该数值，若不存在，输出-1。
第6行1个字符串x, 表示在表尾追加新元素x,若表满，输出"FULL",否则输出链表所有元素，以空格分割;
第7行输出数组状态。

假定： m,n,i,j <= 100, x,y是字符串
数组状态按照 position : content : index格式输出，：是西文符号，：前后都有一个空格，数组元素之间用2个tab键分割,每3个元素一行
备注：每个操作都在上一个操作的基础上完成
输出
多行，分别是执行每次操作后的结果
第1~[m/3]行，追加n个元素后的数组状态；
后面1行，第i位置插入x后当前表中元素
后面1行，删除第j个元素后，当前表中元素
后面1行，查找y的结果
后面1行，表尾追加元素后当前表中元素
最后[m/3]行，执行全部操作后的数组状态；
样例输入
9 5
Jan Feb Mar Apr May
2 Jun
1
Mar
Oct
样例输出
0 : N/A : 2        1 : N/A : 7        2 : Jan : 3
3 : Feb : 4        4 : Mar : 5        5 : Apr : 6
6 : May : -1        7 : N/A : 8        8 : N/A : -1
Jan Jun Feb Mar Apr May 
Jan
3
Jun Feb Mar Apr May Oct 
0 : N/A : 7        1 : N/A : 8        2 : Oct : -1
3 : Feb : 4        4 : Mar : 5        5 : Apr : 6
6 : May : 2        7 : Jun : 3        8 : N/A : -1
*/
#include<iostream>
#include<string>
#define MaxSize 100
using namespace std;
typedef struct SListNode
{
	string data;
	int cur;
}SLinkList[MaxSize];
SLinkList s;
string str[MaxSize];
void CreatSL(SLinkList s, int n, string str[], int m)
{
	int i;
	s[0].cur = -1;
	s[1].cur = 2;
	s[0].data = "N/A";
	s[1].data = "N/A";
	int k = 0;
	for (int i = 2; i < m; i++)
	{
		if (m - n >= 2)
		{
			if (k < n)
				s[i].data = str[k++];
			else
			{
				s[i].data = "N/A";
				k++;
			}
		}
		else
		{
			s[i].data = str[k++];
		}
		s[i].cur = i + 1;
	}
	if (m != 2)
		s[m - 1].cur = -1;
	if (m - n >= 2)
	{
		if (n == 0 && m == 2)
		{
			s[0].cur = -1;
			s[1].cur = 2;
		}
		if (n != 0)
		{
			s[1].cur = s[n + 1].cur;
			s[0].cur = 2;
			s[n + 1].cur = -1;
		}
	}
	else if (m != 2)
	{
		s[0].cur = 2;
		s[1].cur = -1;
	}
	if (m == 2||m==1)
	{
		s[0].cur = -1;
		s[1].cur = -1;
	}

}
void PrintSL(SLinkList &s, int m)
{
	int  k = 0;
	for (int i = 0; i < m; i++)
	{
		cout << i << " : " << s[i].data << " : " << s[i].cur << '\t' << '\t';
		k++;
		if (k == 3)
		{
			cout << endl;
			k = 0;
		}
	}
	if (k != 0)
		cout << endl;
}
void PrintData(SLinkList &s)
{
	int i = 0;
	while (s[i].cur != -1)
	{
		i = s[i].cur;
		cout << s[i].data << " ";
	}
	cout << endl;
}
int Len(SLinkList &s)
{
	int i = 0;
	int len = 0;
	while (s[i].cur != -1)
	{
		i = s[i].cur;
		len++;
	}
	return len;
}
bool IsEmpty(SLinkList &s)
{
	if (s[0].cur == -1)
		return true;
	else
		return false;
}
void InsertSL(SLinkList &s, int i, string x, int &n, int m)
{
	int l, j = 0;
	int k = 1;
	if (s[k].cur == -1||(i==1&&s[j].cur==-1))
	{
		cout << "FULL" << endl;
		return;
	}
	if (IsEmpty(s) && i == 1)
	{
		s[2].data = x;
		int flag = s[s[k].cur].cur;
		s[s[k].cur].cur = -1;
		s[k].cur = flag;
		s[j].cur = 2;
		PrintData(s);
	}
	else if (i >= 1 && i <= Len(s) + 1)
	{
		s[j].cur = 2;
		for (l = 1; l < i; l++)
			j = s[j].cur;
		s[s[k].cur].data = x;
		int flag = s[s[k].cur].cur;
		s[s[k].cur].cur = s[j].cur;
		s[j].cur = s[k].cur;
		s[k].cur = flag;
		PrintData(s);
	}
	else
		cout << -1 << endl;
}
void DelSL(SLinkList &s, int j, int n, int m)
{
	int i, k = 0, l = 1;
	if (s[k].cur == -1)
		cout << "EMPTY" << endl;
	else
	{
		if (j < 1 || j>Len(s))
			cout << -1 << endl;
		else
		{
			for (i = 1; i < j; i++)
				k = s[k].cur;
			cout << s[s[k].cur].data << endl;
			int flag = s[s[k].cur].cur;
			if (s[s[l].cur].data == "N/A"&&s[l].cur != -1)
				s[s[k].cur].cur = s[l].cur;
			else
				s[s[k].cur].cur = -1;
			s[l].cur = s[k].cur;
			s[s[k].cur].data = "N/A";
			s[k].cur = flag;
		}
	}
}
void SearchSL(SLinkList &s, string z)
{
	int i = 0, count = 0, pos = 0, j = 0;
	while (j++ <= Len(s))
	{

		count++;
		if (s[i].data == z)
		{
			pos = count - 1;
			break;
		}
		i = s[i].cur;
	}
	if (pos == 0)
		cout << -1 << endl;
	else
		cout << pos << endl;
}
void AddSL(SLinkList &s, string z, int m)
{
	int k = 1;
	if (s[k].cur == -1 || m == 2)
		cout << "FULL" << endl;
	else
	{
		k = s[k].cur;
		s[1].cur = s[k].cur;
		s[k].cur = -1;
		int j = 0;
		while (s[j].cur != -1)j = s[j].cur;
		s[j].cur = k;
		s[k].data = z;
		PrintData(s);
	}
}
int main()
{
	int m, n;
	SLinkList s;
	string str[MaxSize];
	cin >> m >> n;
	for (int k = 0; k < n; k++)
		cin >> str[k];
	CreatSL(s, n, str, m);
	int i;
	string x;
	cin >> i >> x;
	int j;
	cin >> j;
	string y;
	cin >> y;
	string z;
	cin >> z;
	PrintSL(s, m);
	InsertSL(s, i, x, n, m);
	DelSL(s, j, n, m);
	SearchSL(s, y);
	AddSL(s, z, m);
	PrintSL(s, m);
	return 0;
}

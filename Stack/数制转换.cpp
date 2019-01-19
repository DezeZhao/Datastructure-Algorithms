/*
输入
第1行两个数，转换前的数制 转换后的数制，以空格分割
第2行 待转换的数

假定全部数值 <= 10000
输出
1行，转换结果
样例输入
10 16
13
样例输出
D
*/
#include<iostream>
#include<cstring>
using namespace std;
#define MAX_INT_SIZE 10000
struct SeqStack
{
	char *top;
	char *base;
};
SeqStack s;
void PopStack(SeqStack &s)
{
		cout << *--s.top << endl;
}
void PushStack(SeqStack &s,char e)
{
		*s.top++ = e;
}
bool IsEmpty(SeqStack &s)
{
	if (s.top == s.base)
		return true;
	else
		return false;
}
void PrintStack(SeqStack &s)
{
	while (s.top != s.base)
		cout << *--s.top;
}
void convert_mTOn(SeqStack &s, int m, int n, char str[])
{
	int x, temp=0, y = 1;
	for (int i = 0; i < strlen(str); i++)
		PushStack(s, str[i]);
	while(!IsEmpty(s))
	{
		s.top--;
		if (*s.top >= '0'&&*s.top <= '9')
			x = *s.top - '0';
		if (*s.top >= 'A'&&*s.top <= 'Z')
			x = *s.top - 'A' + 10;
		temp = temp + y * x;
		y *= m;
	}
	while (temp)
	{
		int r = temp % n;
		PushStack(s, (r <= 9 ? '0' + r : 'A' + r - 10));
		temp /= n;
	}
}
int main()
{
	int m, n;
	char str[100];
	s.top = new char;
	s.base = new char;
	s.top = s.base;
	cin >> m >> n;
	cin >> str;
	convert_mTOn(s,m, n, str);
	PrintStack(s);
	cout << endl;
	return 0;
}

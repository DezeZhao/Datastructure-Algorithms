/*
输入
第1行1个正整数n, 表示栈的容量
接着读入多行，每一行执行一个动作。
若输入"Pop"，表示出栈，当栈空时，输出一行“Stack is Empty”;否则，输出出栈的元素；
若输入"Push 10"，表示将元素10入栈,当栈满时，输出"Stack is Full"，否则，不输出；
若输入"Quit",输出栈中所有元素，以空格分割。

假定全部数值 <= 10000
输出
多行，分别是执行每次操作后的结果
样例输入
4
pop
push 10
push 2
push 3
pop
pop
push 1
push 2
push 3
push 4
quit
样例输出
Stack is Empty
3
2
Stack is Full
3 2 1 10
*/
#include<iostream>
#include<string>
using namespace std;
#define MAX_INT_SIZE 10000
struct SeqStack
{
	int *top;
	int *base;
	int stacksize;
};
SeqStack s;
bool IsEmpty(SeqStack &s)
{
	if (s.top == s.base)
		return true;
	else
		return false;
}
bool IsFull(SeqStack&s)
{
	if (s.top - s.base >= s.stacksize)
		return true;
	else
		return false;
}
void PopStack(SeqStack &s)
{
	if (IsEmpty(s))
		cout << "Stack is Empty" << endl;
	else
		cout << *--s.top << endl;
}
void PushStack(SeqStack &s,int& e)
{
	if (IsFull(s))
		cout << "Stack is Full" << endl;
	else
		*s.top++ = e;
}
void PrintStack(SeqStack &s)
{
	while (s.top != s.base)
		cout << *--s.top << " ";
}
int main()
{
	int n;
	cin >> n;
	s.base = new int;
	s.top = new int;
	s.top = s.base;
	s.stacksize = n;
	string s1;
	int x;
	int y[100] = { 0 };
	string vis[100];
	int i = 0;
	while (1)
	{
		cin >> s1;
		if (s1 == "pop")
			vis[i] = "pop";

		else if (s1 == "push")
		{
			cin >> x;
			vis[i] = "push";
			y[i] = x;
		}
		else
		{
			vis[i] = "quit";
			break;
		}
		i++;
	}
	int k = 0;
	while (vis[k] != "quit")
	{
		if (vis[k] == "pop")
			PopStack(s);
		else
			PushStack(s, y[k]);
		k++;
	}
	PrintStack(s);
	return 0;
}

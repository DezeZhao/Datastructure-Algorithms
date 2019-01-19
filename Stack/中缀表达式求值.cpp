/*
描述
表达式求值是程序设计语言编译中的一个基本问题。它的实现是栈应用的一个典型例子。可以用算符优先法直接对表达式求值，或者是先将表达式转换成后缀表达式然后再对后缀表达式求值。 现在请你编写程序，完成简单的算术表达式求值。 假定表达式中只含有+-*/四种运算符和括号()，操作数和结果均是整数。

输入
一行，一个整数四则运算表达式，不含空格，遇等号"="结束输入
输出
一行，表达式的运算结果，若表达式中含有非法字符或除0，均输出ERROR。
样例输入
4+2*3-10/4=
样例输出
8
*/
#include<iostream>
using namespace std;
#define MAX_SIZE 100
struct SeqStack
{
	char *top;
	char *base;
};
struct opdStack
{
	int top;
	int val[MAX_SIZE];
};
void IniStack(SeqStack &s)
{
	s.base = new char;
	s.top = s.base;
}
void PopStack(SeqStack &s)
{
	s.top--;
}
bool IsEmpty(SeqStack &s)
{
	if (s.top == s.base)
		return true;
	else
		return false;
}
void PushStack(SeqStack &s, char e)
{
	*s.top++ = e;
}
bool GetTop(SeqStack &s, char &e)
{
	if (IsEmpty(s))
		return false;
	e = *(s.top - 1);
	return true;
}
void PrintStack(SeqStack &s)
{
	while (s.top != s.base)
		cout << *--s.top;
}
void ConvertExp(SeqStack &s, char m[], char b[],int & flag)
{
	int i = 0, k = 0;
	char c, c1;
	c = m[i];
	while (c != '=')
	{
		if (c == '+' || c == '-')
		{
			while (!IsEmpty(s) && GetTop(s, c1) && c1 != '(')
			{
				PopStack(s);
				b[k++] = c1;
			}
			PushStack(s, c);
		}
		else if (c == '*' || c == '/')
		{
			while (!IsEmpty(s) && GetTop(s, c1) && (c1 == '*' || c1 == '/'))
			{
				PopStack(s);
				b[k++] = c1;
			}
			PushStack(s, c);
		}
		else if(c== '(')
			PushStack(s, c);
		else if (c == ')')
		{
			while (GetTop(s, c1) && c1 != '(')
			{
				PopStack(s);
				b[k++] = c1;
			}
			PopStack(s);
		}
		else if (c >= '0'&&c <= '9')
		{
			while (c >= '0'&&c <= '9')
			{
				b[k++] = c;
				c = m[++i];
			}
			i--;
			b[k++] = ' ';
		}
		else
		{
			flag = 1;
			return;
		}
		c = m[++i];
	}
	while (!IsEmpty(s))
	{
		GetTop(s, c1);
		PopStack(s);
		b[k++] = c1;
	}
	b[k] = '\0';
}
int Calculate(opdStack& opd, char b[])
{
	int i = 0, value = 0, tmp = 0;
	int v1 = 0, v2 = 0;
	char c = b[i];
	while (c != '\0')
	{
		value = 0;
		switch (c)
		{
		case '+':
			v2 = --opd.top;
			v1 = --opd.top;
			tmp = opd.val[v1] + opd.val[v2];
			opd.val[opd.top] = tmp;
			opd.top++;
			break;
		case '-':
			v2 = --opd.top;
			v1 = --opd.top;
			tmp = opd.val[v1] - opd.val[v2];
			opd.val[opd.top] = tmp;
			opd.top++;
			break;
		case '*':
			v2 = --opd.top;
			v1 = --opd.top;
			tmp = opd.val[v1] * opd.val[v2];
			opd.val[opd.top] = tmp;
			opd.top++;
			break;
		case '/':
			v2 = --opd.top;
			v1 = --opd.top;
			if (opd.val[v2] == 0)
				return 0;
			tmp = opd.val[v1] / opd.val[v2];
			opd.val[opd.top] = tmp;
			opd.top++;
			break;
		default:
			while (b[i] != ' ')
			{
				value = value * 10 + (b[i] - '0');
				i++;
			}
			opd.val[opd.top++] = value;
		}
		c = b[++i];
	}
	return  opd.val[--opd.top];
}
int main()
{
	SeqStack s;
	opdStack opd;
	int flag = 0;
	opd.top = 0;
	IniStack(s);
	char Mid_exp[MAX_SIZE], Back_exp[MAX_SIZE];
	cin >> Mid_exp;
	ConvertExp(s, Mid_exp, Back_exp, flag);
	if (flag == 1)
		cout << "ERROR" << endl;
	else
		if (Calculate(opd, Back_exp) == 0)
			cout << "ERROR" << endl;
		else
			cout << Calculate(opd, Back_exp) << endl;
	return 0;
}

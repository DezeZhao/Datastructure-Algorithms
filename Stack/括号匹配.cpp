/*
括号都是成对出现的，并且不能交叉配对，如{[()]}是正确的，而{[}]就是不正确的。现在给你一个C语言源程序，请检查其中的的括号是否都是配对的。假定需要判断的括号只有这三组：{}，[]，()。

输入
一个c语言程序，以EOF结束。
输出
若所有括号均配对成功，输出一行yes;
否则，第一行输出no;
第二行输出第一个未匹配的符号，若缺少右括号，则输出该符号+"期待右括号"；若缺少左括号，则输出该括号+"期待左括号"。
样例输入1
int main(){ 
    int x=0;
    for (int i=1;i<5;i++){
        x=(x+i)*10;
}
样例输出1
no
{期待右括号
样例输入2
int main(){
    int x=0;
    for (int i=1;i<5;i++){
        x=(x+i)*10;}
    }
}
样例输出2
no
}期待左括号
样例输入3
int main(){ 
    int x=0;
    for (int i=1;i<5;i++)
        x=(x+i)*10;
}
样例输出3
yes
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
	s.top--;
}
void PushStack(SeqStack &s,char e)
{
		*s.top++= e;
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
void Match(SeqStack &s, char s0[])
{
	int i = 0;
	if (s0[0] == '}' || s0[0] == ']' || s0[0] == ')')
	{
		cout << "no" << endl;
		cout << s0[0] << "?ڴ???????" << endl;
		return;
	}
	else
	{
		PushStack(s, s0[0]);
		i++;
		while (s0[i] != '\0')
		{
			int flag = 0;
			if ((s0[i] == '}'&&*(s.top - 1) == '{') || (s0[i] == ']'&&*(s.top - 1) == '[') || (s0[i] == ')'&&*(s.top - 1) == '('))
			{
				PopStack(s);
				flag = 1;
			}
			else if (s0[i] == '{' || s0[i] == '[' || s0[i] == '(')
				PushStack(s, s0[i]);
			else if(((s0[i] == '}'&&*(s.top - 1) != '{') || (s0[i] == ']'&&*(s.top - 1) != '[') || (s0[i] == ')'&&*(s.top - 1) != '('))&&!IsEmpty(s))
			{
					cout << "no" << endl;
					cout << *--s.top << "?ڴ???????" << endl;
					return;
			}
			else if (IsEmpty(s) && (s0[i + 1] != '\0') && (s0[i] == '}' || s0[i] == ']' || s0[i] == ')'))
			{
				cout << "no" << endl;
				cout << s0[i] << "?ڴ???????" << endl;
				return;
			}
			i++;
			if (flag == 1&&s0[i]!='\0')
			{
				if (s0[i] == '{' || s0[i] == '[' || s0[i] == '(')
				{
					PushStack(s, s0[i]);
					i++;
				}
				if (IsEmpty(s)&&s0[i + 1] == '\0' && (s0[i] == ')' || s0[i] == '}' || s0[i] == ']'))
				{
					PushStack(s, s0[i]);
					i++;
				}
			}
		}
		if (s.top==s.base)
			cout << "yes" << endl;
		else
		{
			cout << "no" << endl;
			switch (*--s.top)
			{
			case '{':cout << "{?ڴ???????" << endl;
				break;
			case '[':cout << "[?ڴ???????" << endl;
				break;
			case '(':cout << "(?ڴ???????" << endl;
				break;
			case '}':cout << "}?ڴ???????" << endl;
				break;
			case ']':cout << "]?ڴ???????" << endl;
				break;
			case ')':cout << ")?ڴ???????" << endl;
				break;
			}
		}
	}

}
int main()
{
	s.base = new char;
	s.top = s.base;
	char c, s0[100];
	int i = 0,k=0;
	while ((c=getchar())!=EOF)
	{
		if (c == '(' || c== ')' || c== '{' || c== '}' || c== '[' || c == ']')
			s0[k++] = c;	
	}
	s0[k] = '\0';
    Match(s, s0);
	return 0;
}

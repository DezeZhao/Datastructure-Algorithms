/***********************************************************************
函数功能：判断栈是否为空
说明：当栈顶=栈底时，栈为空。
************************************************************************/
bool IsEmpty(SeqStack &s)
{
	if (s.top == s.base)
		return true;
	else
		return false;
}
/***********************************************************************
函数功能：判断栈满
说明：当栈顶-栈底>=栈的初始分配的空间时，栈满。
************************************************************************/
bool IsFull(SeqStack&s)
{
	if (s.top - s.base >= s.stacksize)
		return true;
	else
		return false;
}
/***********************************************************************
函数功能：出栈
说明：如果栈空，则不能出栈；若栈未空，则栈顶指针减1，输出栈顶元素。
************************************************************************/
void PopStack(SeqStack &s)
{
	if (IsEmpty(s))
		cout << "Stack is Empty" << endl;
	else
		cout << *--s.top << endl;
}
/***********************************************************************
函数功能：进制转换
输入参数：初始转换进制n,目的转换进制m
说明：将读入的数字作为字符(串)压栈，然后通过循环从最低位读取，即一个一个
出栈，用初始进制累加，同时随着数位的增加，初始进制也要累乘，保证累加的正
确性，直到栈空，累加结束，从而将n进制数转换为十进制数，然后再用除m取余的
方法，将得到的m进制的每位的数转换成字符（r <= 9 ? '0' + r : 'A' + r - 10）压栈，结束之后，再出栈，这样就将n进制数转换成了m进制数。
************************************************************************/
void convert_mTOn(SeqStack &s, int m, int n, char str[])
{
	int x, temp = 0, y = 1;
	for (int i = 0; i < strlen(str); i++)
		PushStack(s, str[i]);
	while (!IsEmpty(s))
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
/***********************************************************************
函数功能：括号匹配
输入参数：待检测的括号序列s0[]
说明：括号配对的前提是输入的括号种类有三种，即(),[],{};在检测是否匹配时，
若第一个括号为右括号),],}，则直接结束判断（缺少左括号）；其他情况下，若是
左括号则全部压栈，当出现第一个右括号时，将栈顶的左括号和其比较，若是不匹配，则结束判断（栈顶的括号期待相应的右括号）；否则，将栈顶的括号出栈。继续进行输入，按照前面的步骤循环，左压，右比较，直到括号序列结束。若是整个括号序列是配对的，则最终栈为空。
************************************************************************/
void Match(SeqStack &s, char s0[])
{
	int i = 0;
	if (s0[0] == '}' || s0[0] == ']' || s0[0] == ')')
	{
		cout << "no" << endl;
		cout << s0[0] << "期待左括号" << endl;
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
			else if (((s0[i] == '}'&&*(s.top - 1) != '{') || (s0[i] == ']'&&*(s.top - 1) != '[') || (s0[i] == ')'&&*(s.top - 1) != '(')) && !IsEmpty(s))
			{
				cout << "no" << endl;
				cout << *--s.top << "期待右括号" << endl;
				return;
			}
			else if (IsEmpty(s) && (s0[i + 1] != '\0') && (s0[i] == '}' || s0[i] == ']' || s0[i] == ')'))
			{
				cout << "no" << endl;
				cout << s0[i] << "期待左括号" << endl;
				return;
			}
			i++;
			if (flag == 1 && s0[i] != '\0')
			{
				if (s0[i] == '{' || s0[i] == '[' || s0[i] == '(')
				{
					PushStack(s, s0[i]);
					i++;
				}
				if (IsEmpty(s) && s0[i + 1] == '\0' && (s0[i] == ')' || s0[i] == '}' || s0[i] == ']'))
				{
					PushStack(s, s0[i]);
					i++;
				}
			}
		}
		if (s.top == s.base)
			cout << "yes" << endl;
		else
		{
			cout << "no" << endl;
			switch (*--s.top)
			{
			case '{':cout << "{期待右括号" << endl;
				break;
			case '[':cout << "[期待右括号" << endl;
				break;
			case '(':cout << "(期待右括号" << endl;
				break;
			case '}':cout << "}期待左括号" << endl;
				break;
			case ']':cout << "]期待左括号" << endl;
				break;
			case ')':cout << ")期待左括号" << endl;
				break;
			}
		}
	}
}

/***********************************************************************
函数功能：判断列车出站的序列是否ok
输入参数：列车入站序列InOdr,待判断列车出站序列Odr
说明：首先进行判断，若两者长度不相等，则直接结束判断；否则，再进行比较判
断。
比较时，首先从入站序列的首元素开始和出站序列比较，
若相等，两序列分别前移一位，
若不相等，再和栈顶元素比较；
若相等，将该元素出栈，出站序列前移一（j++），
     若此时j等于入站序列的长度，说明出站序列正确，结束循环，
若不相等，
     如果此时i已经等于入站序列的长度，则该出站序列不ok;
     如果不等，则将该入站元素压栈。i++；
继续执行此循环，直到结束循环。
************************************************************************/
Status Judge_OK(SqStack &s, char Odr[], char InOdr[], int iLen)
{
	int i = 0, j = 0;
	SElemType e;
	while (1)
	{
		if (InOdr[i] == Odr[j])    
		{
			i++;
			j++;
			if (j == iLen)
				return OK;
		}
		else if (s.GetTop(e) && e == Odr[j])
		{
			s.Pop(e);
			j++;
			if (j == iLen)
				return OK;
		}
		else
		{
			if (i == iLen)
				return ERROR;
			s.Push(InOdr[i]);
			i++;
		}
	}
}
/*******************************************************************
函数功能：将中缀表达式转换为后缀表达式
说明：如果当前读入的时操作数就将其存在Back_exp数组中，如果当前字符为
操作符，记为x1,将x1与栈顶的运算符x2比较，若栈顶运算符优先级小于当前
运算符优先级，就将当前运算符入栈，否则，将栈顶运算符出栈保存在
Back_exp数组中。之后继续比较新的栈顶运算符和当前运算符的优先级
若两者优先级相等，且x1=')’，x2=‘(',则将x2出栈，继续读入下一个字符；
若读到“=”,则结束，后缀表达式就存在Back_exp中。
注：在存数字时，每个数之间隔个空格，以便于计算一位数以上的数的值；
********************************************************************/
void ConvertExp(SeqStack &s, char m[], char b[], int & flag)
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
		else if (c == '(')
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
/*******************************************************************
函数功能：计算后缀表达式的值
说明：对BACK_exp数组进行遍历，如果当前读入的字符是操作数则将它放到opd
栈（操作数栈），如果当前读入的字符是操作符，则opd栈出栈两次，得到操作
数x,y,进行运算，然后将结果继续存到opd栈。重复执行此操作直到opd栈为空，
Back_exp数组到末尾，将结果opd.val[--opd.top]返回即可；
********************************************************************/
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

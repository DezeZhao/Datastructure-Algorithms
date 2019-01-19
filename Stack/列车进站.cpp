/*
描述
每一时刻，列车可以从入口车站或直接从入口进入出口，再或者从车站进入出口。即每一时刻可以有一辆车沿着箭头a或b或c的方向行驶。 现在有一些车在入口处等待，给出该序列，然后给你多组出站序列，请你判断是否能够通过上述的方式从出口出来。
输入
第1行，一个串，入站序列。
后面多行，每行一个串，表示出栈序列
输出
多行，若给定的出栈序列可以得到，输出yes,否则输出no。
样例输入
abc
abc
acb
bac
bca
cab
cba
样例输出
yes
yes
yes
yes
no
yes
*/
#include<iostream>
#include<cstring>
using namespace std;
#define MAX_SIZE 1000
#define OK     1
#define ERROR  0
#define LOVERFLOW   -2
typedef  int Status;
typedef int  SElemType;
#define  STACK_INIT_SIZE  100   //初始大小为100
#define  STACKINCREMENT  10   //若空间不够，每次增长10
class  SqStack
{
protected:
	SElemType *base;
	SElemType *top;
	int   stacksize;
public:
	SqStack();
	~SqStack();
	Status ClearStack();
	Status GetTop(SElemType&e);
	Status Push(SElemType e);
	Status Pop(SElemType&e);
};
SqStack s;
SqStack::SqStack()
{
	base = new SElemType[STACK_INIT_SIZE];
	if (base == NULL)
		exit(LOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
}
SqStack::~SqStack()
{
	if (base)
		delete base;
	top = NULL;
	stacksize = 0;
}
Status SqStack::ClearStack()
{
	if (stacksize > STACK_INIT_SIZE)
	{/*如果栈扩展过，恢复初始大小*/
		delete base;
		base = new SElemType[STACK_INIT_SIZE];
		if (base == NULL)
			exit(LOVERFLOW);
		stacksize = STACK_INIT_SIZE;
	}
	top = base;
	return OK;
}
Status SqStack::GetTop(SElemType &e)
{

	if (top == base)
		return ERROR;
	e = *(top - 1);
	return OK;
}
Status SqStack::Push(SElemType e)
{
	/*如果栈已满则扩充空间*/
	if (top - base >= stacksize)
	{
		SElemType *newbase;
		newbase = new SElemType[stacksize + STACK_INIT_SIZE];
		if (!newbase)
			return LOVERFLOW;
		memcpy(newbase, base, stacksize * sizeof(SElemType));
		delete base;
		base = newbase;
		top = base + stacksize;
		stacksize += STACKINCREMENT;
	}
	*top++ = e;
	return OK;
}
Status SqStack::Pop(SElemType &e)
{
	if (top == base)
		return ERROR;
	e = *--top;
	return OK;
}
Status Judge_OK(SqStack &s,char Odr[],char InOdr[],int iLen)
{
	int i=0, j=0;
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
int main()
{
	char InOdr[10];
	char OutOdr[MAX_SIZE][10];
	int iLen = 0, oLen = 0;
	cin.getline(InOdr, 10);
	int i;
	for (i = 0; i < 1000; i++)
	{
		if (!cin.getline(OutOdr[i], 10))
			break;
	}
	iLen = strlen(InOdr);
	for (int k = 0; k < i; k++)
	{
		s.ClearStack();
		oLen = strlen(OutOdr[k]);
		if (oLen != iLen)
			cout << "no" << endl;
		else
		{
			if (Judge_OK(s, OutOdr[k], InOdr, iLen))
				cout << "yes" << endl;
			else
				cout << "no" << endl;
		}
	}
	return 0;
}

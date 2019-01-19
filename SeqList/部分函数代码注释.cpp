/****************************************************
功能：初始化顺序表
输入参数：x
说明：利用循环，每输入一个数，将其存入顺序表，表长度加1
*****************************************************/
void InitList(SeqList &SL,int n)
{
	int x, i=0;
	SL.elem = new int[MAX_L];
	while(i<n)
	{
		cin >> x;
		SL.elem[i++] = x;
		SL.length++;
	} 
}
/***************************************************
功能：删除元素
输入参数：e
输出值：若找到e,输出其所在位置；否则，输出-1；
说明：若找到删除的元素e,后面的元素依次向前移动1，
表长减1；否则就返回-1。
****************************************************/
void DelList(SeqList &SL, int e)
{
	int i, flag = 0, j;
	for (i = 0; i < SL.length; i++)
	{
		flag = 0;
		if (SL.elem[i] == e)
		{
			j = i + 1;
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		for (i = j; i < SL.length; i++)
			SL.elem[i - 1] = SL.elem[i];
		SL.length--;
		cout << j << endl;
	}
	if (flag == 0)
		cout << -1 << endl;}
/******************************************
功能：找到元素并将其删除
输入参数：e
输出值：若是找到，将其删除并输出新表；否则
输出-1；
说明：利用循环，一旦找到该元素的位置，结束循环，
标记位置，flag=1，进行删除操作；否则，输出-1
********************************************/
void DelList(SeqList &SL, int e)
{
	int i, flag = 0, j;
	for (i = 0; i < SL.length; i++)
	{
		flag = 0;
		if (SL.elem[i] == e)
		{
			j = i + 1;
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		for (i = j; i < SL.length; i++)
			SL.elem[i - 1] = SL.elem[i];
		SL.length--;
		cout << j << endl;
	}
	if (flag == 0)
		cout << -1 << endl;
}
/*****************************************************
功能：任意位置插入元素
输入参数：位置i，元素e
输出值：若插入位置合适就输出插入后的顺序表；否则，输出-1
说明：若不是插在表尾，将第i个及以后的元素向后循环移动1；
若插在表尾，则不进行循环，直接进行赋值即可；
*******************************************************/
void  InsertList(SeqList &SL, int e, int i)
{
	if (i<1 || i>SL.length + 1)
		cout << -1 << endl;
	else
	{
		for (int j = SL.length - 1; j >= i - 1; j--)
			SL.elem[j + 1] = SL.elem[j];
		SL.elem[i - 1] = e;
		SL.length++;
	}
}
/************************************************
功能：在有序表中插入e使其还是有序表
说明：在一个有序表中，将该元素分别于表中元素比较，直到
e小于等于表中元素，将其插入即可，表长加1；插入的情况分析同上
**************************************************/
void  InsertList(SeqList &SL, int e)
{
	int i = 0;
	while (SL.elem[i] > 0 && SL.elem[i] < e)i++;
	if (i < SL.length)
	{
		for (int j = SL.length - 1; j >= i - 1; j--)
			SL.elem[j + 1] = SL.elem[j];
		SL.elem[i] = e;
	}
	else
		SL.elem[i] = e;
	cout << i + 1 << endl;
	SL.length++;
}
/******************************************
功能：排序
说明：利用冒泡法将顺序表排序，以有序输出
********************************************/
void SortList(SeqList &SL)
{
	int temp;
	for (int i = 0; i < SL.length - 1; i++)
		for (int j = 0; j < SL.length - i - 1; j++)
			if ((SL.elem[j] > SL.elem[j + 1]) && SL.elem[j + 1] > 0)
			{
				temp = SL.elem[j];
				SL.elem[j] = SL.elem[j + 1];
				SL.elem[j + 1] = temp;
			}
}
/*****************************************************
功能：将两个有序表合并为一个有序表
说明：比较La、Lb首元素的大小，小者存入Lc，利用循环，
若La[i]<L[j],L[i]插入Lc；反之，Lb[j]插入，j++;
直到某个顺序表结束，再将另一个顺序表剩余元素插入Lc即可
*******************************************************/
void CmbList(SeqList &La, SeqList &Lb, SeqList &Lc)
{
	Lc.elem = new int[MAX_LC];
	int a = 0, b = 0;
	while (a < La.length&&b < Lb.length)
	{
		if (La.elem[a] < Lb.elem[b])
		{
			InsertList(Lc, La.elem[a]);
			a++;
		}
		else
		{
			InsertList(Lc, Lb.elem[b]);
			b++;
		}
	}
	while (a < La.length)
	{
		InsertList(Lc, La.elem[a]);
		a++;
	}
	while (b < Lb.length)
	{
		InsertList(Lc, Lb.elem[b]);
		b++;
	}
}
/***********************************************
功能：去重
说明：建立辅助数组only，利用两层循环将，外层循环
用于SL.elem顺序表的遍历，内层循环用于only数组的遍历，
从而得到only数组只有只出现一次的元素。
************************************************/
void Rev_same(SeqList &SL)
{
	int *only;
	only = new int[MAX_L];
	int k = 0, t = 1, flag = 0, i, j;
	only[0] = SL.elem[0];
	for (i = 1; i < SL.length; i++)
	{
		flag = 1;
		for (j = 0; j < t; j++)
			if (only[j] == SL.elem[i])
			{
				flag = 0;
				break;
			}
		if (flag == 1)
			only[t++] = SL.elem[i];
	}
	for (int i = 0; i < t; i++)
		cout << only[i] << " ";
	delete[]only;
}
/********************
功能：打印顺序表
说明：利用循环将其输出
**********************/
void PrintList(SeqList &SL)
{
	for (int i = 0; i < SL.length; i++)
		if (SL.elem[i] != 0 && SL.elem[i] > 0)
			cout << SL.elem[i] << " ";
	cout << endl;
}
/*功能：销毁顺序表*/
void ClrList(SeqList &SL)
{
	delete[]SL.elem;
}

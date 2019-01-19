/*描述
队列是限定在表的一端插入，另一端删除的线性表。队列的特点是先进先出（FIFO)。 循环队列是队列的顺序存储结构。本题练习循环队列的基本操作，包括入队、出队、判队空、判队满、队列的遍历。

输入
第1行1个正整数n, 表示队列的容量
接着读入多行，每一行执行一个动作。
若输入"dequeue"，表示出队，当队空时，输出一行“Queue is Empty”;否则，输出出队的元素；
若输入"enqueue 10"，表示将元素10入队,当队满时，输出"Queue is Full"，否则，不输出；
若输入"Quit",输出队列中所有元素，以空格分割。

假定全部数值 <= 10000
输出
多行，分别是执行每次操作后的结果
样例输入
4
dequeue
enqueue 10
enqueue 2
enqueue 3
dequeue
dequeue
enqueue 1
enqueue 2
enqueue 3
enqueue 4
quit
样例输出
Queue is Empty
10
2
Queue is Full
3 1 2 3
*/
#include<iostream>
#include<string>
using namespace std;
#define MAXSIZE 100
#define OVERFLOW -2
#define OK       1
#define ERROR    0
#define TRUE    1
#define FALSE    0
typedef int Status;
typedef int QElemType;
class  SqQueue
{
protected:
	QElemType  *base;
	int   front;
	int   rear;
public:
	int n;
	SqQueue();
	~SqQueue();
	Status EnQueue(QElemType e);
	Status DeQueue(QElemType &e);
	Status QueueEmpty();
	Status QueueFull();
	void  PrintQueue();
};
SqQueue::SqQueue()
{
	base = new QElemType[MAXSIZE];
	if (!base) exit(OVERFLOW);
	front = rear = 0;
}
SqQueue::~SqQueue()
{
	delete base;
}
Status SqQueue::EnQueue(QElemType e)
{
 
	if (QueueFull())
	{
		cout << "Queue is Full" << endl;
		return ERROR;
	}
	base[rear] = e;
	rear = (rear + 1) % (n+1);
	return OK;
}
Status SqQueue::DeQueue(QElemType &e)
{
	if (QueueEmpty())
	{
		cout << "Queue is Empty" << endl;
		return ERROR;
	}
	e = base[front];
	cout << e << endl;
	front = (front + 1) % (n+1);
	return OK;
}
Status SqQueue::QueueEmpty()
{
	if (front == rear) return TRUE;
	return FALSE;
}
Status SqQueue::QueueFull()
{
	if ((rear + 1) % (n+1)== front)
		return TRUE;
	return FALSE;
}
void SqQueue::PrintQueue()
{
	while (front % (n + 1) != rear)
	{
		cout << base[front% (n + 1)]<<" ";
		front = (front + 1) % (n + 1);
	}
	cout << endl;
}
int main()
{
	SqQueue  Q;
	QElemType e;
	cin >> Q.n;
	string s;
	int x;
	int y[100] = { 0 };
	string vis[100];
	int i = 0;
	while (1)
	{
		cin >> s;
		if (s == "dequeue")
			vis[i] = "dequeue";

		else if (s == "enqueue")
		{
			cin >> x;
			vis[i] = "enqueue";
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
		if (vis[k] == "dequeue")
			Q.DeQueue(e);
		else
			Q.EnQueue(y[k]);
		k++;

	}
	Q.PrintQueue();
	return 0;
}

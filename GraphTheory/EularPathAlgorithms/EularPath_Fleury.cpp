#include<iostream>
#include<stack>
#include<vector>
using namespace std;

const int maxn = 2000;//最大顶点数
const int maxm = 3000;//最大边数
int n, m;
//int u[maxn], v[maxn], w[maxm];//起点,终点,权值

struct Edge
{
	int from, to, visit;//起始点,终点
	Edge(int u, int v, int a) :from(u), to(v), visit(a) {}//构造函数,初始化,类比class
};//定义边结构体

/*
无向图存在欧拉回路的充要条件是所有的点的度数均为偶数
无向图存在欧拉路径的充要条件是度数为奇数的点的数量为0个或者2个
有向图存在欧拉回路的充要条件是所有的点的出度均等于入度
有向图存在欧拉路径的充要条件是：
①：欧拉回路的情况
②：所有点中出度比入度大1的点有一个，入度比出度大1的点
有一个，不允许有大几个的情况
对于那些 Eularian path，起点和终点分别在那两个度数为奇的顶点上
（对于无向图）或是入度数不等于出度数的顶点上（对于有向图）。
*/

stack<int>s;//实现输出和dfs过程压/弹栈
vector<Edge>edges;
vector<int>G[maxn];//图的邻接表存储
//int G[maxn][maxn];
int deg[maxn];//存每个点度

/*初始化邻接表和边表*/
void init(int n)
{
	for (int i = 0; i < n; i++)
		G[i].clear();
	edges.clear();
}

/*向图中添加边*/
void AddEdge(int from, int to, int visit)
{
	edges.push_back(Edge(from, to, visit));
	int m = edges.size();//m-1=边的编号
	G[from].push_back(m - 1);//G存起点from对应的边的编号,从而可以找到对应
}                         //的edges[]数组中点和权值的信息
//的edges[]数组中点和权值的信息
int Find_evu(Edge &euv)
{
	int i;
	for (i = 0; i < G[euv.to].size(); i++)
	{
		Edge &evi = edges[G[euv.to][i]];
		if (evi.to == euv.from)
			break;
	}//找到v->u，此处较邻接矩阵法麻烦,一个一个遍历才能找到(无向图)
	//有向图则不需要遍历找v->u;
	return i;
}
/*Fleury算法(dfs)
设G 为一无向欧拉图，求G 中一条欧拉回路的算法为：
1) 任取G 中一顶点v0，令P0 = v0；
2) 假设沿Pi = v0e1v1e2v2 …eivi 走到顶点vi，按下面方法从E(G) - { e1, e2, …, ei }中选ei+1：
a) ei+1 与vi 相关联；
b) 除非无别的边可供选择，否则ei+1 不应该是Gi = G - { e1, e2, …, ei }中的桥。
3) 当2)不能再进行时算法停止。
可以证明的是，当算法停止时，所得到的简单回路Pm = v0e1v1e2v2 …emvm, (vm = v0)为G 中一条欧拉回路。
*/
void  DFS(int u)
{
	s.push(u);
	for (int i = 0; i < G[u].size(); i++)
	{//for(int v=1; v<=n; v++)
		Edge &euv = edges[G[u][i]];
		int v = Find_evu(euv);
		Edge &evu = edges[G[euv.to][v]];
		if (!euv.visit)//if(!G[u][v])
		{
			euv.visit = 1; 
			evu.visit = 1;//无重边情况，
			//G[u][v]--;若有重边则用矩阵存图较为方便
			//G[v][u]--;
			DFS(euv.to);//DFS(v);
			break;
		}
	}
}
void Fleury(int u)
{
	s.push(u);
	while (!s.empty())
	{
		int flag = 0;
		int v = s.top();
		s.pop();
		for (int i = 0; i < G[v].size(); i++)
		{
			Edge &e = edges[G[v][i]];
			if (e.visit)continue;
			flag = 1;
			break; 
		}
		if (!flag)
			cout << v << " ";//输出会因边的输入顺序不同而不同
		else
			DFS(v);
	}
}

int main()
{
	freopen("testdata.in", "r", stdin);
	freopen("testdata.out", "w", stdout);
	cin >> n >> m;
	init(n);
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		AddEdge(u, v, 0);//无重边情况
		//G[u][v]++
		AddEdge(v, u, 0);//建立无向图
		//G[v][u]++
		deg[u] ++;//计算顶点的度
		//G[u][0]++
		deg[v] ++;
		//G[v][0]++
	}
	int i;
	for (i = 1; i <= n; i++)
		if (deg[i] & 1)
			break;//度为奇数 
	if (i == n + 1)//没有奇度点，都为偶度点，从1开始即可(任意一点即可)
		Fleury(1);
	else
		Fleury(i);//从奇度点开始搜索
	system("pause");
	return 0;
}
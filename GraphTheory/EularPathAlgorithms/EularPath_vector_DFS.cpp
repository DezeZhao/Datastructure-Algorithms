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

/*deg
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
stack<int>s;
vector<Edge>edges;
vector<int>G[maxn];//图的邻接表存储
int deg[maxn];//存每个点度

/*初始化邻接表和边表*/
void init()
{
	for (int i = 0; i < 1025; i++)
		G[i].clear();
	edges.clear();
}

/*向图中添加边*/
void AddEdge(int from, int to,int able)
{
	edges.push_back(Edge(from, to, able));
	int m = edges.size();//m-1=边的编号
	G[from].push_back(m - 1);//G存起点from对应的边的编号,从而可以找到对应
}   
                         //的edges[]数组中点和权值的信息
int Find_evu(Edge &euv)
{
	int i;
	for (i = 0; i < G[euv.to].size(); i++)
	{
		Edge &evi = edges[G[euv.to][i]];
		if (evi.to == euv.from)
			break;
	}//找到v->u，此处较邻接矩阵法麻烦,遍历才能找到(无向图)
	//有向图则不需要遍历找v->u;
	return i;
}
/*Hierholzer算法(逐步插入回路法，dfs核心思想)*/
void DFS(int u)//只访问一次边
{
	for (int v = 0; v < G[u].size(); v++)
	{
		Edge &euv = edges[G[u][v]];
		int i=Find_evu(euv);
		Edge &evu = edges[G[euv.to][i]];
		if (!euv.visit)//u->v还没visit
		{
			euv.visit = 1;//visited
			evu.visit = 1;//visited(无向图)
			DFS(euv.to);
		}
	}
	s.push(u);//存放Eularian path/cycle
}

void PrintEularPath()
{
	while (!s.empty())
	{
		cout << s.top() <<endl;
		s.pop();
	}
	cout << endl;
}

int main()
{
	//freopen("testdata.in", "r", stdin);
	//freopen("testdata.out", "w", stdout);
	cin >>m;
	init();
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		AddEdge(u, v,0);
		AddEdge(v, u,0);//建立无向图
		deg[u]++;//计算顶点的度
		deg[v]++;
	}
	int i,j=1;
	for (i = 1; i <= n; i++)
		if (deg[i] & 1)
		{
			j=i;
			break;//度为奇数
		}
	DFS(j);
	PrintEularPath();
	return 0;
}
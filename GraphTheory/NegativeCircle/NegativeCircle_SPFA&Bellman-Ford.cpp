#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

const int maxn = 2020;//最大顶点数
const int maxm = 3010;//最大边数
const long long int INF = 214748364700000;//足够大才行
int n, m;

struct Edge
{
	int from, to, dist;//起始点,终点,两点距离（权值）
	Edge(int u, int v, int w) :from(u), to(v), dist(w) {}//构造函数,初始化,类比class
};//定义边结构体

struct NegativeCircle
{
	vector<Edge>edges;
	vector<int>G[maxn];//图的邻接表存储
	bool final[maxn];//final[v]=true当且仅当v∈S,即已经求得v0到v的最短路径,兼标记数组
	long long int D[maxn];//某点到其余的点的距离
	int enqueue[maxn];//顶点进(出)队列次数,在SPFA中用于判断是否有负权环出现

	/*初始化邻接表和边,及距离*/
	void init(int n)
	{
		for (int i = 0; i < n; i++)
			G[i].clear();
		edges.clear();

	}

	/*向图中添加边*/
	void AddEdge(int from, int to, int dist)
	{
		edges.push_back(Edge(from, to, dist));
		int m = edges.size();//m-1=边的编号
		G[from].push_back(m - 1);//G存起点from对应的边的编号,从而可以找到对应
	}	                         //的edges[]数组中点和权值的信息

	bool Bellman_Ford(int u0)
	{
		for (int i = 1; i <= n; i++)
			D[i] = INF;
		D[u0] = 0;
		bool neg_loop = false;//判断有无负权环
		//bool flag = false;//判断D[]是否已经都为确定值

		//进行n-1次松弛操作O(nm)
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < edges.size(); j++)
			{
				Edge &e = edges[j];
				D[e.to] = min(D[e.from] + e.dist, D[e.to]);
				/*if (D[e.from] + e.dist < D[e.to])
				{
					D[e.to] = D[e.from] + e.dist;
					flag = true;
				}*/
			}
			//if (!flag)
			//break;//如果D[]已经全部确定,跳出循环
		}

		//检测负权回路,上面的操作保证没有负权回路的存在，
		//如果找到了更短的路径，则说明存在负权回路
		for (int i = 0; i < edges.size(); i++)
		{
			Edge &e = edges[i];
			if (D[e.from] + e.dist < D[e.to])
			{
				neg_loop = true;//存在负权环
				break;
			}
		}
		if (neg_loop)
			return false;
		else
			return true;
	}
	/*非连通图也可判断*/
	bool SPFA(int u0)
	{
		for (int i = 1; i <= n; i++)
			D[i] = INF;
		D[u0] = 0;
		memset(final, false, sizeof(final));
		memset(enqueue, 0, sizeof(enqueue));
		queue<int>q;
		q.push(u0);
		final[u0] = true;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			final[u] = false;
			enqueue[u]++;
			if (enqueue[u] == n)
				return false;//有负权环
			for (int i = 0; i < G[u].size(); i++)
			{
				Edge &e = edges[G[u][i]];
				if (D[e.from] + e.dist < D[e.to])
				{
					D[e.to] = D[e.from] + e.dist;
					if (!final[e.to])
					{
						final[e.to] = true;
						q.push(e.to);
					}
				}
			}
		}
		return true;
	}

};
int main()
{
	//freopen("testdata1.in","r",stdin);
	//freopen("testdata1.out","w",stdout);
	int t;
	NegativeCircle NC;
	int i = 0;
	cin>>t;
	while (t--)
	{
		cin>>n>>m;
		NC.init(n);
		for (int i = 0; i < m; i++)
		{
			int u, v, w;
			cin >> u >> v >> w;//scanf("%d%d%d", &u, &v, &w);
			if (w < 0)
				NC.AddEdge(u, v, w);
			else
			{
				NC.AddEdge(u, v, w);
				NC.AddEdge(v, u, w);
			}
		}
		if (NC.Bellman_Ford(1))
			cout<<"NO"<<endl;
		else
			cout<<"YES"<<endl;
	}
	return 0;
}
/*Bellman_Ford算法
下测试点不正确，因为缺少了1这个点
1
4 3
2 3 -1
3 4 -1
4 2 -1
NO
*/
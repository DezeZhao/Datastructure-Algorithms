#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

const int maxn = 1000;//最大顶点数
const int maxm = 1000;//最大边数
const int INF = 1000000;
int n, m;
//int u[maxn], v[maxn], w[maxm];//起点,终点,权值
/*在一个含有n个顶点的图中，任意两点之间的最短路径最多包含n-1条边，
最短路径中不可能包含回路。因为最短路径是一个不包含回路的简单路径，
回路分为正权回路(回路权值之和为正)和负权回路(回路权值之和为负)。
如果最短路径中包含正权回路，那么去掉这个回路，一定可以得到更短的路径；
如果最短路径中包含负权回路，那么肯定没有最短路径，因为每多走一次
负权回路就可以得到更短的路径. 因此最短路径肯定是一个不包含回路的
最短路径，即最多包含n-1条边。
对于边3-2，它可以使3-1变成3-2-1，从而使其距离变短，此过程称为松弛。
（松弛点数，拉紧距离）即w[3-2]+w[2-1]<w[3-1]*/

struct Edge
{
	int from, to, dist;//起始点,终点,两点距离（权值）
	Edge(int u, int v, int w) :from(u), to(v), dist(w) {}//构造函数,初始化,类比class
};//定义边结构体

struct HeapNode
{
	int dist, u;//权值,起点
	bool operator < (const HeapNode &node) const
	{
		return dist > node.dist;//最小值优先
	}
};

struct ShortestPath
{
	vector<Edge>edges;
	vector<int>G[maxn];//图的邻接表存储
	bool final[maxn];//final[v]=true当且仅当v∈S,即已经求得v0到v的最短路径,兼标记数组
	int D[maxn];//某点到其余的点的距离
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

	/*朴素Dijstra算法*/
	void Simple_Dijstra(int u0)//u0为源点
	{
		memset(final, false, sizeof(final));
		for (int i = 1; i <= n; i++)
			D[i] = INF;
		D[u0] = 0;//源点到自身的距离为0
		final[u0] = true;
		for (int i = 0; i < G[u0].size(); i++)
		{
			Edge &e = edges[G[u0][i]];//引用,起别名
			D[e.to] = min(e.dist, D[e.to]);
		}
		for (int i = 0; i < n; i++)//求最短路径,时间复杂度为O(nm)
		{
			int v0 = 0;
			int Min = INF;
			for (int j = 0; j < n; j++)
				if (!final[j] && D[j] < Min)
				{
					Min = D[j];
					v0 = j;
				}
			final[v0] = true;//目的点
			/*更新当前最短距离D[],即松弛relax操作*/
			for (int k = 0; k < G[v0].size(); k++)
			{
				Edge &e = edges[G[v0][k]];
				if (!final[e.to] && e.dist + Min < D[e.to])
					D[e.to] = e.dist + Min;
			}
		}
	}

	/*                       优先队列(堆)优化的Dijstra算法
	Dijstra的思想是每次在dist里面找到最小的那一条边，然后用最小的那条边去松弛其他的边，
	在此将dist存在priority_queue里面，每次通过优先队列得到dist最小的那条边,然后通过邻
	接表去松弛与这条边相连的其他的边，再将更新的dist存入优先队列，直到队列空时结束*/
	void Priority_queue_Dijstra(int u0)
	{
		memset(final, false, sizeof(final));
		for (int i = 1; i <= n; i++)
			D[i] = INF;
		priority_queue<HeapNode>pq;
		D[u0] = 0;
		pq.push(HeapNode { 0, u0 }); //源点对应的权值和from点进队列
		while (!pq.empty())//求最短路径,O(nlogn);
		{
			HeapNode node = pq.top();
			pq.pop();
			int u = node.u;
			if (final[u])continue;
			final[u] = true;
			for (int i = 0; i < G[u].size(); i++)
			{
				Edge &e = edges[G[u][i]];
				if (D[e.to] > D[u] + e.dist)
				{
					D[e.to] = D[u] + e.dist;
					pq.push(HeapNode { D[e.to],e.to });
				}
			}
		}
	}
	/*                              Bellman-Ford算法
	原理是对图进行最多V-1次松弛操作,得到所有可能的最短路径。优于迪科斯彻算法的方
	面是边的权值可以为负数、实现简单,缺点是时间复杂度过高,高达O(VE)。但算法可以
	进行若干种优化,提高了效率。

	思路上与狄克斯特拉算法(Dijkstra algorithm)最大的不同是每次都是从源点u0重新出
	发进行"松弛"更新操作,而Dijkstra则是从源点出发向外扩逐个处理相邻的节点，不会去
	重复处理节点，这边也可以看出Dijkstra效率相对更高点。

	判断出图是否存在负环路.但存在负环路的情况下不支持计算出各个节点的最短路径。只
	需要在结束(n-1)次遍历后,再执行一次遍历,若还可以更新数据则说明存在负环路(如果一
	个图没有负权回路，那么最短路径所包含的边最多为n-1条，即进行n-1轮松弛操作后最
	短路不会再发生变化。如果在n-1轮松弛后最短路仍然可以 发生变化，则这个图一定有负权回路)

	场景
	1.从起点出发是否存在到达各个节点的路径。
	2.从起点出发到达各个节点最短路径。
	3.是否存在负环路。
	负权环：图上一个点到图上另一个点的一个环，环上权重和为负数。

	代码中注释行有一个小小的时间优化，即提前退出循环;*/
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
	/*                   SPFA算法:Bellman-Ford算法的队列优化
	适用于权值有负值,且没有负圈的图的单源最短路径,复杂度O(kE),k为每个节点进入Queue的次数,
	且k一般<=2,所以实际SPFA的复杂度一般为O(E)。期望时间复杂度:O(kE),其中k为所有顶点进队的
	平均次数，可以证明m一般小于等于2n;（除非数据点专门卡SPFA，通常m都不大）

	SPFA算法核心的循环的提前跳出：在实际操作中,Bellman-Ford算法经常会在未达到n-1次前就出解,
	n-1其实是最大值。于是可以在循环中设置判定，在某次循环不在进行松弛的时候直接退出循环，
	进行负权环的判定。

	具体做法是用一个队列保存待松弛的点，然后对于每个出队的点依次遍历每个与他有边相邻的点
	(邻接表效率较高)如果该点可以松弛,并且队列中没有该点,就将其入队列，如此迭代直到队列为空。

	SPFA,要从Bellman-Ford的优化说起。在n个点m条边的图中, Bellman-Ford的复杂度是n*m,依次对
	每条边进行松弛操作,重复这个操作n-1次后则一定得到最短路,这是因为最长的没有环路的路,也只
	不过是n个点n-1条边构成的,又因为每次循环,至少relax一边所以最多n-1次就一定能得到最短路。

	SPFA的意义在于,如果一个点上次没有被松弛过,那么下次就不会从这个点开始松弛。每次把被松
	弛过的点加入到队列中,就可以忽略掉没有被松弛过的点。算法的核心在于队列优化Bellman-Ford,
	利用了每个点不会更新次数太多的特点发明的此算法。

	(Bellman-Ford算法中,其实每实施一轮松弛操作,就会有一些顶点已经求得其最短路,即这些顶点
	的最短路的"估计值"变为"确定值"。此后这些顶点的最短路的值就会一直保持不变,不再受后续轮
	松弛操作的影响.但是，每次还是会判断是否需要松弛,即更新,在此浪费了时间,而SPFA算法正是
	针对这一点进行了优化。)*/
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
	freopen("testdata.in", "r", stdin);
	freopen("testdata.out", "w", stdout);
	int k;
	cin >> n >> m>> k;//输入顶点数和边数
	ShortestPath SP;
	SP.init(n);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;//scanf("%d%d%d", &u, &v, &w);
		SP.AddEdge(u, v, w);
		SP.AddEdge(v, u, w);//无向图
	}

	SP.Simple_Dijstra(k);
	cout << "Simple Dijstra Algorithm:" << endl;
	for (int i = 0; i < n; i++)
		cout << SP.D[i + 1] << " ";//printf("%d\n",SP.D[w]);
	cout << endl;


	/*SP.Priority_queue_Dijstra(k);
	cout << "Priority_queue Optimized Dijstra Algorithm:" << endl;
	for (int i = 0; i < n; i++)
		cout << SP.D[i + 1] << " ";
	cout << endl;

	cout << "Bellman-Ford Algorithm:" << endl;
	if (SP.Bellman_Ford(k))
		for (int i = 0; i < n; i++)
			cout << SP.D[i + 1] << " ";
	else
		cout << "Graph contains negative-weight cycle!";
	cout << endl;

	cout << "SPFA Algorithm:" << endl;
	if (SP.SPFA(k))
		for (int i = 0; i < n; i++)
			cout << SP.D[i + 1] << " ";
	else
		cout << "Graph contains negative-weight cycle!";
	cout << endl;*/
	return 0;
}



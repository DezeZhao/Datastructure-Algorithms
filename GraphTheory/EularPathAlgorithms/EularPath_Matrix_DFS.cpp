#include<iostream>
#include<stack>
#include<algorithm>

using namespace std;

const int maxn = 2000;//最大顶点数
const int maxm = 3000;//最大边数
int n, m;
stack<int>s;
int G[maxn][maxn];
//int degree[maxn];//存每个点度

/*Hierholzer算法(逐步插入回路法，dfs核心思想)*/
void DFS(int u)
{
	for (int v = 1; v <=n; v++)
		if (G[u][v])
		{
			G[u][v]--;
			G[v][u]--;
			DFS(v);
		}
	s.push(u);//存放Eularian path/cycle
}

void PrintEularPath()
{
	while (!s.empty())
	{
		cout << s.top() << endl;
		s.pop();
	}
	cout << endl;
}

int main()
{
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		n = max(max(u, v), n);
		G[u][v]++;
		G[v][u]++;
		G[u][0]++;//计算顶点的度
		G[v][0]++;
	}
	int u=1,i;
	for (i = 1; i <= n; i++)
		if (G[i][0] & 1)
		{
			u=i;
			break;//度为奇数
		}
	DFS(u);//从奇度点开始搜索；没奇度点从1开始
	PrintEularPath();
	return 0;
}

#include<iostream>
using namespace std;

const int maxn=1000;
const int INF=10000000;
int n,m;
int G[maxn][maxn];
int D[maxn][maxn];//×î¶ÌÂ·¾¶±í
void Floyd()
{
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			D[i][j]=G[i][j];
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				if(D[i][j]>D[i][k]+D[k][j])
					D[i][j]=D[i][k]+D[k][j];
}
int main()
{
	freopen("testdata1.in","r",stdin);
	freopen("testdata1.out","w",stdout);
	int k;
	cin>>n>>m;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(i==j)
				G[i][j]=0;
			else
				G[i][j]=INF;
	for(int i=1; i<=m; i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		G[u][v]=w;
		G[v][u]=w;
	}
	Floyd();
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
			cout<<D[i][j]<<"\t";
		cout<<endl;
	}
	cout<<endl;
	return 0;
}
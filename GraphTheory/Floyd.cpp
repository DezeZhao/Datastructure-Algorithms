#include<iostream>
using namespace std;
typedef int VertexType;
#define MAX_VERTEX_NUM 20
#define INFINITY 65535
int num[MAX_VERTEX_NUM] = { 0 };
//typedef enum { DG, DN, UDG, UDN } GrapgKind;
typedef  int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
//邻接矩阵类型
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];      //顶点表
	AdjMatrix arcs;     //邻接矩阵
	int vexnum, arcnum;  //图的顶点数和边/弧数
	int Graphkind;
}  MGraph;
typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //最短路径数组
typedef  int ShortPathTable[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 	 //最短路径长度
int LocateVertex(MGraph &G, VertexType v)
{
	int i;
	for (i = 1; i <= G.vexnum; i++)
		if (v == G.vexs[i])
			return i;
	return -1;
}
void CreateGraph(MGraph &G)
{
	int i, j, k;
	VertexType v1, v2;
	int w;
	int n, m;
	cin >> n >> m;
	G.vexnum = n;
	G.arcnum = m;
	for (i = 1; i <= G.vexnum; i++)
		G.vexs[i] = i;
	for (i = 1; i <= G.vexnum; i++)
		for (j = 1; j <= G.vexnum; j++)
			G.arcs[i][j] = INFINITY;
	for (k = 0; k < G.arcnum; k++)
	{
		cin >> v1 >> v2 >> w;
		i = LocateVertex(G, v1);
		j = LocateVertex(G, v2);
		G.arcs[i][j] = w;
	}
}
void ShortestPath_FLOYD(MGraph G, PathMatrix P[], ShortPathTable &D) {
	// 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其
	  // 带权长度D[v][w]。若P[v][w][u]为TRUE，则u是从v到w当前求得最
	  // 短路径上的顶点。
	int v, w, u, i;
	for (v = 0; v < G.vexnum; ++v) // 初始化已知路径及距离
		for (w = 0; w < G.vexnum; ++w) {
			D[v][w] = G.arcs[v][w];
			for (u = 0; u < G.vexnum; ++u) P[v][w][u] = 0;
			if (D[v][w] < INFINITY) {     // 从v到w有直接路径
				P[v][w][v] = P[v][w][w] = 1;
			}//if
		}//for
	for (u = 0; u < G.vexnum; ++u)
		for (v = 0; v < G.vexnum; ++v)
			for (w = 0; w < G.vexnum; ++w)
				if (D[v][u] + D[u][w] < D[v][w]) {  // 从v经u到w的一条路径更短
					D[v][w] = D[v][u] + D[u][w];
					for (i = 0; i < G.vexnum; ++i)
						P[v][w][i] = (P[v][u][i] || P[u][w][i]);
				}//if
} // ShortestPath_FLOYD

int main()
{
	MGraph G;
	int v0;
	cin >> v0;
	ShortPathTable D;
	PathMatrix P[MAX_VERTEX_NUM];
	CreateGraph(G);
	ShortestPath_FLOYD(G, P, D);
	system("pause");
}

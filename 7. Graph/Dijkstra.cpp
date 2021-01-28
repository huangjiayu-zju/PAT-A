#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxv = 1000; //最大顶点数
const int INF = 0x3fffffff;

//一、邻接矩阵版，适用于顶点数目不大（V不超过1000的情况）,并且记录最短路径
int n, G[maxv][maxv];   //n为顶点数，maxv为最大顶点数
int d[maxv];    //起点到达各顶点的最短路径长度
int pre[maxv];  //prev[v]表示从起点到顶点v的最短路径上v的前一个顶点（求最短路径）
bool vis[maxv] = {false};   //标记数组，true表示已访问，初值为false

void Dijkstra(int s){   //s为起点
    fill(d, d + maxv, INF); //慎用memset
    for (int i = 0; i < n; i++){    //初始化设每个点的前驱为自身（求最短路径）
        pre[i] = i;
    }
    d[s] = 0;
    for (int i = 0; i < n; i++){    //1. 循环n次
        int u = -1, min = INF;      //2. u使d[u]最小，min存放最小的d[u]
        for (int j = 0; j < n; j++){    //找到未访问的顶点中d[]最小的
            if(vis[j] == false && d[j] < min){
                u = j;
                min = d[j];
            }
        }
        if(u == -1){    //找不到小于INF的d[u]，说明剩下的顶点和s不连通
            return;
        }
        vis[u] = true;  //3.标记u为已访问
        for (int v = 0; v < n; v++){    //4.遍历所有顶点v
            //如果v未被访问&&u能到达v&&以u为中介点可以使d[v]更优
            if(vis[v] == false && G[u][v] != INF && d[u] + G[u][v] < d[v]){
                d[v] = d[u] + G[u][v];  //优化d[v]
                pre[v] = u; //记录v的前驱结点是u（求最短路径）
            }
        }
    }    
}

//输出最短路径
void DFS(int s, int v){ //s为起点编号，v为当前访问的顶点编号（从终点开始递归）
    if(v == s){ //如果当前已经到达起点s，则输出起点并返回
        printf("%d\n", s);
        return;
    }
    DFS(s, pre[v]); //递归访问v的前驱节点pre[v]
    printf("%d\n", v);  //从最深处return回来之后，输出每一层的顶点号
}

//二、邻接表法
struct Node{
    int v;      //边的目标顶点
    int dis;    //边权
};
vector<Node> Adj[maxv]; //图G，Adj[u]存放从顶点u出发可以到达的所有顶点
int n, d[maxv];
bool vis[maxv] = {false};

void Dijkstra(int s){
    fill(d, d + maxv, INF);
    d[s] = 0;
    for (int i = 0; i < n; i++){
        int u = -1, min = INF;
        for (int j = 0; j < n; j++){
            if(vis[u] == false && d[u] < min){
                u = j;
                min = d[u];
            }
        }
        if(u == -1){
            return;
        }
        vis[u] = true;
        //只有下面这个for与邻接矩阵写法不同
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;    //通过邻接表直接获得u能到达的顶点v
            if(vis[v] == false && d[u] + Adj[u][j].dis < d[v]){
                d[v] = d[u] + Adj[u][j].dis;
            }
        }
    }
}


#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxv = 1000; //最大顶点数
const int INF = 0x3fffffff;

//一、Prim邻接矩阵版，备注部分表示与Dijkstra算法的区别

int n, G[maxv][maxv];   
int d[maxv];        //顶点与集合S的最短距离
bool vis[maxv] = {false};   

int Prim(int s){    //s为初始点，默认为0号，函数返回最小生成树的边权之和
    fill(d, d + maxv, INF); 
    d[s] = 0;
    int ans = 0; //存放最小生成树的边权之和
    for (int i = 0; i < n; i++){   
        int u = -1, min = INF;      
        for (int j = 0; j < n; j++){    
            if(vis[j] == false && d[j] < min){
                u = j;
                min = d[j];
            }
        }
        if(u == -1){    
            return;
        }
        vis[u] = true;
        ans += d[u];//将与集合S距离最小的边加入最小生成树
        for (int v = 0; v < n; v++){     
            if(vis[v] == false && G[u][v] != INF && G[u][v] < d[v]){//以u为中介点可以使v离集合S更近
                d[v] = G[u][v];  //将G[u][v]赋值给d[v]
            }
        }
    }
    return ans;
}

//二、Prim邻接表版
struct Node{
    int v;      
    int dis;    
};
vector<Node> Adj[maxv]; 
int n, d[maxv]; //顶点与集合S的最短距离
bool vis[maxv] = {false};

int Prim(int s){
    fill(d, d + maxv, INF);
    d[s] = 0;
    int ans = 0; //存放最小生成树的边权之和
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
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;    
            if(vis[v] == false && Adj[u][j].dis < d[v]){//以u为中介点可以使v离集合S更近
                d[v] = G[u][v];//将G[u][v]赋值给d[v]
            }
        }
    }
}


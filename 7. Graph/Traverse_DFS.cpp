#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int maxv = 1000;  //最大顶点数
const int INF = 1000000000; //设INF为一个很大的数

//一、DFS遍历图邻接矩阵版
int n, G[maxv][maxv];   //n为顶点数，maxv为最大顶点数
bool vis[maxv] = {false};   //顶点i未被访问

void DFS(int u, int depth){ //u为当前访问的顶点标号，depth为当前深度
    vis[u] = true;
    //如果需要对u做一些操作，可以在这里进行
    //下面对所有从u出发能到达的分支结点进行枚举
    for (int v = 0; v < n; v++){    //对每个顶点v
        if(vis[v] == false && G[u][v] != INF){  //如果v未被访问，且u可到达v
            DFS(v, depth + 1);  //访问v，深度加1
        }
    }
}

void DFSTrave(){    //遍历图G
    for (int u = 0; u < n; u++){
        if(vis[u] == false){
            DFS(u, 1);  //访问u和u所在的连通块，1表示初始为第一层
        }
    }
}

//二、DFS遍历图邻接表版
vector<int> Adj[maxv]; //图G的邻接表
int n;
bool vis[maxv] = {false};

void DFS(int u, int depth){
    vis[u] = true;
    //对u操作
    for (int i = 0; i < Adj[u].size(); i++){
        int v = Adj[u][i];  //u的子结点
        if(vis[v] == false){
            DFS(v, depth + 1); 
        }
    }
}

void DFSTrave(){
    for (int u = 0; u < n; u++){
        if(vis[u] == false){
            DFS(u, 1);
        }
    }
}


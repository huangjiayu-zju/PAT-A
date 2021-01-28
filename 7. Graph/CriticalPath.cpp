#include<cstdio>
#include<stack>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxv = 1010;

struct node{
    int v;//后继结点
    int w;//权重
};
vector<node> G[maxv];//邻接表
int n, inDegree[maxv], ve[maxv], vl[maxv];//顶点数、每个结点的入度


//拓扑序列
stack<int> topOrder;
//拓扑排序，顺便求ve数组
bool topologicalSort(){
    queue<int> q;
    for (int i = 0; i < n; i++){
        if(inDegree[i] == 0){
            q.push(i);  
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        topOrder.push(u);   //将u加入拓扑序列
        for (int i = 0; i < G[u].size(); i++){
            int v = G[u][i].v;//u的i号后继结点编号为v
            inDegree[v]--;  
            if(inDegree[v] == 0){
                q.push(v);
            }
            //用ve[u]来更新u的所有后继结点v
            if(ve[u] + G[u][i].w > ve[v]){
                ve[v] = ve[u] + G[u][i].w;
            }
        }
    }
    if(topOrder.size() == n){   
        return true;
    }else{
        return false;
    }
}

//关键路径，不是有向无环图返回-1，否则返回关键路径长度
int CriticalPath(){
    memset(ve, 0, sizeof(ve));  //ve数组初始化
    if(topologicalSort() == false){
        return -1;  //不是有向无环图，返回-1
    }
    fill(vl, vl + n, ve[n - 1]); //vl数组初始化，初始值为汇点的ve值
    //直接使用topOrder出栈即为逆拓扑序列，求解vl数组
    while(!topOrder.empty()){
        int u = topOrder.top();
        topOrder.pop();
        for (int i = 0; i < G[u].size(); i++){
            int v = G[u][i].v;
            //用u的所有后续结点v的vl值来更新vl[u]
            if(vl[v] - G[u][i].w < vl[u]){
                vl[u] = vl[v] - G[u][i].w;
            }
        }
    }
    //遍历邻接表的所有边，计算活动的最早开始时间e和最迟开始时间l
    for (int u = 0; u < n; u++){
        for (int i = 0; i < G[u].size(); i++){
            int v = G[u][i].v, w = G[u][i].w;
            int e = ve[u], l = vl[v] - w;
            if(e == l){ //说明活动u->v是关键活动 
                printf("%d->%d\n", u, v);
            }
        }
    }
    return ve[n - 1];   //返回关键路径长度
}
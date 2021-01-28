#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int maxv = 1010;

vector<int> G[maxv];//邻接表
int n, inDegree[maxv];//顶点数、每个结点的入度

//拓扑排序
bool topologicalSort(){
    int num = 0;        //记录加入拓扑序列的顶点数
    queue<int> q;
    for (int i = 0; i < n; i++){
        if(inDegree[i] == 0){
            q.push(i);  //将所有入度为0的结点入队
        }
    }
    while(!q.empty()){
        int u = q.front();//取队首结点u
        // printf("%d",u);//此处可输出顶点u，作为拓扑序列中的顶点
        q.pop();
        for (int i = 0; i < G[u].size(); i++){
            int v = G[u][i];//u的后继结点v
            inDegree[v]--;  //顶点v的入度减1
            if(inDegree[v] == 0){//顶点v的入度减为0则入队
                q.push(v);
            }
        }
        G[u].clear(); //清空顶点u的所有出边(如无必要可以不写)
        num++;  //加入拓扑序列的顶点数加1
    }
    if(num == n){   //加入拓扑序列的顶点数为1，说明拓扑排序成功
        return true;
    }else{
        return false;
    }
}
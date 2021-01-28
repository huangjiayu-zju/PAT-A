#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxv = 1000; //最大顶点数
const int INF = 0x3fffffff;

//三、Dijkstra+DFS的模板写法
int n, G[maxv][maxv];   
int d[maxv];    
vector<int> pre[maxv];  
bool vis[maxv] = {false};   

void Dijkstra(int s){   
    fill(d, d + maxv, INF); 
    // for (int i = 0; i < n; i++){    //pre数组一开始不需要赋初值
    //     pre[i] = i;
    // }
    d[s] = 0;
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
        for (int v = 0; v < n; v++){    
            if(vis[v] == false && G[u][v] != INF){
                if(d[u] + G[u][v] < d[v]){
                    d[v] = d[u] + G[u][v];
                    pre[v].clear();       //清空pre[v]
                    pre[v].push_back(u);  //令v的前驱为u
                }else if(d[u] + G[u][v] == d[v]){
                    pre[v].push_back(u);  
                }
            }
        }
    }    
}

//遍历所有最短路径，找出一条使第二标尺最优的路径。以计算最短路径上的最短花费为例
int st; //路径的起点
int optValue;   //第二标尺最优值
int value[maxv][maxv];  //value[][]为第二标尺矩阵，这里看作是结点a->b的花费矩阵
vector<int> path, tempPath; //最优路径、临时路径

void DFS(int v){    //v为当前访问结点
    //递归边界
    if(v == st){    //如果到达了叶子结点st，即路径的起点
        tempPath.push_back(v);  //将起点st加入临时路径tempPath的最后面
        int tempValue = 0;      //存放临时路径tempPath的第二标尺的值
        //计算路径tempPath上的value值（根据题意修改）
        for (int i = tempPath.size() - 1; i > 0; i--){      //倒着访问
            int id = tempPath[i], idNext = tempPath[i - 1]; //当前结点和下个结点
            tempValue += value[id][idNext];                 //增加边id->idNext的边权
        }
        //如果value优于optValue
        if(tempValue < optValue){   //这里指如果当前路径的边权更小（根据题意修改）
            optValue = tempValue;   //更新第二标尺最优值和路径
            path = tempPath;
        }
        tempPath.pop_back();        //将刚刚加入的结点删除
        return;
    }
    //递归式
    tempPath.push_back(v);  //将当前访问结点加入临时路径tempPath的最后面
    for (int i = 0; i < pre[v].size(); i++){
        DFS(pre[v][i]);   //结点v的前驱结点pre[v][i]，递归
    }
    tempPath.pop_back();    //遍历完所有前驱结点，将当前结点v删除
}

#include<cstdio>
#include<vector>
#include<set>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxv = 1000;
const int INF = 0x3fffffff;

//邻接表实现的Bellman-Ford算法
struct Node{
    int v, dis; //v为邻接边的目标顶点，dis为邻接边的边权
    Node(int _v, int _dis) : v(_v), dis(_dis) {}    //构造函数
};
vector<Node> Adj[maxv]; //图G的邻接表
int n, d[maxv];//n为顶点数，d[]为起点到达各点的最短路径长度

bool Bellman(int s){    //s为源点
    fill(d, d + maxv, INF);
    d[s] = 0;
    //以下为求解数组d的部分
    for (int i = 0; i < n - 1; i++){    //执行n-1轮操作，n为顶点数
        for (int u = 0; u < n; u++){    //每轮操作都遍历所有边
            for (int j = 0; j < Adj[u].size(); j++){
                int v = Adj[u][j].v;    //邻接边的顶点
                int dis = Adj[u][j].dis;//邻接边的边权
                if(d[u] + dis < d[v]){  
                    d[v] = d[u] + dis;  //松弛操作
                }
            }
        }
    }
    //以下为判断负环的代码
    for (int u = 0; u < n; u++){        //对每条边进行判断
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;
            int dis = Adj[u][j].dis;
            if(d[u] + dis < d[v]){      //如果可以被松弛
                return false;           //说明图中有从源点可达的负环
            }
        }
    }
    return true;                        //数组d的所有值都已经达到最优
}

//SPFA
vector<Node> Adj[maxv]; //图G的邻接表
int n, d[maxv], num[maxv];//num数组记录顶点的入队次数
bool inq[maxv];

bool SPFA(int s){
    //初始化部分
    memset(inq, false, sizeof(inq));
    memset(num, 0, sizeof(num));
    fill(d, d + maxv, INF);
    //源点入队部分
    queue<int> q;   
    q.push(s);      //源点入队
    inq[s] = true;  //源点已入队
    num[s]++;       //源点入队次数加1
    d[s] = 0;       //源点的d值为0
    //主体部分
    while (!q.empty()){
        int u = q.front();  //队首顶点编号为u
        q.pop();            //出队
        inq[u] = false;     //设置u为不在队列中
        //遍历u的所有邻接边v
        for (int j = 0; j < Adj[u].size(); j++){
            int v = Adj[u][j].v;
            int dis = Adj[u][j].dis;
            //松弛操作
            if(d[u] + dis < d[v]){  
                d[v] = d[u] + dis;
                if(!inq[v]){    //如果v不在队列中
                    q.push(v);  //v入队
                    inq[v] = true;//设置v在队列中
                    num[v]++;   //v的入队次数加1
                    if(num[v] >= n){//有可达负环
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
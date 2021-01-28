#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 510;
const int INF = 0x3fffffff;

int n, m, st, ed;
int G[maxn][maxn], weight[maxn];//邻接矩阵与点权
int d[maxn], num[maxn], w[maxn];//d[]最短距离，num[]最短路径条数，w[]最大点权之和
bool vis[maxn] = {false};

void Dijkstra(int s){
    fill(d, d + n, INF);
    fill(num, num + n, 0);
    fill(w, w + n, 0);
    d[s] = 0, num[s] = 1, w[s] = weight[s];
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
                if(d[u] + G[u][v] < d[v]){  //以u为中介点时能令d[v]变小
                    d[v] = d[u] + G[u][v];  //覆盖d[v]
                    num[v] = num[u];        //覆盖num[v]
                    w[v] = w[u] + weight[v];//覆盖w[v]
                }
                else if(d[u] + G[u][v] == d[v]){    //找到一条相同长度的路径
                    if(w[u] + weight[v] > w[v]){    //以u为中介点时点权之和更大
                        w[v] = w[u] + weight[v];    //w[v]继承自w[u]
                    }
                    num[v] += num[u];               //最短路径条数与点权无关，写在外面
                }
            }
        }        
    }
}

int main(){
    int c1, c2, l;
    scanf("%d%d%d%d", &n, &m, &st, &ed);
    for (int i = 0; i < n; i++){
        scanf("%d", &weight[i]);
    }
    fill(G[0], G[0] + maxn * maxn, INF);//初始化二维数组写法
    for (int i = 0; i < m; i++){
        scanf("%d%d%d", &c1, &c2, &l);
        G[c1][c2] = l;
        G[c2][c1] = l;
    }
    Dijkstra(st);
    printf("%d %d", num[ed], w[ed]);
    return 0;
}

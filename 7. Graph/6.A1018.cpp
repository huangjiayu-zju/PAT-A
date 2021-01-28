#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxv = 510;
const int INF = 0x3fffffff;

int n, m, cmax, sp, numPath, G[maxv][maxv], weight[maxv];
int d[maxv], minNeed = INF, minRemain = INF;//minNeed记录最少携带的数目，minRemain记录最少带回的数目
vector<int> pre[maxv];
vector<int> tempPath, path;
bool vis[maxv];

void Dijkstra(int s){
    fill(d, d + maxv, INF);
    d[s] = 0;
    for (int i = 0; i <= n; i++)
    {
        int u = -1, min = INF;
        for (int j = 0; j <= n; j++){
            if(vis[j] == false && d[j] < min){
                u = j;
                min = d[j];
            }
        }
        if(u == -1){
            return;
        }
        vis[u] = true;
        for (int v = 0; v <= n; v++){
            if(vis[v] == false && G[u][v] != INF){
                if(d[u] + G[u][v] < d[v]){
                    d[v] = d[u] + G[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }else if(d[u] + G[u][v] == d[v]){
                    pre[v].push_back(u);
                }
            }
        }
    }
}

void DFS(int v){
    if(v == 0){ //根结点为0
        tempPath.push_back(v);
        int need = 0, remain = 0;//路径tempPath上需要携带的数目、需要带回的数目
        for (int i = tempPath.size() - 1; i >= 0; i--){
            int id = tempPath[i];   //当前结点编号
            if(weight[id] > 0){      //点权大于0说明需要带走一部分自行车
                remain += weight[id];
            }else{                  //点权小于0，需要补给
                if(remain > abs(weight[id])){
                    remain -= abs(weight[id]);
                }else{
                    need += abs(weight[id]) - remain;   //  不够的部分从PBMC携带
                    remain = 0;
                }
            }
        }
        if(need < minNeed){ //需要从PBMC携带的自行车数目更少
            minNeed = need;
            minRemain = remain;
            path = tempPath;
        }else if(need == minNeed && remain < minRemain){//携带数目相同，带回数目更小
            minRemain = remain;
            path = tempPath;
        }
        tempPath.pop_back();
        return;
    }
    tempPath.push_back(v);
    for (int i = 0; i < pre[v].size(); i++)
    {
        DFS(pre[v][i]);
    }
    tempPath.pop_back();
}

int main(){
    scanf("%d%d%d%d", &cmax, &n, &sp, &m);
    int u, v;
    fill(G[0], G[0] + maxv * maxv, INF);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &weight[i]);
        weight[i] -= cmax / 2;
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &u, &v);
        scanf("%d", &G[u][v]);
        G[v][u] = G[u][v];
    }
    Dijkstra(0);
    DFS(sp);
    printf("%d ", minNeed);
    for (int i = path.size() - 1; i >= 0; i--){
        printf("%d", path[i]);
        if(i > 0){
            printf("->");
        }
    }
    printf(" %d", minRemain);
    return 0;
}

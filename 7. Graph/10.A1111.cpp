#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxv = 510;//最大顶点数
const int INF = 0x3fffffff;

//n为顶点数，m为边数，st和ed分别为起点和终点，G为距离矩阵，Time为时间矩阵
//d[]记录最短距离，t[]记录最少时间，minTime记录最短路径上的最小时间
//visD用于距离，visT用于时间，vis[i]=true表示已访问，初始为false
int n, m, st, ed, G[maxv][maxv], Time[maxv][maxv];
int d[maxv], t[maxv], minTime = INF;
bool visD[maxv] = {false}, visT[maxv] = {false};
vector<int> preD[maxv], preT[maxv];//前驱，分别用于距离和时间
vector<int> tempPath, pathD, pathT;//临时路径，最优路径

//s为源点，G为距离（或时间矩阵），d为最短距离（或时间）
//pre为前驱，vis为是否访问
void Dijkstra(int s, int G[][maxv], int d[], vector<int> pre[], bool vis[]){//二维数组作为参数第二维要写数目
    fill(d, d + maxv, INF);
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
                    pre[v].clear();
                    pre[v].push_back(u);
                }else if(d[u] + G[u][v] == d[v]){
                    pre[v].push_back(u);
                }
            }
        }
    }
}

//DFS中计算最优路径（用于距离）
void getFirstPath(){
    int tempTime = 0;//记录当前路径的时间和
    for (int i = tempPath.size() - 1; i > 0; i--){//倒着访问
        int id = tempPath[i], idNext = tempPath[i - 1];
        tempTime += Time[id][idNext];
    }   
    if(tempTime < minTime){
        minTime = tempTime;
        pathD = tempPath;
    }
}

//DFS中计算最优路径（用于时间）
void getSecondPath(){
    if(pathT.size() == 0 || tempPath.size() < pathT.size()){
        pathT = tempPath;   //最优路径为空或者找到了顶点个数更小的路径时，更新pathT
    }
}

//求解最优路径，v为当前结点，pre为前驱数组，isFirstPath表示第一次求解还是第二次求解
void DFS(int v, vector<int> pre[], bool isFirstPath){
    if(v == st){//递归边界，到达叶子结点（路径起点）
        tempPath.push_back(v);
        if(isFirstPath){
            getFirstPath();
        }else{
            getSecondPath();
        }
        tempPath.pop_back();
        return;
    }
    tempPath.push_back(v);
    for (int i = 0; i < pre[v].size(); i++){
        DFS(pre[v][i], pre, isFirstPath);
    }
    tempPath.pop_back();
}

//打印路径
void printPath(vector<int> path){
    printf("%d", path.back());
    for (int i = path.size() - 2; i >= 0; i--){
        printf(" -> %d", path[i]);
    }
    printf("\n");
}

int main(){
    scanf("%d%d", &n, &m);
    int u, v, oneWay;
    fill(G[0], G[0] + maxv * maxv, INF);
    fill(Time[0], Time[0] + maxv * maxv, INF);
    for (int i = 0; i < m; i++){
        scanf("%d%d%d", &u, &v, &oneWay);
        scanf("%d%d", &G[u][v], &Time[u][v]);
        if(!oneWay){//双向
            G[v][u] = G[u][v];
            Time[v][u] = Time[u][v];
        }
    }
    scanf("%d%d", &st, &ed);
    Dijkstra(st, G, d, preD, visD);
    Dijkstra(st, Time, t, preT, visT);
    DFS(ed, preD, true);
    DFS(ed, preT, false);
    printf("Distance = %d", d[ed]);
    if(pathD == pathT){
        printf("; ");
    }else{
        printf(": ");
        printPath(pathD);
    }
    printf("Time = %d: ", t[ed]);
    printPath(pathT);
    return 0;
}
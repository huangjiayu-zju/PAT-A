#include<cstdio>
#include<algorithm>
using namespace std;
const int maxv = 200;
const int INF = 0x3fffffff;

int n, m;//n为顶点数，m为边数
int dis[maxv][maxv];//dis[i][j]表示顶点i和顶点j的最短距离

void Floyd(){
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if(dis[i][k] != INF && dis[k][j] != INF && dis[i][k] + dis[k][j] < dis[i][j]){
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

int main(){
    int u, v, w;
    fill(dis[0], dis[0] + maxv * maxv, INF);
    scanf("%d%d", &n, &m);  //顶点数n、边数m
    for (int i = 0; i < n; i++){
        dis[i][i] = 0;  //顶点i和顶点i的距离初始化为0
    }
    for (int i = 0; i < m; i++){
        scanf("%d%d%d", &u, &v, &w);
        dis[u][v] = w;  //以有向图为例进行输入
    }
    Floyd();
    for (int i = 0; i < n; i++){//输出dis数组
        for (int j = 0; j < n; j++){
            printf("%d ", dis[i][j]);
        }
        printf("\n");
    }
    return 0;
}
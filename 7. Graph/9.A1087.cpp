#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#include<string>
using namespace std;
const int maxv = 210;
const int INF = 0x3fffffff;

int n, m, st, G[maxv][maxv], weight[maxv];
int d[maxv], w[maxv], num[maxv], pt[maxv], pre[maxv];//d[]最短花费(距离)，w[]最大幸福值(点权值)，num[]最短路径条数，pt[]最短路径上顶点数，pre[]记录前驱
bool vis[maxv] = {false};
map<string, int> cityToIndex;
map<int, string> indexToCity;

void Dijkstra(int s){
    fill(d, d + maxv, INF);
    memset(w, 0, sizeof(w));
    memset(num, 0, sizeof(num));
    memset(pt, 0, sizeof(pt));
    for (int i = 0; i < n; i++){
        pre[i] = i;
    }
    d[s] = 0;
    num[s] = 1;
    for (int i = 0; i < n; i++){
        int u = -1, min = INF;
        for (int j = 0; j < n;j++){
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
                if(d[u] + G[u][v] < d[v]){              //以u为中介点使d[v]更优
                    d[v] = d[u] + G[u][v];
                    w[v] = w[u] + weight[v];
                    num[v] = num[u];
                    pt[v] = pt[u] + 1;                    
                    pre[v] = u;
                }else if(d[u] + G[u][v] == d[v]){       //找到长度相同的路径
                    num[v] += num[u];                   //注意这里是继承不是覆盖num[u]
                    if(w[v] < w[u] + weight[v]){        //以u为中介点使w[v]更优
                        w[v] = w[u] + weight[v];
                        pt[v] = pt[u] + 1;
                        pre[v] = u;
                    }else if(w[v] == w[u] + weight[v]){ //找到相同点权之和的路径
                        double uAvg = 1.0 * (w[u] + weight[v]) / (pt[u] + 1);
                        double vAvg = 1.0 * w[v] / pt[v];
                        if(uAvg > vAvg){                //以u为中介使平均点权更大
                            pt[v] = pt[u] + 1;
                            pre[v] = u;
                        }
                    }                   
                }
            }
        }
    }
}

void printPath(int v){
    if(v == 0){
        cout << indexToCity[v];
        return;
    }
    printPath(pre[v]);
    cout << "->" << indexToCity[v];
}

int main(){
    string start, city1, city2;
    cin >> n >> m >> start;
    cityToIndex[start] = 0;
    indexToCity[0] = start;
    for (int i = 1; i <= n - 1; i++){
        cin >> city1 >> weight[i];
        cityToIndex[city1] = i;
        indexToCity[i] = city1;
    }
    fill(G[0], G[0] + maxv * maxv, INF);//初始化图G
    for (int i = 0; i < m; i++){
        cin >> city1 >> city2;
        int c1 = cityToIndex[city1];
        int c2 = cityToIndex[city2];
        cin >> G[c1][c2];
        G[c2][c1] = G[c1][c2];
    }
    Dijkstra(0);
    int rom = cityToIndex["ROM"];
    printf("%d %d %d %d\n", num[rom], d[rom], w[rom], w[rom] / pt[rom]);
    printPath(rom);
    return 0;
}
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxv = 1015;
const int INF = 0x3fffffff;

int n, m, k, ds, G[maxv][maxv];
int d[maxv];
bool vis[maxv] = {false};

void Dijkstra(int s){
    memset(vis, false, sizeof(vis));
    fill(d, d + maxv, INF);
    d[s] = 0;
    for (int i = 0; i < n + m; i++){
        int u = -1, min = INF;
        for (int j = 1; j <= n + m; j++){
            if(vis[j] == false && d[j] < min){
                u = j;
                min = d[j];
            }
        }
        if(u == -1){
            return;
        }
        vis[u] = true;
        for (int v = 1; v <= n + m; v++){
            if(vis[v] == false && G[u][v] != INF && G[u][v] + d[u] < d[v]){
                d[v] = d[u] + G[u][v];
            }
        }
    }
}

//将str[]转换为数字，若str是数字，则返回本身；否则返回去掉G之后的数加上n
int getID(char str[]){
    int i = 0, len = strlen(str), ID = 0;
    while(i < len){
        if(str[i] != 'G'){
            ID = ID * 10 + (str[i] - '0');
        }
        i++;
    }
    if(str[0] == 'G'){
        return n + ID;
    }else{
        return ID;
    }
}

int main(){
    scanf("%d%d%d%d", &n, &m, &k, &ds);
    int u, v, w;
    char city1[5], city2[5];
    fill(G[0], G[0] + maxv * maxv, INF);//别忘记初始化图G
    for (int i = 0; i < k; i++){
        scanf("%s %s %d", city1, city2, &w);
        u = getID(city1);
        v = getID(city2);
        G[u][v] = G[v][u] = w;
    }

    double ansDis = -1, ansAvg = INF;   //最大的最短距离，最小平均距离
    int ansID = -1;                     //最终加油站id
    for (int i = n + 1; i <= n + m; i++){//枚举所有加油站
        double minDis = INF, avg = 0;   //minDis为最大的最近距离，avg为平均距离
        Dijkstra(i);
        for (int j = 1; j <= n; j++){   //枚举所有居民房，求出minDis与avg
            if(d[j] > ds){              //存在距离大于DS的居民房，直接跳出
                minDis = -1;
                break;
            }
            if(d[j] < minDis){          //更新最近距离
                minDis = d[j];
            }
            avg += 1.0 * d[j] / n;
        }
        if(minDis == -1){               //存在距离大于ds的居民房，跳过该加油站
            continue;
        }
        if(minDis > ansDis){            //找出最大的最近距离
            ansID = i;
            ansDis = minDis;
            ansAvg = avg;
        }else if(minDis == ansDis && avg < ansAvg){//更新最小平均距离
            ansID = i;
            ansAvg = avg;
        }
    }
    if(ansID == -1){    //无解
        printf("No Solution\n");
    }else{
        printf("G%d\n", ansID - n);
        printf("%.1f %.1f\n", ansDis, ansAvg);
    }
    return 0;
}












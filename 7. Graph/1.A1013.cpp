#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxv = 1111;

vector<int> G[maxv];
bool vis[maxv] = {false};
int currentPoint;   //当前需要删除的顶点号

void dfs(int v){
    if(v == currentPoint){  //当遍历到已删除结点v时，返回
        return;
    }
    vis[v] = true;
    for (int i = 0; i < G[v].size(); i++){
        if(vis[G[v][i]] == false){
            dfs(G[v][i]);
        }        
    }
}

int main(){
    int n, m, k, a, b;
    int block; //连通块数目
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < m; i++){
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int query = 0; query < k; query++){
        scanf("%d", &currentPoint);
        memset(vis, false, sizeof(vis));    //初始化vis数组为false
        block = 0;
        for (int i = 1; i <= n ; i++)   //枚举每个顶点
        {
            if(i != currentPoint && vis[i] == false){
                dfs(i); //遍历顶点i所在的连通块
                block++;    //连通块个数加1
            }
        }
        printf("%d\n", block - 1);  //需要添加的边数等于连通块个数减1
    }

}
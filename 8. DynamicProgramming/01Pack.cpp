#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100;//物品最大件数
const int maxv = 1000;//容量V的上限

int w[maxn], c[maxn], dp[maxn];//每件物品的重量，价值
int main(){
    int n, V;
    scanf("%d%d", &n, &V);
    for (int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= n; i++){
        scanf("%d", &c[i]);
    }
    //边界
    for (int v = 0; v <= V; v++){
        dp[v] = 0;
    }
    for (int i = 1; i <= n; i++){
        for (int v = V; v >= w[i]; v--){
            //状态转移方程
            dp[v] = max(dp[v], dp[v - w[i]] + c[i]);
        }
    }
    //寻找dp[0...V]中最大的即为答案
    int max = 0;
    for (int v = 0; v <= V; v++){
        if(dp[v] > max){
            max = dp[v];
        }
    }
    printf("%d\n", max);
    return 0;
}

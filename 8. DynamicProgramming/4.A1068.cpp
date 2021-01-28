#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 10010; //硬币数
const int maxv = 110;   //总价值

int w[maxn], dp[maxv] = {0};//w[i]为钱币价值，dp
bool choice[maxn][maxv],flag[maxn];//choice[i][v]记录计算dp[i][v]时选择了哪个策略，flag表示放入还是不放入
bool cmp(int a,int b){
    return a > b;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++){
        scanf("%d", &w[i]);
    }
    sort(w + 1, w + n + 1, cmp);//逆序排列
    for (int i = 1; i <= n; i++){
        for (int v = m; v >= w[i]; v--){
            if(dp[v] <= dp[v - w[i]] + w[i]){
                dp[v] = dp[v - w[i]] + w[i];
                choice[i][v] = 1;//放入第i件物品
            }else{
                choice[i][v] = 0;
            }
        }
    }
    if (dp[m] != m){
        printf("No Solution");
    }else{
        //记录最优路径
        int k = n, num = 0, v = m;
        while(k >= 0){
            if(choice[k][v] == 1){
                flag[k] = true;
                v -= w[k];
                num++;
            }else{
                flag[k] = false;                
            }
            k--;
        }
        //输出方案
        for (int i = n; i > 0; i--){
            if(flag[i] == true){
                printf("%d", w[i]);
                num--;
                if(num > 0){
                    printf(" ");
                }
            }
        }
        
    }
    return 0;
}
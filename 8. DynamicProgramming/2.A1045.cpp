#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

//通过一个hashtable[]的映射，将寻找给定顺序的颜色的问题转化为一个求解最长不下降子序列的问题

const int maxc = 210;   //最大颜色数
const int maxn = 10010; //最大L
int HashTable[maxc];    //将喜欢色的颜序列映射为递增序列，不喜欢的颜色映射为-1
int A[maxn], dp[maxn];  //原数组A和DP数组

int main(){
    int n, m, x;
    scanf("%d%d", &n, &m);
    memset(HashTable, -1, sizeof(HashTable));
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &x);
        HashTable[x] = i;
    }
    int L, num = 0;
    scanf("%d", &L);
    for (int i = 0; i < L; i++)
    {
        scanf("%d", &x);
        if(HashTable[x] >= 0){
            A[num++] = HashTable[x];
        }
    }
    //LIS问题模板
    int ans = -1;
    for (int i = 0; i < num; i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++){
            if(A[j] <= A[i] && dp[i] < dp[j] + 1){
                dp[i] = dp[j] + 1;
            }
        }
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}
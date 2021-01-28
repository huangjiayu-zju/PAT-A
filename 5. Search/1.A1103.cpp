#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 410;

int n, k, p, maxFacSum = -1;//maxFacSum记录最大底数之和
vector<int> fac, temp, ans;//fac为预处理n^p,temp为临时序列,ans为最优序列

int power(int x){//求n^q
    int ans = 1;
    for (int i = 0; i < p; i++)
    {
        ans *= x;
    }
    return ans;
}

void init(){//预处理所有不超过n的i^p
    int i = 0, temp = 0;
    while(temp <= n){
        fac.push_back(temp);
        temp = power(++i);
    }    
}

void DFS(int index, int nowK, int sum, int facSum){
    if(nowK == k && sum == n){
        if(facSum > maxFacSum){
            maxFacSum = facSum;
            ans = temp;
        }
        return;
    }

    if(index < 1 || nowK > k || sum > n){//fac[0]不需要选择
        return;
    }
    
    //选择当前fac[index]
    temp.push_back(index);
    DFS(index, nowK + 1, sum + fac[index], facSum + index);
    temp.pop_back();
    //不选择当前fac[index]
    DFS(index - 1, nowK, sum, facSum);
    
}

int main(){
    scanf("%d%d%d", &n, &k, &p);
    init();
    DFS(fac.size() - 1, 0, 0, 0);//从fac的最后一位开始往前搜索
    if(maxFacSum == -1){
        printf("Impossible\n");
    }else{
        printf("%d = %d^%d", n, ans[0], p);
        for (int i = 1; i < ans.size(); i++)//从1开始
        {
            printf(" + %d^%d", ans[i], p);
        }
        
    }
    return 0;
}



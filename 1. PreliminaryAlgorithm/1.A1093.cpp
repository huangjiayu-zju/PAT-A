#include<cstdio>
#include<cstring>
const int maxn = 100010;
const int MOD = 1000000007;

//对一个确定位置的Alai说，以它形成的PAT的个数等于它左边P的个数乘以它右边T的个数

char str[maxn];
int leftNumP[maxn] = {0};//每一位左边（含）P的个数

int main(){
    scanf("%s", str);
    int len = strlen(str);
    for (int i = 0; i < len; i++)//从左往右遍历并得到leftNumP[]数组
    {
        if(i > 0){
            leftNumP[i] = leftNumP[i - 1];
        }
        if(str[i] == 'P'){
            leftNumP[i]++;
        }
    }
    //ans为答案，rightNumT记录右边T的个数，从右往左遍历，当前位为'A'时更新ans
    int ans = 0, rightNumT = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if(str[i] == 'T'){
            rightNumT++;
        }else if(str[i] == 'A'){
            ans = (ans + leftNumP[i] * rightNumT) % MOD;
        }
    }
    printf("%d\n", ans);
    return 0;
}


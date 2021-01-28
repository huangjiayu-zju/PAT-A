#include<cstdio>

const int maxn = 1010;
double p[maxn] = {};//p[n]表示幂次为n的项的系数，初值为0

int main(){
    int k, n, count = 0; //count表示非零项的系数
    double a;
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d %lf", &n, &a);
        p[n] += a;
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d %lf", &n, &a);
        p[n] += a;
    }
    for (int i = 0; i < maxn; i++){
        if(p[i] != 0){
            count++;
        }
    }
    printf("%d", count);
    for (int i = maxn - 1; i >= 0; i--){//按幂次从大到小的顺序输出
        if(p[i] != 0){
            printf(" %d %.1f", i, p[i]);//末尾不能有空格输出
        }
    }
    return 0;
}
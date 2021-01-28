#include<cstdio>

int main(){
    int n;
    scanf("%d", &n);
    double v;
    long long ans=0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &v);
        ans += (long long)(v *1000)* i * (n + 1 - i);
    }
    printf("%.2f\n", ans / 1000.0);
    return 0;
}
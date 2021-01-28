#include<cstdio>
int main(){
    int ans = 0, a = 1, n;
    int left, right, now;
    scanf("%d", &n);
    while(n/a != 0){
        right = n % a;
        now = n / a % 10;
        left = n / (a * 10);
        if(now ==0){
            ans += left * a;
        }
        else if(now ==1){
            ans += left * a + right + 1;
        }else{
            ans += (left + 1) * a;
        }
        a = a * 10;
    }
    printf("%d\n", ans);
    return 0;
}
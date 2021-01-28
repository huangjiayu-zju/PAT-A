#include<cstdio>

int main(){
    int n, total = 0,now=0,to;//now为当前所在层号，to表示要去的下一层
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &to);
        if(now<to){
            total += (to - now) * 6 + 5;
        }else if(now > to){
            total += (now - to) * 4 + 5;
        }else{
            total += 5;
        }
        now = to;
    }
    printf("%d\n", total);
    return 0;
}
#include<cstdio>
typedef long long LL;

int main()
{
    int T, tcase = 1;
    scanf("%d", &T);
    while(T--){
        LL a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        LL res = a + b;
        bool flag;
        if(a > 0 && b > 0 && res < 0){//正溢出为true
            flag = true;
        }else if(a < 0 && b < 0 && res >= 0){//负溢出为false
            flag = false;
        }else if(res > c){//无溢出时，大于c为true
            flag = true;
        }else{//无溢出时，小于c为false
            flag = false;
        }
        if(flag == true){
            printf("Case #%d: true\n", tcase++);
        }else{
            printf("Case #%d: false\n", tcase++);
        }
    }
    return 0;
}
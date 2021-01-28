#include<cstdio>
#include<cmath>
const int maxn = 100010;

int p[maxn] = {0}, pNum = 0;//p[]存放素数
bool prime[maxn] = {0};//false表示是素数

void Find_Prime(){//素数表
    for(int i = 2; i < maxn; i++){
        if(prime[i] == false){
            p[pNum++] = i;
            for (int j = i + i; j < maxn; j += i){
                prime[j] = true;
            }
        }
    }
}

struct factor{
    int cnt;
    int x;
} fac[10];

int main(){
    Find_Prime();
    int n,num=0;
    scanf("%d", &n);
    if(n==1){//特殊情况
        printf("1=1\n");
    }else{
        printf("%d=", n);
        int sqr = (int)sqrt(1.0 * n);
        for(int i = 0; i < pNum && p[i] <= sqr; i++){//p[i] <= sqr因为这部分处理小于sqr的质因子
            if(n%p[i]==0){
                fac[num].cnt = 0;
                fac[num].x = p[i];
                while(n%p[i]==0){
                    fac[num].cnt++;
                    n /= p[i];
                }
                num++;
            }
            if(n==1){
                break;//及时退出循环，节省时间
            }
        }
        if(n!=1){
            fac[num].cnt = 1;
            fac[num].x = n;
            num++;
        }
        //按格式输出结果
        for (int i = 0; i < num; i++)
        {
            if(i!=0){
                printf("*");
            }
            printf("%d", fac[i].x);
            if(fac[i].cnt>1){
                printf("^%d", fac[i].cnt);
            }
        }
    }
    return 0;
}
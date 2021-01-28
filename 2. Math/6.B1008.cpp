//让移动的次数最少
#include<cstdio>
int gcd(int a,int b){
    if(b==0)
        return a;
    else
        return gcd(b, a % b);
}

int main(){
    int a[110];
    int n, m, temp, pos, next;//temp临时变量，pos存放当前处理位置，next为下一个处理的位置
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    m = m % n; //修正m
    if(m!=0){
        int d = gcd(m, n);//d为最大公约数
        for (int i = n - m; i < n - m + d; i++)//枚举最大公约数范围
        {
            temp = a[i];
            pos = i;
            do{
                next = (pos - m + n) % n;
                if(next != i){//下一个位置不是初始点
                    a[pos] = a[next];
                }
                else{
                    a[pos] = temp;
                }
                pos = next;
            } while (pos != i);//循环知道当前处理位置回到初始点时结束
        }        
    }
    for (int i = 0; i < n; i++){
        printf("%d", a[i]);
        if(i < n - 1){
            printf(" ");
        }
    }
    return 0;
}
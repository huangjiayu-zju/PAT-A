#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
typedef long long LL;

//N不会被除自己以外的大于sqrt(N)的连续整数整除，所以只要遍历[2,sqrt(N)]

int main(){
    LL n;
    scanf("%lld", &n);
    LL sqr = (LL)sqrt(1.0 * n), ansI = 0, ansLen = 0;//ansLen为最长连续整数，ansI为对应的第一个整数
    for (LL i = 2; i <= sqr; i++){
        LL temp = 1, j = i;//temp为当前连续整数乘积
        while(1){//让j从i开始不断加1，看最长能到多少
            temp *= j;
            if(n % temp != 0){//不能整除n则结束运算
                break;
            }
            if(j - i + 1 > ansLen){//发现更长的长度
                ansLen = j - i + 1;
                ansI = i;
            }
            j++;
        }
    }
    if(ansLen == 0){//遍历结束ansLen为0说明不存在能整除的连续整数，输出N本身
        printf("1\n%lld\n", n);
    }else{
        printf("%lld\n", ansLen);
        for (LL i = 0; i < ansLen; i++){
            printf("%lld", ansI + i);
            if(i < ansLen - 1){
                printf("*");
            }
        }
    }
    return 0;
}

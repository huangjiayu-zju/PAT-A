#include<cstdio>
#include<cmath>
using namespace std;

bool isPrime(int n){
    if(n<=1){
        return false;
    }
    int sqr = (int)sqrt(n * 1.0);
    for (int i = 2; i <= sqr; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}
int d[101];
int main(){
    int n, radix;
    while(scanf("%d", &n)!=EOF){
        if(n < 0){
            break;
        }
        scanf("%d", &radix);
        if(isPrime(n)==0){
            printf("No\n");
        }else{
            int len = 0;
            do{//进制转换
                d[len++] = n % radix;
                n /= radix;
            } while (n != 0);
            for (int i = 0; i < len; i++){//逆序转换进制
                n = n * radix + d[i];
            }
            if(isPrime(n)){
                printf("Yes\n");
            }else{
                printf("No\n");
            }
        }
    }
    return 0;
}
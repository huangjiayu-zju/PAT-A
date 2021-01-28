#include<cstdio>
#include<cmath>
using namespace std;
const int maxn = 10001;
bool hashTable[maxn] = {0};//hashTable[x]=false表示x号未使用

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

int main(){
    int n, TSize, a;
    scanf("%d%d", &TSize, &n);
    while(isPrime(TSize)==0){
        TSize++;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        int M = a % TSize;
        if(hashTable[M]==false){//如果M号位未被使用，则已经找到
            hashTable[M] = true;
            if(i==0){
                printf("%d", M);
            }else{
                printf(" %d", M);
            }
        }else{//二次方探查法
            int step;
            for (step = 1; step < TSize; step++)
            {
                M = (a + step * step) % TSize;
                if(hashTable[M]==false){
                    hashTable[M] = true;
                    if(i==0){
                        printf("%d", M);
                    }else{
                        printf(" %d", M);
                    }
                    break;
                }
            }
            if(step >= TSize){
                if(i > 0){
                    printf(" ");
                }
                printf("-");
            }            
        }
    }
    return 0;
}


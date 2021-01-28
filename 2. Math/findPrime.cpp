#include <cmath>
#include <cstdio>
const int maxn = 101;//素数表表长

int prime[maxn], pNum = 0;//prime数组存放所有素数，pNum为素数个数
bool p[maxn] = {0};//p[i]==false表示i是素数

bool isPrime(int n){
    if (n <= 1){
        return false;
    }
    int sqr = (int)sqrt(n * 1.0);
    for (int i = 2; i <= sqr; i++){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

void Find_Prime(){
    for (int i = 0; i < maxn; i++){
        if(isPrime(i) == true){
            prime[pNum++] = i;
        }
    }
}

//素数筛法
void Find_Prime(){
    for (int i = 2; i < maxn; i++){
        if(p[i] == false){
            prime[pNum++] = i;
            for (int j = i + i; j < maxn; j += i){
                p[j] = true;
            }
        }
    }
}

int main(){
    Find_Prime();
    for (int i = 0; i < pNum; i++)
    {
        printf("%d ", prime[i]);
    }
    return 0;
}









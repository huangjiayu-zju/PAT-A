#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100010;
int n, a[maxn];//数组a存放所有正整数，n为其个数

int main(){
    int sum = 0, sum1 = 0;//sum和sum1记录所有整数之和与切分后前n/2个元素之和
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        sum += a[i];
    }
    nth_element(a, a + n / 2, a + n);
    for (int i = 0; i < n / 2; i++){
        sum1 += a[i];
    }
    printf("%d %d\n", n % 2, (sum - sum1) - sum1);
    return 0;
}
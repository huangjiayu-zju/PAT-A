#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100010;

int main(){
    int n, p, a[maxn];
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    int i = 0, j = 0, count = 1;
    while(i < n && j < n){
        while (j < n && a[j] <= (long long)a[i] * p){//因为a[i]*p可能达到10^18，必须用long long来存储
            count = max(count, j - i + 1);
            j++;
        }
        i++;
    }
    printf("%d\n", count);
    return 0;
}
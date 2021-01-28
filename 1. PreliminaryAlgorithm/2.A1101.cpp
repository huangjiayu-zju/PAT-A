#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100010;
const int INF = 0x7fffffff;

int a[maxn], leftMax[maxn], rightMin[maxn];//a为序列，leftMax和rightMin分别为每一位左边最大的数和右边最小的数
int ans[maxn], num = 0; //ans记录所有主元，num为主元个数

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    leftMax[0] = 0;
    for (int i = 1; i < n; i++)
    {
        leftMax[i] = max(leftMax[i - 1], a[i - 1]);
    }
    rightMin[n - 1] = INF;
    for (int i = n - 2; i >= 0; i--)
    {
        rightMin[i] = min(rightMin[i + 1], a[i + 1]);
    }
    for (int i = 0; i < n; i++)
    {
        if(leftMax[i] < a[i] && rightMin[i] > a[i]){
            ans[num++] = a[i];
        }
    }
    printf("%d\n", num);
    for (int i = 0; i < num; i++)
    {
        printf("%d", ans[i]);
        if(i < num - 1){
            printf(" ");
        }
    }
    printf("\n");//当主元个数为0时，第二行虽然没有输出主元，但必须输出一个换行
    return 0;
}
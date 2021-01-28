#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;

//至少有E天骑车超过E英里
int miles[maxn];
bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)//输入英里数，下标从1开始
    {
        scanf("%d", &miles[i]);
    }
    sort(miles + 1, miles + n + 1, cmp);//将英里数从大到小排序
    int E = 1;//让E从小到大遍历数组
    while (E <= n && E < miles[E])//找到第一个E>=miles[E]的E
    {
        E++;
    }
    printf("%d\n", E - 1);//E-1即为结果
    return 0;
}
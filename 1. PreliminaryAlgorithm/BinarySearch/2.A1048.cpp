#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int a[maxn];

int Bin(int l, int r, int key)
{ //在[l,right]查找值为key的数的下标，初始为[0,n-1]
    int mid;
    while (l <= r)
    {//查找确定的数要用<=而查找大于某个数用<
        mid = (l + r) / 2;
        if (a[mid] == key)
        {
            return mid;
        }
        if (a[mid] > key)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int i, n, m; //这里定义i因为输出时要用到
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    for (i = 0; i < n; i++)
    { //对每个a[i]，用二分法查找数字内是否存在m-a[i],如果存在且下标不是i，则输出
        int pos = Bin(0, n - 1, m - a[i]);
        if (pos != -1 && i != pos)//排除下标相同的情况，是同一位置的数字
        {
            printf("%d %d\n", a[i], a[pos]);
            break;
        }
    }
    if (i == n)
    {
        printf("No Solution\n");
    }
    return 0;
}
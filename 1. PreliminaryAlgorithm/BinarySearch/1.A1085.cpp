#include<cstdio>
#include<algorithm>
using namespace std;

//从左至右扫描序列，对其中的每个数a[i]，在a[i+1]~a[n-1]内二分查找第一个超过a[i]*p的数的位置j
//这样j-i就是对位置i来说满足条件的最远长度，取所有j-i的最大值即可

const int maxn = 100010;
int n, p, seq[maxn];

int binarySearch(int i, long long x)
{ //在[i+1,n-1]范围内查找第一个大于x的数的位置
    if (seq[n - 1] <= x)
    {
        return n;
    }
    int l = i + 1, r = n - 1, mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (seq[mid] > x)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return l;
}

int main()
{
    scanf("%d%d", &n, &p);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &seq[i]);
    }
    sort(seq, seq + n); //递增排序
    int ans = 1;        //最大长度，初值为1，表示至少有一个数
    for (int i = 0; i < n; i++)
    { //在seq[i+1,n-1]中查找第一个超过seq[i]*q的数，返回其位置给j
        int j = binarySearch(i, (long long)seq[i] * p);//注意必须强制类型转换
        //int j = upper_bound(seq + i + 1, seq + n, (long long)seq[i] * p) - a;//无需自定义二分查找
        ans = max(ans, j - i);
    }
    printf("%d\n", ans);
    return 0;
}
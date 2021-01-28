#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int coupons[maxn], product[maxn];

int main()
{
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &coupons[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &product[i]);
    }
    sort(coupons, coupons + n);
    sort(product, product + m);
    int i = 0, j, ans = 0;
    while (i < n && i < m && coupons[i] < 0 && product[i] < 0)
    {
        ans += coupons[i] * product[i];
        i++;
    }
    i = n - 1;
    j = m - 1;
    while (i >= 0 && j >= 0 && coupons[i] > 0 && product[j] > 0)
    {
        ans += coupons[i] * product[j];
        i--, j--;
    }
    printf("%d\n", ans);
    return 0;
}

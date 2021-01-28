#include <cstdio>
#include <algorithm>
using namespace std;
//假设当前加油站编号为now，接下来从满油状态下能到达的所有加油站中选出下一个前往的加油站，策略如下
//1. 优先前往比now更低油价的加油站，并只加够到此加油站的油
//2. 如果没有加油站的油价比now低，那么在now加油站加满油，然后前往油价尽可能低的加油站。
//如果在满油状态下都找不到能到达的加油站，返回当前加油站距离+满油状态前进距离

const int maxn = 510; //加油站最大数目
const int INF = 1000000000;
struct station
{
    double dis, price; //价格，与起点距离
} st[maxn];
bool cmp(station a, station b)
{ //按距离从大到小排序
    return a.dis < b.dis;
}

int main()
{
    int n;
    double cmax, D, Davg;
    scanf("%lf%lf%lf%d", &cmax, &D, &Davg, &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%lf", &st[i].price, &st[i].dis);
    }
    st[n].price = 0;       //数组后面放置终点，价格为0
    st[n].dis = D;         //终点距离为D
    sort(st, st + n, cmp); //将所有加油站按距离从小到大排序
    if (st[0].dis != 0)
    { //起点没有加油站
        printf("The maximum travel distance = 0.00\n");
    }
    else
    {
        int now = 0;                                    //当前所处的加油站编号
        double ans = 0, nowTank = 0, MAX = cmax * Davg; //总花费、当前油量，满油行驶距离
        while (now < n)                                 //每次循环选出下一个需要到达的加油站
        {                                               //当前油价st[now].price，找出第一个低于当前油价的加油站，如果没有则选择距离MAX内价格最低的那个
            int k = -1;                                 //最低油价的加油站的编号
            double priceMin = INF;                      //选出这趟循环的最低油价，不包括出发点的油价
            for (int i = now + 1; i <= n && st[i].dis - st[now].dis <= MAX; i++)
            { //从当前加油站now的下一个开始遍历i，两者距离不能超过MAX
                if (st[i].price < priceMin)
                {                           //如果油价比当前最低油价低
                    priceMin = st[i].price; //更新区间内的最低油价
                    k = i;
                    if (priceMin < st[now].price)
                    { //找到第一个比当前油价低的加油站即为本次循环找到的加油站
                        break;
                    }
                }
            }
            if (k == -1)
            { //找不到可以到达的加油站，直接跳出循环
                break;
            }
            //计算到达下一站k的转移花费，关键是当前油量，需要补充的油量，到站后剩余的油量。
            double need = (st[k].dis - st[now].dis) / Davg; //need从now到k，需要消耗的油量
            if (st[k].price < st[now].price)
            { //如果加油站k的油价低于当前油价，只买足够到达加油站的油
                if (nowTank < need)
                {
                    ans += (need - nowTank) * st[now].price;
                    nowTank = 0;
                }
                else
                {
                    nowTank -= need;
                }
            }
            else
            { //如果加油站k的油价高于当前油价，将邮箱加满，到达下一站后还剩cmax-need的油量
                ans += (cmax - nowTank) * st[now].price;
                nowTank = cmax - need;
            }
            now = k;
        }
        if (now == n)
        {
            printf("%.2f\n", ans);
        }
        else
        {
            printf("The maximum travel distance = %.2f\n", st[now].dis + MAX);
        }
    }
    return 0;
}

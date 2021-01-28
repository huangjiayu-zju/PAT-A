//合并果子问题
#include<cstdio>
#include<queue>
using namespace std;
typedef long long ll;

//代表小顶堆的优先队列
priority_queue<ll, vector<ll>, greater<ll>> q;

int main(){
    int n;  //果子个数
    ll temp, x, y, ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("lld", &temp);
        q.push(temp);   //将初始重量压入优先队列
    }
    while(q.size() > 1){    //只要优先队列中至少有两个元素
        x = q.top();
        q.pop();
        y = q.top();
        q.pop();
        q.push(x + y);
        ans += x + y;
    }
    printf("%lld\n", ans);  //ans即为最小带权路径长度
    return 0;
}

#include<cstdio>
#include<set>
using namespace std;
const int N = 51;
set<int> st[N]; //N个集合

void compare(int x, int y){ //比较集合st[x]与st[y]
    int totalNum = st[y].size(), sameNum = 0;
    for (set<int>::iterator it = st[x].begin(); it != st[x].end(); it++){//遍历集合st[x]
        if(st[y].find(*it) != st[y].end()){//在st[y]中能找到该元素
            sameNum++;
        }
        else{
            totalNum++;
        }
    }
    printf("%.1f%%\n", sameNum * 100.0 / totalNum);
}

int main(){
    int n, m, v, k, st1, st2;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)//从1开始，因为查询的编号从1开始
    {
        scanf("%d", &m);
        for (int j = 0; j < m; j++){
            scanf("%d", &v);
            st[i].insert(v);
        }
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        scanf("%d%d", &st1, &st2);
        compare(st1, st2);
    }
    return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1010;

int father[maxn];       //存放父亲结点
int isRoot[maxn] = {0}; //记录每个结点是否作为某个集合的根结点
int course[maxn] = {0}; //记录任意一个喜欢活动h的人的编号i(course[h]=i)，这样只要合并findFather(course[i])与i即可

int findFather(int x){
    int a = x;
    while(x != father[x]){
        x = father[x];
    }
    while (a != father[a]){
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void Union(int a, int b){
    int faA = findFather(a);
    int faB = findFather(b);
    if(faA != faB){
        father[faA] = faB;
    }
}

void init(int n){   //初始化father[i]=i，且flag[i]=false
    for (int i = 1; i <= n; i++){
        father[i] = i;
        isRoot[i] = false;
    }
}

bool cmp(int a, int b){
    return a > b;
}

int main(){
    int n, k, h;
    scanf("%d", &n); //人数
    init(n); //初始化
    for (int i = 1; i <= n; i++) //对每个人
    {
        scanf("%d:", &k); //活动个数
        for (int j = 0; j < k; j++){ //对每个活动
            scanf("%d", &h); //输入i号人喜欢的活动h
            if(course[h] == 0){//如果活动h第一次有人喜欢
                course[h] = i;
            }
            Union(findFather(course[h]), i);//合并
        }
    }
    for (int i = 1; i <= n; i++)
    {
        isRoot[findFather(i)]++; //i的根结点是findFathar(i)，人数加1
    }
    int ans = 0;//记录集合数目
    for (int i = 1; i <= n; i++)
    {
        if(isRoot[i] != 0){
            ans++;
        }
    }
    printf("%d\n", ans);
    sort(isRoot + 1, isRoot + n + 1, cmp); //从大到小排序
    for (int i = 1; i <= ans ; i++)
    {
        printf("%d", isRoot[i]);
        if(i < ans){
            printf(" ");
        }
    }
    return 0;
}
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxv = 110; //最大顶点数
const int maxe = 110;//最大边数

//边集定义部分
struct edge{
    int u, v;//边的两个端点编号
    int cost;//边权
}E[maxe];//最多有maxe条边

bool cmp(edge a, edge b){//让数组E按边权从大到小排序
    return a.cost < b.cost;
}

//并查集部分
int father[maxv];//并查集数组
int findFather(int x){//并查集查询函数
    int a = x;
    while(father[x] != x){ 
        x = father[x];
    }
    while(a != father[a]){
        int z = a; 
        a = father[a];
        father[z] = x; 
    }
    return x;
}

//kruskal部分，返回最小生成树的边权之和，参数n为顶点个数，m为图的边数
int kruskal(int n, int m){
    int ans = 0, Num_Edge = 0;  //ans为所求边权之和，Num_Edge为当前生成树的边数
    for (int i = 1; i <= n; i++){//假设题目中顶点范围为[1,n]
        father[i] = i;          //并查集初始化
    }   
    sort(E, E + m, cmp);        //所有边按边权从小到大排序
    for (int i = 0; i < m; i++){//枚举所有边
        int faU = findFather(E[i].u);//查询测试边两个端点所在集合的根结点
        int faV = findFather(E[i].v);
        if(faU != faV){         //如果不在一个集合中
            father[faU] = faV;  //合并集合(即把测试边加入最小生成树中)
            ans += E[i].cost;   //更新边权之和
            Num_Edge++;         //更新生成树的边数
            if(Num_Edge == n-1){//边数等于顶点数减1时结束算法
                break;
            }
        }
    }
    if(Num_Edge != n - 1){      //无法连通时返回-1
        return -1;
    }else{
        return ans;             //返回最小生成树的边权之和
    }
}
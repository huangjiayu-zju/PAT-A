#include<cstdio>
using namespace std;
const int maxn = 110;

bool isRoot[maxn] = {false}; //记录每个结点是否作为某个集合的根结点，通常会遍历一遍结点，isRoot[findFather[i]] = true
int father[maxn];//father[i]表示元素i的父亲结点，father[i] = i说明元素i是该集合的根结点

//初始化并查集，一开始，每个元素都是独立的集合
void init(int n){
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;//令father[i] = -1也可
    }
    
}

//查找：返回元素x所在集合的根结点，路径压缩后的并查集查找函数均摊效率认为是O(1)的操作
int findFather(int x){
    //由于x在下面的while中会变成根结点，因此先保存原来的x
    int a = x;
    while(father[x] != x){ // 如果不是根结点，继续循环
        x = father[x]; //获得自己的父亲结点
    }
    //到这里，x存放的是根结点，下面把路径上的所有结点的father都改成根结点
    while(a != father[a]){
        int z = a; //因为a要被father[a]覆盖，所以先保存a的值，以修改father[a]
        a = father[a]; //a回溯父亲结点
        father[z] = x; //将原来的结点a的父亲改为根结点x
    }
    return x;
}

//递归写法
int findFather(int v){
    if(v == father[v]){//找到根结点
        return v;
    }
    else{
        int F = findFather(father[v]); //递归寻找father[v]的根结点F
        father[v] = F; //将根结点F赋值给father[v]
        return F; //返回根结点F
    }
}

//合并：将两个集合合并成一个集合
void Union(int a, int b){
    int faA = findFather(a); //查找a的根结点
    int faB = findFather(b); //查找b的根结点
    if(faA != faB){ //如果不属于同一个集合
        father[faA] = faB; //合并它们
    }
}
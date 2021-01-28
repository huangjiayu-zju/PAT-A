#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxn = 210;//结点个数上限

// 一条路径是哈密顿回路需要满足三个条件
// 1.首尾结点相同
// 2.路径的每条边必须存在
// 3.不考虑首结点，路径的剩余结点包含且只包含图中所有结点各一次
//     3.1 路径结点个数num等于图的结点个数加1
//     3.2 不考虑首结点，路径的剩余结点互不相同

int n, m, k;//结点个数n，边数m，路径条数k
bool G[maxn][maxn] = {false};//无向图G
bool isInPath[maxn];//记录结点是都已在路径上出现过
bool judgeHamiltonianCycle(vector<int> &path){//判断路径path是否是哈密顿回路，注意加引用
    if(path.size() != n + 1 || path.front() != path.back()){
        return false;
    }else{
        memset(isInPath, false, sizeof(isInPath));//初始化所有结点都不在路径上
        for (int j = 1; j < path.size(); j++){//遍历除首结点外的结点
            if(isInPath[path[j]] || !G[path[j-1]][path[j]]){
                return false;
            }
            isInPath[path[j]] = true;
        }
    }
    return true;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        G[u][v] = G[v][u] = true;
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++)
    {
        int num, tempNode;
        scanf("%d", &num);
        vector<int> path;
        for (int j = 0; j < num; j++){
            scanf("%d", &tempNode);
            path.push_back(tempNode);
        }
        printf(judgeHamiltonianCycle(path) ? "YES\n" : "NO\n");
    }
    return 0;
}
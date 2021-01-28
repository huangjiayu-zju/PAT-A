#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
const int maxn = 100010;

vector<int> child[maxn];//存放树
double p, r;
int n, maxDepth, num;//maxDepth为最大深度，num为最大深度的叶节点个数
void DFS(int index,int depth){//当前访问结点index和当前深度depth
    if(child[index].size() == 0){//到达叶结点
        if(depth > maxDepth){//更新最大深度
            maxDepth = depth;
            num = 1;//重置最大深度叶结点数目为1
        }else if(depth == maxDepth){//深度等于最大深度
            num++;
        }
        return;
    }
    for (int i = 0; i < child[index].size(); i++)
    {
        DFS(child[index][i], depth + 1);
    }
    
}

int main(){
    int father, root;
    scanf("%d%lf%lf", &n, &p, &r);
    r = r / 100;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &father);
        if(father!=-1){
            child[father].push_back(i);
        }else{
            root = i;
        }
    }
    DFS(root, 0);
    printf("%.2f %d\n", p * pow(1 + r, maxDepth), num);
    return 0;

}
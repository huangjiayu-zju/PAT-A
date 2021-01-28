#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 110;

struct Node{
    int weight;
    vector<int> child;
} node[maxn];

bool cmp(int a, int b){//按结点数据域从大到小排序
    return node[a].weight > node[b].weight;
}

int n, m, S;//结点数、非叶结点数及给定的和
int path[maxn] = {0};//记录路径

void DFS(int index, int numNode, int sum){//当前访问结点、当前路径path上的结点个数、当前的结点点权和
    if(sum > S){//当前和超过S，直接返回
        return;
    }
    if(sum == S){
        if(node[index].child.size()!=0){//先判断是否是叶子结点
            return;
        }
        //到达叶子结点，path[]存放了完整的路径，输出path
        for (int i = 0; i < numNode; i++)
        {
            printf("%d", node[path[i]].weight);
            if(i < numNode - 1){
                printf(" ");
            }
            else{
                printf("\n");
            }
        }
        return;
    }
    for (int i = 0; i < node[index].child.size(); i++)//枚举所有子结点
    {
        int child = node[index].child[i];//结点index的第i个子结点编号
        path[numNode] = child;//将结点child加入路径中
        DFS(child, numNode + 1, sum + node[child].weight);//递归进入下一层
    }
}

int main(){
    scanf("%d%d%d", &n, &m, &S);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &node[i].weight);
    }
    int id, k, child;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &id, &k);
        for (int j = 0; j < k; j++){
            scanf("%d", &child);
            node[id].child.push_back(child);
        }
        sort(node[id].child.begin(), node[id].child.end(), cmp);//排序
    }
    path[0] = 0;//路径第一个结点设置为0号结点
    DFS(0, 1, node[0].weight);
    return 0;
}




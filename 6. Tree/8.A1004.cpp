#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 110;

vector<int> node[maxn];
int leaf[maxn] = {0};//记录每层叶结点个数
int max_h;//记录最大高度
int h[maxn] = {0};//结点i所处的层号，从1开始，DFS用的是一个变量，但BFS要用数组来记录

void BFS(){
    queue<int> q;//存放地址
    q.push(1);//根结点入队列
    while(!q.empty()){//循环遍历每层
        int now = q.front();
        q.pop();
        if(node[now].size()==0){//如果该结点是叶子结点，更新最大深度
            leaf[h[now]]++;
            max_h = max(max_h, h[now]);
        }else{//如果不是叶子结点，枚举所有子结点，并计算出子结点的层数，为下一轮循环做准备
            for (int i = 0; i < node[now].size(); i++)
            {
                h[node[now][i]] = h[now] + 1;//子结点层号为当前结点层号加1
                q.push(node[now][i]);
            }
        }        
    }
}

int main(){
    int n, m, id, k, child;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &id, &k);
        for (int j = 0; j < k; j++){
            scanf("%d", &child);
            node[id].push_back(child);
        }
    }
    h[1] = 1;
    BFS();
    for (int i = 1; i <= max_h; i++)
    {
        if(i == 1){
            printf("%d", leaf[i]);
        }
        else{
            printf(" %d", leaf[i]);
        }
    }
    return 0;

}
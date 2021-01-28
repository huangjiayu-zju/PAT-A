#include<cstdio>
#include<vector>
using namespace std;
const int maxn = 110;

vector<int> node[maxn];
int hashTable[maxn] = {0};//记录第i层的结点个数

void DFS(int index, int level){
    // if(node[index].size() == 0){//不需要递归出口，因为叶子结点没有额外信息要计算
    //     hashTable[level]++;//第level层的结点加1
    //     return;
    // }
    hashTable[level]++;
    for (int i = 0; i < node[index].size(); i++)
    {
        DFS(node[index][i], level + 1);
    }
}

int main(){
    int n, m, parent, child, k;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &parent, &k);
        for (int j = 1; j <= k; j++)
        {
            scanf("%d", &child);
            node[parent].push_back(child);
        }
    }
    DFS(1, 1);
    int maxLevel = -1, maxValue = 0;
    for (int i = 1; i < maxn; i++)//计算hashTable数组的最大值
    {
        if(hashTable[i] > maxValue){
            maxValue = hashTable[i];
            maxLevel = i;
        }
    }
    printf("%d %d\n", maxValue, maxLevel);
    return 0;
}
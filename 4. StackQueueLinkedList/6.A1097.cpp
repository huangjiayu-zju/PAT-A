#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn = 100010;
bool isExist[maxn] = {false};

struct Node{
    int address, data, next;
    int order;//令未删除的结点从0开始，被删除的结点从maxn开始编号
} node[maxn];

bool cmp(Node a, Node b){
    return a.order < b.order;
}

int main(){
    for (int i = 0; i < maxn; i++)
    {
        node[i].order = 2 * maxn;//区分无效结点
    }
    int begin, n, address;
    scanf("%d%d", &begin, &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &address);
        scanf("%d%d", &node[address].data, &node[address].next);
        node[address].address = address;
    }
    int countValid = 0, countRemoved = 0, p = begin;//未删除有效节点个数和已删除的个数
    while(p != -1){
        if(isExist[abs(node[p].data)]==false){
            node[p].order = countValid++;
            isExist[abs(node[p].data)] = true;           
        }else{
            node[p].order = maxn + countRemoved++;        
        }
        p = node[p].next;
    }
    sort(node, node + maxn, cmp);
    int count = countValid + countRemoved;
    for (int i = 0; i < count; i++)
    {
        if(i == countValid - 1 || i == count - 1){
            printf("%05d %d -1\n", node[i].address, node[i].data);
        }else{
            printf("%05d %d %05d\n", node[i].address, node[i].data,node[i+1].address);
        }
    }
    return 0;
}
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100010;

struct Node{
    int address, data, next;
    bool flag;  //结点是否在链表上
} node[maxn];

bool cmp(Node a, Node b){
    if(a.flag == false || b.flag == false){
        return a.flag > b.flag;//只要a和b中有一个无效结点，就把它放到后面
    }else{
        return a.data < b.data;
    }
}

int main(){
    for (int i = 0; i < maxn; i++)
    {
        node[i].flag = false;
    }
    int n, s;//s为首结点地址
    scanf("%d%d", &n, &s);
    int address;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &address);
        scanf("%d%d", &node[address].data, &node[address].next);
        node[address].address = address;
    }
    int p = s, count = 0;
    while(p != -1){
        node[p].flag = true;
        count++;
        p = node[p].next;
    }
    if(count == 0){//特例，新链表中没有结点
        printf("0 -1");
    }else{
        sort(node, node + maxn, cmp);
        printf("%d %05d\n", count, node[0].address);
        for (int i = 0; i < count; i++)
        {
            if(i < count - 1){
                printf("%05d %d %05d\n", node[i].address, node[i].data, node[i+1].address);
            }else{
                printf("%05d %d -1\n", node[i].address, node[i].data);
            }
        }
    }
    return 0;

}
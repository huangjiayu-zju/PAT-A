#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 100010;

//定义静态链表(步骤1)
struct Node{
    int address, data, next;
    int order;//结点在链表上的序号，无效结点记为maxn
} node[maxn];

bool cmp(Node n1, Node n2){
    return n1.order < n2.order;
}

int main(){
    //初始化(步骤2)
    for (int i = 0; i < maxn; i++)
    {
        node[i].order = maxn;
    }
    int begin, n, k, address;//起始地址，结点个数，步长
    scanf("%d%d%d", &begin, &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &address);
        scanf("%d%d", &node[address].data, &node[address].next);
        node[address].address = address;
    }
    int p = begin, count = 0;//count计数有效结点的个数
    //遍历链表找出单链表的所有有效结点(步骤3)
    while(p != -1){//-1表示链表结束
        node[p].order = count++;//order从0开始
        p = node[p].next;//下一个结点
    }
    //按单链表从头到尾顺序排列(步骤4)
    sort(node, node + maxn, cmp);    
    n = count;//有效结点为前count个结点，把count赋给n
    //形成单链表后按照题目要求输出(步骤5)
    for (int i = 0; i < n / k; i++)
    {
        for (int j = (i+1)*k-1; j > i*k ; j--)
        {
            printf("%05d %d %05d\n", node[j].address, node[j].data, node[j - 1].address);
        }
        //处理每块最后一个结点的next地址
        printf("%05d %d ", node[i*k].address, node[i*k].data);
        if(i < n / k - 1){//如果i号块不是最后一个完整块
            printf("%05d\n", node[(i + 2) * k - 1].address);
        }else{//如果是最后一个完整块
            if(n % k == 0){//恰好是最后一个结点
                printf("-1\n");
            }else{//剩下不完整的块按原来的顺序输出
                printf("%05d\n", node[(i + 1) * k].address);
                for (int m = n / k * k; m < n; m++){
                    printf("%05d %d ", node[m].address, node[m].data);
                    if(m < n - 1){
                        printf("%05d\n", node[m + 1].address);
                    }else{
                        printf("-1\n");
                    }
                }
            }
        }
        
    }
    return 0;

}
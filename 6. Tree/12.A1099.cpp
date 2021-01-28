#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 110;

struct Node{
    int lchild, rchild;
    int data;
} node[maxn];
int number[maxn],n,num = 0;//num是当前已经处理的结点数目

void inOrder(int root){//中序遍历，将排序号的序列依次填入二叉树
    if(root == -1){//知道到达叶子结点
        return;
    }
    inOrder(node[root].lchild);
    node[root].data = number[num++];  //填入序列中的整数
    inOrder(node[root].rchild);
}

void BFS(int root){
    queue<int> q;
    q.push(root);
    num = 0;
    while(!q.empty()){
        int now = q.front();
        q.pop();
        num++;
        printf("%d", node[now].data);
        if(num < n){
            printf(" ");
        }else{
            printf("\n");
        }
        if(node[now].lchild != -1){
            q.push(node[now].lchild);
        }
        if(node[now].rchild != -1){
            q.push(node[now].rchild);
        }
    }
}

int main(){
    int lchild,rchild;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &lchild, &rchild);
        node[i].lchild = lchild;
        node[i].rchild = rchild;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &number[i]);
    }
    sort(number, number + n);
    inOrder(0);
    BFS(0);
    return 0;
}
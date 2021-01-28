#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 20;
struct Node{ //二叉树的静态写法
    int lchild, rchild;
} node[maxn];
bool notRoot[maxn] = {false}; //记录是否不是根结点，初始均是根结点
int n, num = 0;//n为结点个数，num为当前已经输出的结点个数

//将输入的字符转换为-1或者结点编号
int strToNum(char c){
    if(c == '-'){
        return -1;
    }
    else{
        notRoot[c - '0'] = true;//标记编号c不是根结点，因为根结点不是任何结点的孩子结点
        return c - '0';
    }
}

int findRoot(){
    for (int i = 0; i < n; i++)
    {
        if(notRoot[i] == false){
            return i;
        }
    }    
}

//后序遍历，用以反转二叉树
void postOrder(int root){
    if(root == -1){
        return;
    }
    postOrder(node[root].lchild);
    postOrder(node[root].rchild);
    swap(node[root].lchild, node[root].rchild);//交换左右孩子结点
}

void print(int id){
    printf("%d", id);
    num++;
    if(num < n){
        printf(" ");
    }else{
        printf("\n");
    }
}

void BFS(int root){
    queue<int> q;//注意队列里存的是地址
    q.push(root);//将根结点地址入队
    while(!q.empty()){
        int now = q.front();
        q.pop();
        print(now);
        if(node[now].lchild != -1){
            q.push(node[now].lchild);
        }
        if(node[now].rchild != -1){
            q.push(node[now].rchild);
        }
    }

}

void inOrder(int root){
    if(root == -1){
        return;
    }
    inOrder(node[root].lchild);
    print(root);
    inOrder(node[root].rchild);
}


int main(){
    char lchild, rchild;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%*c%c %c", &lchild, &rchild);
        node[i].lchild = strToNum(lchild);
        node[i].rchild = strToNum(rchild);
    }
    int root = findRoot();//获得根结点编号
    postOrder(root);
    BFS(root);
    num = 0;
    inOrder(root);
    return 0;
}

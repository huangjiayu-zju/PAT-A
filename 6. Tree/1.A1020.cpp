#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 40;

struct Node{
    int data;
    Node *lchild;
    Node *rchild;
};

int in[maxn], post[maxn];
int n;//结点个数

//create函数返回构建出的二叉树的根节点地址
Node* create(int inL, int inR, int postL, int postR){
    if(postL > postR){
        return NULL;
    }
    Node *root = new Node;
    root->data = post[postR];
    int k;
    for (k = inL; k <= inR; k++){
        if(in[k] == post[postR]){
            break;
        }
    }
    int numLeft = k - inL;
    root->lchild = create(inL, k - 1, postL, postL + numLeft - 1);
    root->rchild = create(k + 1, inR, postL + numLeft, postR - 1);
    return root;
}

int num = 0;//记录已输出结点个数，因为题目要求最后一个数后面的空格不被输出
void BFS(Node* root){
    queue<Node *> q;
    q.push(root);
    while(!q.empty()){
        Node *now = q.front();
        q.pop();
        printf("%d", now->data);
        num++;
        if(num < n){
            printf(" ");
        }
        if(now->lchild!=NULL){
            q.push(now->lchild);
        }
        if(now->rchild!=NULL){
            q.push(now->rchild);
        }
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &post[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &in[i]);
    }
    Node *root = create(0, n - 1, 0, n - 1);
    BFS(root);
    return 0;
}
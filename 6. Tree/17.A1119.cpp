#include<cstdio>
#include<vector>
using namespace std;
const int maxn = 50;

struct Node{
    int data;
    Node *lchild;
    Node *rchild;
};
int pre[maxn], post[maxn];//先序，后序序列
int n;//结点个数
bool isUnique = true;//二叉树是否唯一

//当前二叉树的先序序列区间是[preL,preR],后序序列区间为[postL,postR]
//create函数返回构建出的二叉树的根结点地址
Node* create(int preL, int preR, int postL, int postR){
    if(preL > preR){
        return NULL;//空树
    }
    Node *root = new Node;
    root->data = pre[preL];//根结点
    //在后序序列中找到先序序列的第二个结点，其下标为k;numLeft为（左）子树的结点个数
    int k, numLeft = 0;
    for (k = postL; k < postR; k++){
        numLeft++;
        if(post[k] == pre[preL+1]){
            break;
        }
    }
    if(k == postR - 1){
        isUnique = false;
    }
    root->lchild = create(preL + 1, preL + numLeft, postL, k);//建立左子树
    root->rchild = create(preL + numLeft + 1, preR, k + 1, postR - 1);//建立右子树
    return root;//返回根结点
}

vector<int> in;//中序序列
void inOrder(Node* root){
    if(!root){
        return;
    }
    inOrder(root->lchild);
    in.push_back(root->data);
    inOrder(root->rchild);
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pre[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &post[i]);
    }
    Node *root = create(0, n - 1, 0, n - 1);
    inOrder(root);
    printf(isUnique ? "Yes\n" : "No\n");
    for (int i = 0; i < in.size(); i++)
    {
        printf("%d", in[i]);
        printf((i + 1 < in.size()) ? " " : "\n");
    }
    return 0;
}
#include<cstdio>
#include<queue>
using namespace std;

struct Node{
    int data;//数据域
    int layer; //层次遍历中记录每个节点所处层次
    Node *lchild;//指向左子树根节点的指针
    Node *rchild;//指向右子树根节点的指针
};
Node *root = NULL;

//新建结点
Node* newNode(int v){
    Node *node = new Node;//申请一个node型变量的地址空间
    node->data = v;
    node->lchild = node->rchild = NULL;
    return node;
}

//查找所有数据域为给定数据域的结点，并将它们的数据域修改为给定的数据域
void search(Node* root, int x, int newdata){
    if(root == NULL){
        return;
    }
    if(root->data == x){
        root->data = newdata;
    }
    search(root->lchild, x, newdata);
    search(root->rchild, x, newdata);
}

//insert在二叉树中插入一个数据域为x的新结点
void insert(Node* &root, int x){//注意根节点指针要使用指针
    if(root == NULL){
        root = newNode(x);//不使用引用，对root的修改无法作用到原变量上去
        return;
    }
    // if(){//由二叉树的性质，x应该插在左子树
    //     insert(root->lchild, x);
    // }else{
    //     insert(root->rchild, x);
    // }
}

//二叉树的建立
Node* create(int data[], int n){
    Node *root = NULL;//新建空根节点root
    for (int i = 0; i < n; i++)
    {
        insert(root, data[i]);
    }
    return root;
}

//二叉树三种遍历
void preorder(Node* root){
    if(root == NULL){
        return;
    }
    printf("%d\n", root->data);
    preorder(root->lchild);
    preorder(root->rchild);
}

void inorder(Node* root){
    if(root == NULL){
        return;
    }
    preorder(root->lchild);
    printf("%d\n", root->data);
    preorder(root->rchild);
}

void postorder(Node* root){
    if(root == NULL){
        return;
    }    
    preorder(root->lchild);
    preorder(root->rchild);
    printf("%d\n", root->data);
}

//层次遍历，计算每个结点所处的层次
void LayerOrder(Node* root){
    //队列中元素是Node*型而不是Node型：队列中保存的只是原元素的一个副本，因此如果队列中直接存放node型，当需要修改队首元素时，就会无法对原元素进行修改
    queue<Node *> q; //注意队列里存的是地址
    root->layer = 1;//根节点的层号为1
    q.push(root);//根结点入队
    while(!q.empty()){
        Node *now = q.front();//取出队首元素
        q.pop();
        printf("%d", now->data);//访问队首元素
        if(now->lchild != NULL){//左子树非空
            now->lchild->layer = now->layer + 1;//左孩子层号为当前层号加1
            q.push(now->lchild);
        }
        if(now->rchild != NULL){
            now->rchild->layer = now->layer + 1;
            q.push(now->rchild);
        }
    }
}

//给定一颗二叉树的先序遍历序列和中序遍历序列，重建二叉树
//先序序列区间[preL,preR]，中序序列空间为[inL,inR]，返回根结点地址
int pre[100],in[100];//分别存放先序中序序列
Node* create(int preL, int preR, int inL, int inR){
    if(preL > preR){
        return NULL;//先序序列长度小于等于0时直接返回
    }
    Node *root = new Node;//新建一个新的结点，用来存放当前二叉树的根结点
    root->data = pre[preL];//新结点的数据域为根结点的值
    int k;
    for (k = inL; k <= inR; k++){//在中序序列中找到in[k] == pre[preL]的结点
        if(in[k] == pre[preL]){
            break;
        }
    }
    int numLeft = k - inL;//左子树结点个数
    root->lchild = create(preL + 1, preL + numLeft, inL, k - 1);//返回左子树的根节点地址，赋值给root的左指针
    root->rchild = create(preL + numLeft + 1, preR, k + 1, inR);
    return root;
}
#include<cstdio>
#include<queue>
using namespace std;

struct Node{
    int data;//数据域
    Node *lchild;//指向左子树根节点的指针
    Node *rchild;//指向右子树根节点的指针
};

Node* newNode(int v){
    Node *node = new Node;//申请一个node型变量的地址空间
    node->data = v;
    node->lchild = node->rchild = NULL;
    return node;
}

//查找二叉查找树中数据域为x的结点
void search(Node* root, int x){
    if(root == NULL){//空树，查找失败
        printf("search failed");
        return;
    }
    if(x == root->data){
        printf("%d\n", root->data);
    }else if(x < root->data){
        search(root->lchild, x);
    }else{
        search(root->rchild, x);
    }
}

//在二叉树中插入一个数据域为x的新结点
void insert(Node* &root, int x){
    if(root == NULL){
        root = newNode(x);
        return;
    }
    if(x == root->data){
        return;
    }else if(x < root->data){
        insert(root->lchild, x);
    }else{
        insert(root->rchild, x);
    }
}

//二叉查找树的建立
Node* create(int data[], int n){
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        insert(root, data[i]);
    }
    return root;
}

//删除以root为根结点的树中权值为x的结点
//寻找以root为根结点的树中的最大权值结点，用以辅助寻找结点的前驱
Node* findMax(Node* root){
    while(root->rchild != NULL){
        root = root->rchild;
    }
    return root;
}
//寻找以root为根结点的树中的最小权值结点，用以辅助寻找结点的后继
Node* findMin(Node* root){
    while(root->lchild != NULL){
        root = root->lchild;
    }
    return root;
}

void deleteNode(Node* &root, int x){
    if(root == NULL){//不存在权值为x的结点
        return;
    }
    if(root->data == x){//找到想要删除的结点
        if(root->lchild == NULL && root->rchild == NULL){//如果是叶子结点
            root = NULL;//把root地址设为NULL，父结点就引用不到了
        }else if(root->lchild != NULL){//左子树不为空
            Node *pre = findMax(root->lchild);//找root前驱
            root->data = pre->data;//用前驱覆盖root
            deleteNode(root->lchild, pre->data);//在左子树中删除结点pre
        }else{//右子树不为空时
            Node *next = findMin(root->rchild);
            root->data = next->data;
            deleteNode(root->rchild, next->data);
        }
    }else if(root->data > x){
        deleteNode(root->lchild, x);//在左子树中递归删除权值为x的结点
    }else{
        deleteNode(root->rchild, x);
    }
}
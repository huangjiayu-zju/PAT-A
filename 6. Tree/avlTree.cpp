#include<cstdio>
#include<algorithm>
using namespace std;

struct Node{
    int data, height;//data为结点权值，height为当前子树高度
    Node *lchild, *rchild;//左右孩子结点地址
};

//生成一个新结点，v为结点权值
Node* newNode(int v){
    Node *node = new Node;
    node->data = v;
    node->height = 1;//结点初始高度为1
    node->lchild = node->lchild = NULL;
    return node;
}

//获取以root为根结点的子树的当前height
int getHeight(Node* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}

//计算结点root的平衡因子
int getBalanceFactor(Node* root){
    return getHeight(root->lchild) - getHeight(root->rchild);
}

//更新结点root的height
void updateHeight(Node* root){
    //max(左孩子的height, 右孩子的height) + 1
    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}

//查找AVL树中数据域为x的结点
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

//插入权值为v的结点
//左旋(Left Rotation):1. 让B的左子树成为A的右子树2. 让A成为B的左子树3.将根结点设定为B
void L(Node* &root){
    Node *temp = root->rchild; //root指向结点A，temp指向结点B
    root->rchild = temp->lchild;//步骤1
    temp->lchild = root;//步骤2
    updateHeight(root);//更新结点A的深度
    updateHeight(temp);//更新结点B的深度
    root = temp;//步骤3
}

//右旋(Right Rotation)
void R(Node* &root){
    Node *temp = root->lchild; //root指向结点A，temp指向结点B
    root->lchild = temp->rchild;//步骤1
    temp->rchild = root;//步骤2
    updateHeight(root);//更新结点A的深度
    updateHeight(temp);//更新结点B的深度
    root = temp;//步骤3
}

void insert(Node* &root, int v){
    if(root == NULL){//到达空结点
        root = newNode(v);
        return;
    }
    if(v < root->data){//v比根结点的权值小
        insert(root->lchild, v); //往左子树插入
        updateHeight(root);//更新树高
        if(getBalanceFactor(root) == 2){
            if(getBalanceFactor(root->lchild) == 1){//LL型，根结点做一次右旋
                R(root);
            }else if(getBalanceFactor(root->lchild) == -1){//LR型，左孩子做一次左旋，根结点一次右旋
                L(root->lchild);
                R(root);
            }
        }
    }else{// v比结点的权值大
        insert(root->rchild, v); 
        updateHeight(root);
        if(getBalanceFactor(root) == -2){
            if(getBalanceFactor(root->rchild) == -1){//RR型，根结点做一次左旋
                L(root);
            }else if(getBalanceFactor(root->rchild) == 1){//RL型，右孩子做一次右旋，根结点一次左旋
                R(root->rchild);
                L(root);
            }
        }
    }
}

//AVL树的建立
Node* create(int data[], int n){
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        insert(root, data[i]);
    }
    return root;
}
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

struct Node{
    int data, height;//data为结点权值，height为当前子树高度
    Node *lchild, *rchild;//左右孩子结点地址
}*root;

Node* newNode(int v){
    Node *node = new Node;
    node->data = v;
    node->height = 1;
    node->lchild = node->lchild = NULL;
    return node;
}

int getHeight(Node* root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}

int getBalanceFactor(Node* root){
    return getHeight(root->lchild) - getHeight(root->rchild);
}

void updateHeight(Node* root){
    root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
}

void L(Node* &root){
    Node *temp = root->rchild; 
    root->rchild = temp->lchild;
    temp->lchild = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

void R(Node* &root){
    Node *temp = root->lchild; 
    root->lchild = temp->rchild;
    temp->rchild = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

void insert(Node* &root, int v){
    if(root == NULL){
        root = newNode(v);
        return;
    }
    if(v < root->data){
        insert(root->lchild, v); 
        updateHeight(root);
        if(getBalanceFactor(root) == 2){
            if(getBalanceFactor(root->lchild) == 1){
                R(root);
            }else if(getBalanceFactor(root->lchild) == -1){
                L(root->lchild);
                R(root);
            }
        }
    }else{
        insert(root->rchild, v); 
        updateHeight(root);
        if(getBalanceFactor(root) == -2){
            if(getBalanceFactor(root->rchild) == -1){
                L(root);
            }else if(getBalanceFactor(root->rchild) == 1){
                R(root->rchild);
                L(root);
            }
        }
    }
}

void levelOrder(Node* root, int n){
    queue<Node *> q;
    q.push(root);
    while(!q.empty()){
        Node *front = q.front();
        q.pop();
        printf("%d", front->data);
        n--;
        printf(n ? " " : "\n");
        if(front->lchild){
            q.push(front->lchild);
        }
        if(front->rchild){
            q.push(front->rchild);
        }
    }
}

bool judgeCompleteTree(Node *root, int n){
    queue<Node *> q;
    q.push(root);
    while(n){
        Node *front = q.front();
        q.pop();
        if(front == NULL){
            return false;
        }
        n--;
        q.push(front->lchild);
        q.push(front->rchild);
    }
    return true;
}

int main(){
    int n, v;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v);
        insert(root, v);
    }
    levelOrder(root, n);
    printf(judgeCompleteTree(root, n) ? "YES\n" : "NO\n");
    return 0;
}
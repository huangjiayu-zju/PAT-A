#include<cstdio>
#include<vector>
using namespace std;

struct Node{
    int data;
    Node *lchild;
    Node *rchild;
};

Node* newNode(int v){
    Node *node = new Node;
    node->data = v;
    node->lchild = node->rchild = NULL;
    return node;
}

void insert(Node* &root, int v){
    if(root == NULL){
        root = newNode(v);
        return;
    }
    // !!!没有通过是这里的原因，题目输入结点值可以相同，root->data一开始是根结点的值，后面的值输入进来会被忽略
    // if(root->data == v){
    //     return;
    // }
    if(root->data > v){
        insert(root->lchild, v);
    }else{
        insert(root->rchild, v);
    }
}

void preOrder(Node* root, vector<int>& vi){
    if(root == NULL){
        return;
    }
    vi.push_back(root->data);
    preOrder(root->lchild,vi);
    preOrder(root->rchild,vi);
}

void preOrderMirror(Node* root, vector<int>& vi){
    if(root == NULL){
        return;
    }
    vi.push_back(root->data);    
    preOrderMirror(root->rchild,vi);
    preOrderMirror(root->lchild,vi);
}

void postOrder(Node* root, vector<int>& vi){
    if(root == NULL){
        return;
    }
    postOrder(root->lchild,vi);
    postOrder(root->rchild,vi);
    vi.push_back(root->data);
}

void postOrderMirror(Node* root, vector<int>& vi){
    if(root == NULL){
        return;
    }        
    postOrderMirror(root->rchild,vi);
    postOrderMirror(root->lchild,vi);
    vi.push_back(root->data);
}

void print(vector<int> vi){
    for (int i = 0; i < vi.size(); i++)
    {
        if(i > 0){
            printf(" ");
        }
        printf("%d", vi[i]);        
    }   
}

int main(){
    vector<int> origin, pre, post, preM, postM;//初始序列，先序、后序，镜像树先序、后序    
    int n, data;
    scanf("%d", &n);
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        origin.push_back(data);
        insert(root, data);
    }
    preOrder(root, pre);
    preOrderMirror(root, preM);
    postOrder(root, post);
    postOrderMirror(root, postM);
    if(pre == origin){//vector可以直接用==比较
        printf("YES\n");
        print(post);
    }else if(preM == origin){
        printf("YES\n");
        print(postM);
    }else{
        printf("NO\n");
    }
    return 0;
}






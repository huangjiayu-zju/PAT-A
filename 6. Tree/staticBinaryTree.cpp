#include<cstdio>
const int maxn = 110;

struct Node{
    int data;
    int lchild;
    int rchild;
} node[maxn];

int index = 0;
int newNode(int v){
    node[index].data = v;
    node[index].lchild = -1;
    node[index].rchild = -1;
    return index++;
}

void search(int root, int x, int newdata){
    if(root == -1){
        return;
    }
    if(node[root].data == x){
        node[root].data = newdata;
    }
    search(node[root].lchild, x, newdata);
    search(node[root].rchild, x, newdata);
}

void insert(int &root, int x){
    if(root == -1){
        root = newNode(x);
        return;
    }
    // if(由二叉树的性质，x应该插在左子树){
    //     insert(node[root].lchild, x);
    // }
    else{
        insert(node[root].rchild, x);
    }
}

int create(int data[], int n){
    int root = -1;
    for (int i = 0; i < n; i++)
    {
        insert(root, data[i]);
    }
    return root;
}
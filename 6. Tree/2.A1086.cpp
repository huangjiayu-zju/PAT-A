#include<cstring>
#include<stack>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 40;

struct Node{
    int data;
    Node *lchild;
    Node *rchild;
};
int pre[maxn], post[maxn], in[maxn];
int n;

Node* create(int preL, int preR, int inL, int inR){
    if(preL > preR){
        return NULL;
    }
    Node *root = new Node;
    root->data = pre[preL];
    int k;
    for (k = inL; k <= inR; k++){
        if(in[k] == pre[preL]){
            break;
        }
    }
    int numLeft = k - inL;
    root->lchild = create(preL + 1, preL + numLeft, inL, k - 1);
    root->rchild = create(preL + numLeft + 1, preR, k + 1, inR);
    return root;
}

int num = 0;
void postorder(Node* root){
    if(root==NULL){
        return;
    }
    postorder(root->lchild);
    postorder(root->rchild);
    printf("%d", root->data);
    num++;
    if(num < n){
        printf(" ");
    }
}

int main(){
    scanf("%d", &n);
    char str[5];
    stack<int> st;
    int x, preIndex = 0, inIndex = 0;//入站元素、先序序列位置及中序序列位置
    for (int i = 0; i < 2*n; i++)
    {
        scanf("%s", str);
        if(strcmp(str,"Push") == 0){//入栈，更新先序序列
            scanf("%d", &x);
            pre[preIndex++] = x;
            st.push(x);
        }else{
            in[inIndex++] = st.top();//出栈，更新中序序列
            st.pop();
        }
    }
    Node *root = create(0, n - 1, 0, n - 1);//建树
    postorder(root);
    return 0;
}
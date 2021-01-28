#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn = 30;

//进行层序遍历，让空结点也入队，如果在访问完N个非空结点之前访问到了空结点，那么说明不是完全二叉树

bool isRoot[maxn];//节点是否是根结点
struct Node{
    int left, right;//左右结点的下标
} node[maxn];

//input函数输入数据
int input(){
    char id[3];
    scanf("%s", id);
    if(id[0] == '-'){
        return -1;
    }else if(strlen(id) == 1){
        return id[0] - '0';
    }else{
        return (id[0] - '0') * 10 + (id[1] - '0');
    }
}

//找到根结点函数编号
int findRoot(int n){
    for (int i = 0; i < n; i++){
        if(isRoot[i]){
            return i;
        }
    }
    return -1;
}

//BFS判断完全二叉树，root为根结点编号，last是最后一个结点编号（注意引用），n为结点个数
bool BFS(int root, int &last, int n){
    queue<int> q; 
    q.push(root);
    while(n){
        int front = q.front();
        q.pop();
        if(front == -1){
            return false;   //访问到空结点，一定是非完全二叉树
        }
        n--;
        last = front;   //记录最后一个非空结点编号
        q.push(node[front].left);
        q.push(node[front].right);
    }
    return true;
}

int main(){
    int n;
    scanf("%d", &n);
    memset(isRoot, true, sizeof(isRoot));
    for (int i = 0; i < n; i++){
        int left = input(), right = input();
        isRoot[left] = isRoot[right] = false;
        node[i].left = left;
        node[i].right = right;
    }
    int root = findRoot(n), last;
    bool isCompleteTree = BFS(root, last, n);
    if(isCompleteTree){
        printf("YES %d\n", last);
    }else{
        printf("NO %d\n", root);
    }
    return 0;
}
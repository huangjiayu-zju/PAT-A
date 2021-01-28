#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1010;

int number[maxn], CBT[maxn], n, index = 0; //number存放结点权值，CBT存放完全二叉树，n为结点数，index从小到大枚举number数组

void inOrder(int root){//DFS的逻辑,重要
    if(root > n){//空结点，直接返回
        return;
    }
    inOrder(2 * root);//往左子树递归
    CBT[root] = number[index++];//根结点处赋值number[index]
    inOrder(2 * root + 1);//往右子树递归
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &number[i]);
    }
    sort(number, number + n);//从小到大排序number数组
    inOrder(1);//1号位为根结点
    for (int i = 1; i <= n; i++)
    {
        printf("%d", CBT[i]);//CBT数组是按照二叉树的层序来存放结点
        if(i < n){
            printf(" ");
        }
    }
    return 0;
}


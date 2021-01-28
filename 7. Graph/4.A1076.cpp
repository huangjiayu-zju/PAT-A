#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int maxn = 1010;

struct Node{
    int v;//结点编号从1开始
    int layer; //层号
};
vector<Node> Adj[maxn];
bool inq[maxn] = {false};


int BFS(int s, int L){//s为初始结点，l为层数上限
    int numForward = 0;//最大转发数 = 遍历到的结点数之和
    queue<Node> q;
    Node start;
    start.v = s;
    start.layer = 0;
    q.push(start);
    inq[start.v] = true;
    while(!q.empty()){
        Node topNode = q.front();
        q.pop();
        int u = topNode.v;
        for (int i = 0; i < Adj[u].size(); i++)//这里i是0不是1
        {
            Node next = Adj[u][i];
            next.layer = topNode.layer + 1;
            if(inq[next.v] == false && next.layer <= L){
                q.push(next);
                inq[next.v] = true;
                numForward++;
            }
        }        
    }
    return numForward;
}

int main(){
    int n, l, numFollow, idFollow;  //结点个数、层数上限、用户关注人数，用户关注的id
    Node user;
    scanf("%d%d", &n, &l);
    for (int i = 1; i <= n; i++)    //i为用户编号
    {
        user.v = i; //用户编号为i
        scanf("%d", &numFollow); //第i号用户关注的人数
        for (int j = 0; j < numFollow; j++){
            scanf("%d", &idFollow); //i号用户关注的用户编号
            Adj[idFollow].push_back(user);
        }
    }
    int numQuery, s;
    scanf("%d", &numQuery);
    for (int i = 0; i < numQuery; i++)
    {
        memset(inq, false, sizeof(inq));//别忘记每次循环都更新inq数组
        scanf("%d", &s);
        printf("%d\n", BFS(s, l));
    }
    return 0;
}









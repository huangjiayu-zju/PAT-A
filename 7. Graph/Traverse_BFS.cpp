#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int maxv = 1000;  //最大顶点数
const int INF = 1000000000; //设INF为一个很大的数

//三、BFS遍历图邻接矩阵版
int n, G[maxv][maxv];//n为顶点数
bool inq[maxv] = {false};

void BFS(int u){
    queue<int> q;
    q.push(u);
    inq[u] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++)
        {
            if(inq[v] == false && G[u][v] != INF){
                q.push(v);
                inq[v] == true;
            }
        }
        
    }
}

void BFSTrave(){
    for (int i = 0; i < n; i++)
    {
        if(inq[i] == false){
            BFS(i);
        }
    }
    
}

//四、BFS遍历图邻接表版（输出顶点所在层号）
struct Node{
    int v;  //顶点编号
    int layer;  //顶点层号
};
vector<Node> Adj[maxv]; //vector元素为Node型
int n;
bool inq[maxv] = {false};

void BFS(int s){//s为起始结点编号
    queue<Node> q;
    Node start;
    start.v = s;    
    start.layer = 0;   //起始顶点层号为0
    q.push(start);
    inq[start.v] = true;
    while(!q.empty()){
        Node topNode = q.front();
        q.pop();
        int u = topNode.v;  //队首顶点编号
        for (int i = 0; i < Adj[u].size(); i++){
            Node next = Adj[u][i]; //从u出发能到达的结点next
            next.layer = topNode.layer + 1;
            if(inq[next.v] == false){
                q.push(next);
                inq[next.v] = true;
            }
        }        
    }
}

void BFSTrave(){
    for (int i = 0; i < n; i++)
    {
        if(inq[i] == false){
            BFS(i);
        }
    }
    
}
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 100;
struct Node{
    int x, y; //位置x,y
} node;

int n, m;//矩阵大小n*m
int matrix[maxn][maxn];//01矩阵
bool inq[maxn][maxn] = {false};//记录(x,y)是否已入过队
//设置两个增量数组，表示四个方向
int X[4] = {0, 0, 1, -1};
int Y[4] = {0, 0, 1, -1};

bool judge(int x,int y){ //判断坐标(x,y)是否需要访问
    if(x >= n || x < 0 || y >= m || y < 0){
        return false;
    }
    if(matrix[x][y] == 0||inq[x][y] == true){
        return false;
    }
    return true;
}

//BFS访问位置(x,y)所在的块，将块中所有"1"的inq都设置为true
void BFS(int x, int y){
    queue<Node> q;//定义队列
    node.x = x, node.y = y;//当前结点的坐标为(x,y)
    q.push(node);
    inq[x][y] = true;
    while(!q.empty()){
        Node top = q.front();//取出队首元素
        q.pop();
        for (int i = 0; i < 4; i++)//枚举4个方向
        {
            int newX = top.x + X[i];
            int newY = top.y + Y[i];
            if(judge(newX, newY)){//如果新位置未被访问过
                node.x = newX, node.y = newY;
                q.push(node);//将结点node入队
                inq[newX][newY] = true;//设置位置(newX,newY)已经入队
            }
        }
        
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int x = 0; x < n; x++){
        for (int y = 0; y < m; y++){
            scanf("%d", &matrix[x][y]);
        }
    }
    int ans = 0;//存放块数
    for (int i = 0; i < n; i++){//枚举每一个位置
        for (int j = 0; j < m; j++){
            //如果元素为1且未入队过
            if(matrix[i][j] == 1 && inq[i][j] == false){
                ans++;
                BFS(i, j);
            }

        }
    }
    printf("%d\n", ans);
    return 0;
}
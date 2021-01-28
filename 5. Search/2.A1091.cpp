#include<cstdio>
#include<queue>
using namespace std;

struct Node{
    int x, y, z;
}node;
int n, m, l, t;//矩阵m*n*l
int pixel[1290][130][61];
bool inque[1290][130][61] = {false};
int X[6] = {0, 0, 1, -1, 0, 0};
int Y[6] = {0, 0, 0, 0, 1, -1};
int Z[6] = {1, -1, 0, 0, 0, 0};

bool judge(int x, int y, int z){
    if(x >= m || x < 0 || y >= n || y < 0 || z >= l || z < 0){
        return false;
    }
    if(pixel[x][y][z]==0 || inque[x][y][z]==true){
        return false;
    }
    return true;
}

int BFS(int x, int y, int z){
    int total = 0;//记录当前块中1的个数
    queue<Node> q;
    node.x = x, node.y = y, node.z = z;
    q.push(node);
    inque[x][y][z] = true;
    while(!q.empty()){//处理当前块
        Node top = q.front();
        q.pop();
        total++;
        for (int i = 0; i < 6; i++){
            int newX = top.x + X[i];
            int newY = top.y + Y[i];
            int newZ = top.z + Z[i];            
            if(judge(newX,newY,newZ)){   
                //total++;    //第一次写的时候放在了这里，导致出错，应该直接记录出队列的结点个数就好
                node.x = newX, node.y = newY, node.z = newZ;
                q.push(node);
                inque[newX][newY][newZ] = true;
            }
        }
        
    }
    if(total >= t){
        return total;
    }
    else{
        return 0;
    }
}

int main(){
    scanf("%d%d%d%d", &m, &n, &l, &t);
    for (int i = 0; i < l; i++){
        for (int j = 0; j < m; j++){
            for (int k = 0; k < n; k++){
                scanf("%d", &pixel[j][k][i]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < l; i++){
        for (int j = 0; j < m; j++){
            for (int k = 0; k < n; k++){
                if(pixel[j][k][i] == 1 && inque[j][k][i] == false){
                    ans += BFS(j, k, i);
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
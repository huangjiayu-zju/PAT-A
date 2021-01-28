#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 10010;

/*
先判定给定的数据能否使图连通，这点很容易用并查集来判断。
当图连通时，由于题目保证只有N-1条边，因此一定能确定是一棵树
下面选择合适的根结点，使得树的高度最大。具体做法是：
先任意选择一个结点，从该结点开始遍历树，获取能达到的最深的顶点(记为结点集合A)
然后从集合A中任意一个结点出发遍历整个树，获取能达到的最深的顶点(记为结点集合B)
这样集合A与集合B的并集即为所求的使树高最大的结点
*/

bool isRoot[maxn];  //记录每个结点是否作为某个集合的根结点
int father[maxn];

void init(int n){
    for (int i = 1; i <= n; i++)
    {
        father[i] = i;
    }
}

int findFather(int x){
    int a = x;
    while(x != father[x]){
        x = father[x];
    }
    while(a != father[a]){
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

void Union(int a, int b){
    int faA = findFather(a);
    int faB = findFather(b);
    if(faA != faB){
        father[faA] = faB;
    }
}

int calBlock(int n){    //计算连通块数目
    int Block = 0;
    for (int i = 1; i <= n; i++)
    {
        isRoot[findFather(i)] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        if(isRoot[i]){
            Block++;
        }
    }
    return Block;
}

vector<int> G[maxn]; //邻接表
int maxH = 0;   //最大高度
vector<int> temp, ans;  //temp临时存放DFS的最远结点结果，Ans保存答案

void DFS(int u, int depth, int pre){//u是当前访问结点编号，height为当前树高，pre为u的父节点
    if(maxH < depth){   //如果获得了更大树高
        temp.clear();
        temp.push_back(u);
        maxH = depth;
    }else if(maxH == depth){    //如果树高等于最大树高
        temp.push_back(u);
    }
    for (int i = 0; i < G[u].size(); i++)   //遍历u的所有子结点
    {
        if(G[u][i] == pre){ //由于邻接表中存放无向图，因此需要跳过回去的边
            continue;
        }
        DFS(G[u][i], depth + 1, u); //访问子结点
    }    
}

int main(){
    int a, b, n;
    scanf("%d", &n);
    init(n);    //并查集初始化
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
        Union(a, b);    //合并a，b所在的集合
    }
    int block = calBlock(n);    //计算集合数目
    if(block != 1){
        printf("Error: %d components\n", block);
    }else{  //图是连通的，那么一次DFS可完成了整个图的遍历，得到最深高度和相应顶点
        DFS(1, 1, -1); //从1号结点开始DFS，初始高度为1。
        ans = temp;
        DFS(ans[0], 1, -1);//从任意一个根结点开始遍历，temp中保存了结点集合B
        for (int i = 0; i < temp.size(); i++)
        {
            ans.push_back(temp[i]); //ans中存放了集合A和集合B的并集
        }
        sort(ans.begin(),ans.end());    //按从小到大排序
        printf("%d\n", ans[0]);
        for (int i = 1; i < ans.size(); i++)
        {
            if(ans[i] != ans[i-1]){
                printf("%d\n", ans[i]); //重复编号不输出
            }
        }
        
    }
    return 0;
}

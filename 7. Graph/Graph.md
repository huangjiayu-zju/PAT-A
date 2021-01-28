## 图的存储 
邻接矩阵：设图G(V,E)的顶点编号为0,1,...,N-1，则如果G[i][j]为0，说明顶点i和顶点j之前不存在边。邻接矩阵只适用于顶点数目不太大(一般不超过1000)的题目

邻接表：如果把同一个顶点的所有出边放在一个列表中，那么N个顶点就会有N个列表（没有出边，则对应空表），这N个列表被称为图G的邻接表。用vector来实现邻接表。
```c
//vector<int> Adj[N]; //邻接表只存放每条边的终点编号而不存放边权。
struct Node{
    int v; //边的终点编号
    int w; //边权
    Node(int _v, int _w) : v(_v), w(_w) {}  //构造函数
};
vector<Node> Adj[N];
Adj[1].push_back(Node(3,4)); //构造函数可以不定义临时变量来实现加边操作
```

## 图的遍历 1~4
DFS遍历图的基本思路就是将经过的顶点设置为已访问，在下次递归碰到这个结点时就不再去处理，直到整个图的顶点都被标记为已访问。如果已知给定的图是一个连通图，则只需要一次DFS就能完成遍历。
```c
DFS(u){ //访问顶点u
    vis[u] = true; //设置u已被访问
    for(从u出发能到达的所有顶点v){  //枚举从u出发可以到达的所有顶点v
        if(vis[v] == false){    //如果v未被访问
            DFS(v); //递归访问v
        }
    }
}
DFSTrave(G){    //遍历图G
    for(G的所有顶点u){  //对图G的所有顶点u
        if(vis[u] == false){    //如果u未被访问
            DFS(u); //访问u所在的连通块
        }
    }
}
```
BFS遍历图的基本思想是建立一个队列，并把从该顶点出发可以到达的未曾加入过队列(而不是访问)的顶点全部加入队列，直到队列为空
```c
bool inq[maxn] = {false}
BFS(u){ //  遍历u所在的连通块
    queue q;    //定义队列q
    将u入队;
    inq[u] = true;  //设置u已被加入过队列
    while(q非空){   //只要队列非空
        取出q的队首元素u进行访问;
        for(从u出发可达的所有顶点v){    //枚举从u能直接到达的顶点v
            if(inq[v] == false){    //如果v未曾加入过队列
                将v入队;
                inq[v] = true;  //设置v已被加入过队列
            }
        }
    }
}
BFSTrave(G){    //遍历图G
    for(G的所有顶点u){  //枚举G的所有顶点
        if(inq[u] == false){    //如果u未曾加入过队列
            BFS(u); //遍历u所在的连通块
        }
    }
}
```

## 最短路径
对任意给出的图G(V,E)和起点S、终点T，如何求从S到T的最短路径
### Dijkstra
解决单源最短路问题，即给定图G(V,E)和起点s，求从起点s到达其它顶点的最短距离

设集合S存放已被访问的结点（即已经确定该结点的最短距离），然后执行n次下面的步骤（n为结点个数）
1. 每次从集合V-S（即未确定最短距离）中选择与起点s的最短距离最小的一个顶点（记为u），访问并加入集合S（设置其距离已经被确定）
2. 之后，令u为中介点，优化起点s与所有从u能到达的顶点v之间的最短距离

集合S的实现、起点s到达顶点$V_i$(0<=i<=n-1)的最短距离的实现
- 集合S可以用一个bool型数组vis\[]来实现，vis[i] = true表示顶点$V_i$已经被访问
- 令int型数组d\[]表示起点s到达顶点$V_i$的最短距离，初始时除了起点s的d[s]赋为0，其余顶点都赋为一个很大的数(0x3fffffff)。
```
//G为图，一般设置为全局变量；数组d为源点到达各点的最短路径长度，s为起点
Dijkstra(G,d[],s){
    初始化;
    for(循环n次){
        u = 使d[u]最小的还未被访问的顶点的标号;
        设u已被访问;
        for(从u出发能到达的所有顶点v){
            if(v未被访问&&以u为中介点使s到顶点v的最短距离d[v]更优){
                优化d[v];
            }
        }
    }
}
```

- 临界矩阵的时间复杂度$O(V^2)$，邻接表的时间复杂度$O(V^2+E)$。注意到寻找最小d[u]的过程可以不必达到O(V)的复杂度，而可以使用堆优化来降低复杂度。使用STL中的优先队列使得邻接表实现的算法时间复杂度降为$O(VLogV+E)$
- Dijkstra算法只能应对所有边权都是非负数的情况，如果出现负数最好使用SPFA算法
- 如果题目给出的是无向边，只需要把无向边当成两条指向相反的有向边即可，在输入的时候进行处理。

求解从起点$V_1$到达$V_i$最短路径：设置数组pre\[]，令pre[v]表示从起点到顶点v的最短路径上v的前一个结点，当条件成立时将u赋给pre[v]
```
if(v未被访问&&以u为中介点使s到顶点v的最短距离d[v]更优){
    优化d[v];
    令v的前驱为u;
}
```
然后用递归不断利用pre[]的信息寻找前驱，直至到达起点后从递归深处开始输出。

如果碰到有两条即两条以上可以达到最短距离的路径，题目会给出一个第二标尺（第一标尺是距离），要求在所有最短路径中选择第二标尺最优的一条路径
1. 给每条边再增加一个边权（比如说花费），然后要求再最短路径有多条时要求路径上的花费之和最小
2. 给每个点增加一个点权（例如每个城市能搜集到的物资），然后在最短路径有多条时要求路径上的点权之和最大
3. 直接问有多少条最短路径

对这三种出题方法，都只需要增加一个数组来存放新增的边权或点券或最短路径条数，然后在算法中修改**优化d[v]**的那个步骤即可
1. 新增边权。以新增的边权代表花费为例，用cost[u][v]表示u->的花费（由题目输入），并增加一个数组c\[]，令从起点s到达顶点u的最少花费为c[u]，初始化时只有c[s] = 0、其余c[u]均为INF。这样在`d[u] + G[u][v] < d[v]`（即可以使s到v的最短距离d[v]更优）时更新d[v]和c[v]，当`d[u] + G[u][v] == d[v]`（即最短距离相同）且`c[u]+cost[u][v]<c[v]`（即可以使s到v的最少花费更优）时更新c[v],`c[v]=c[u]+cost[u][v]`。
2. 新增点权。以新增的点权代表城市中能收集到的物资为例，用weight[u]表示城市u中的物资数目（由题目输入），并增加一个数组w\[]，令从起点s到达顶点u可以收集到的最大物资为w[u],初始化时w[s]为weight[s]，其余均为0。更新方法同上
3. 求最短路径条数。只需要增加一个数组num[\]，令从起点s到达顶点u的最短路径条数为num[u]，初始化时只有num[s]为1、其余num[n]均为0。更新方法与上面稍有不同，在`d[u] + G[u][v] < d[v]`（即可以使s到v的最短距离d[v]更优）时更新d[v]，并让num[v]继承num[u](num[v]=num[u])，而当`d[u] + G[u][v] == d[v]`（即最短距离相同）时将num[u]加到num[v]上((num[v]+=num[u]))。

```c
for (int v = 0; v < n; v++){                //遍历所有顶点v
    //如果v未被访问 && u能到达v
    if(vis[v] == false && G[u][v] != INF){
        if(d[u] + G[u][v] < d[v]){          //以u为中介点可以使d[v]更优
            d[v] = d[u] + G[u][v];
            更新第二标尺;    
        }else if(d[u] + G[u][v] == d[v] && 第二标尺可以更优){
            更新第二标尺;
        }
    }
}
```

#### DFS+Dijkstra
如果出现了一些逻辑更为复杂的计算边权或点权的方式，此时按上面的方式只使用Dijkstra算法就不一定能计算出正确结果（原因时不一定满足最优子结构），或者即使能算出，逻辑也极其复杂，容易写错。可以用一种更通用、又模板化的方式解决此类问题——**Dijkstra + DFS**。

先在Dijkstra算法中记录下所有最短路径（只考虑距离），然后从这些最短路径中选出一条第二标尺最优的路径（因为在给定一一条路径的情况下，针对这条路径的信息都可以通过边权和点权很容易计算出来！）

1. 使用Dijkstra算法记录所有最短路径
   - 定义变长数组pre，存放结点v的所有能产生最短路径的前驱结点`vector<int> pre[maxv]`（注：对需要查询某个顶点u是否在顶点v前驱中的题目，可以把pre数组设置为set\<int>数组，此时使用pre[v].count(u)来查询比较方便），通过vector类型的pre数组，就可以使用DFS来获取所有最短路径。
   - 在更新d[v]的过程中更新pre数组
     - 如果`d[u] + G[u][v] < d[v]`，说明以u为中介点可以使d[v]更优，此时需要令v的前驱结点为u。即清空原先的pre[v]，再添加u。
     - 如果`d[u] + G[u][v] == d[v]`，说明以u为中介点可以找到一条相同距离的路径，因此v的前驱结点在原来的基础上添加上u结点（不必先清空pre[v]）。
2. 遍历所有最短路径，找出一条使第二标尺最优的路径
    - pre数组会产生一条递归树，遍历这条树，每次到达叶子结点，就会产生一条完整的最短路径，因此每得到一条完整路径，就可以对这条路径计算其第二标尺的值，令其与当前第二标尺的最优值进行比较。如果更优则更新最优值，并用这条路径覆盖当前的最优路径。
    - DFS递归函数
      - 全局变量的第二标尺最优值`optValue`，记录最优路径的数组`path`，临时记录DFS遍历到叶子结点时的路径`tempPath`
      - 递归边界：当前访问的结点时叶子结点（路径的起点st）。此时对tempPath中存放的路径求出第二标尺的值value，并与optValue比较，如果更优，则更新optValue并把tempPath覆盖path。
      - 递归式（在递归过程中生成tempPath）：在访问当前结点v时将v加到tempPath的最后面，然后遍历pre[v]中的所有结点并进行递归，等pre[v]的所有结点遍历完毕后再把tempPath最后面的v弹出。注意叶子结点没有办法通过上面写法直接加入tempPath，需要在访问到叶子结点时临时加入（在递归边界中加入）。
      - 存放在tempPath中的路径结点时逆序的，访问结点需要倒着进行。
    - 如果需要同时计算最短路径（指距离最短）的条数，既可以在Dijkstra代码中添加num数组，也可以开一个全局变量来记录最短路径条数，当DFS到达叶子结点时令该全局变量加1
    - 注意顶点的下标范围需要根据题意来考虑是0~n-1还是1~n，或是在某些有n+1个结点的题目里是0~n

### Bellman-Ford算法和SPFA算法
如果出现了负权边，Dijkstra就会失效，而Bellman-Ford算法可解决单源最短路径问题，但也能处理有负边权的情况。因为如果图中有负环，且从源点可以到达，那么就会影响最短路径的求解。

Bellman-Ford算法设置一个数组d，用来存放从源点到各个顶点的最短距离。同时Bellman-Ford算法返回一个bool值：如果其存在从源点可达的负环，那么函数将返回false；否则，函数将返回true，此时数组d中存放的值就是从源点到达各顶点的最短距离。
1. 对图中的边进行V-1轮操作，每轮都遍历图中所有的边：对每条边`u->v`，如果以u为中介点可以使d[v]更小，即`d[u] + length[u->u] < d[v]`成立时，用d[u] + length[u->u]更新d[v]（松弛操作）。时间复杂度是`O(VE)`，n(V)是顶点个数，E是边数。
2. 再对所有边进行一轮操作，判断是否有某条边u->v仍然满足`d[u] + length[u->u] < d[v]`，如果有，说明图中有从源点可达的负环，返回false；否则，说明数组d中的所有值都已经达到最优，返回true。
    ```c
    for(i = 0; i < n - 1; i++){ //执行n-1轮操作，其中n为顶点数
        for(each edge u->v){    //每轮操作都遍历所有边
            if(d[u] + length[u->v] < d[v]){ //以u为中介点可以使d[v]更小
                d[v] = d[u] + length[u->v]; //松弛操作
            }
        }
    }
    for(each edge u->v){    //对每条边进行判断
        if(d[u] + length[u->v] < d[v]){ //如果仍可以被松弛
            return false;   //说明图中有从源点可达的负环
        }
    }
    return true;    //数组d中的所有值都已经达到最优
    ```
- Bellman-Ford算法需要遍历所有边，使用邻接表会比较方便；如果使用邻接矩阵，时间复杂度会上升到$O(V^3)$
- 如果在某一轮操作时，发现所有边搜没有被松弛，说明数组d中的所有值都已经达到最优，不需要再继续，提前退出即可。
- 最短路径的求解方法、有多重标尺时的做法均与Dijkstra算法中介绍的相同。唯一要注意的是统计最短路径条数的做法：BF算法期间会多次访问曾经访问过的顶点，因此需要设置记录前驱的数组`set<int> pre[maxn]`,且当遇到一条和已有最短路径长度相同的路径时，必须重新计算最短路径长度。
    ```c
    int num[maxv];  //num[]记录最短路径条数
    set<int> pre[maxv];
    ...
    if(d[u] + dis < d[v]){ //以u为中介点时能令d[u]变小
        ...
        num[v] = num[u];    //和Dijkstra一样覆盖
        pre[v].clear();
        pre[v].insert(u);
    }else if(d[u] + dis == d[v]){   //找到一条相同长度的路径
        ...
        pre[v].insert(u);
        num[v] = 0; //重新统计num[v]
        for(set<int>::iterator it = pre[v].begin(); it != pre[v].end(); it++){
            num[v] += num[*it];
        }
    }
    ```
注意到，BF算法的每轮操作都需要操作所有边，这其中大量无意义的操作严重影响了算法的性能，注意到，**只有当某个顶点u的d[u]值改变时，从它出发的边的临界点v的d[v]值才有可能被改变**。由此可以优化：建立一个队列，每次将队首顶点u取出，然后对从u出发的所有边u->v进行松弛操作，也就是判断`d[u] + length[u->u] < d[v]`是否成立，如果成立，则覆盖，于是d[v]获得更优的值，此时如果v不在队列中，就把v加入队列。这样操作直到队列为空（说明图中没有从源点可达的负环），或是某个顶点的入队次数超过V-1（说明图中存在从源点可达的负环）
```c
queue<int> q;
源点s入队;
while(队列非空){
    取出队首元素u;
    for(u的所有邻接边u->v){
        if(d[u] + dis < d[v]){
            d[v] = d[u] + dis;
            if(v不在当前队列){
                v入队;
                if(v入队次数大于n-1){
                    说明有可达负环,return;
                }
            }
        }
    }
}
```
优化后的算法称为SPFA(Shortest Path Faster Algorithm)，期望时间复杂度是$O(kE)$，E是图的边数，k是一个常数，很多情况下k不超过2，此算法异常高效，并且经常性地优于堆优化的Dijkstra算法。但如果图中有从源点可达的负环，传统SFPA的时间复杂度就会退化成O(VE)。
- 使用SFPA可以判断是否存在从源点可达的负环，但如果负环从源点不可达，则需要添加一个辅助顶点C，并添加一条从源点到达C的有向边以及V-1条从C到达除源点外各顶点的有向边才能判断负环是否存在。
- SPFA十分灵活，其内部的写法可以根据具体场景的不同进行调整，示例代码中的队列可以替换成优先队列以加快速度；或者替换成双端队列，使用SLF优化和LLL优化
- 示例代码是SPFA的BFS版本，如果将队列替换成栈，则可以实现DFS版本的SPFA，对判环有奇效。

### Floyd算法(弗洛伊德算法)
用来解决全源最短路问题，即对给定的图G(V,E)，求任意两点u,v之间的最短路径长度，时间复杂度是$O(n^3)$，顶点数n限制在200内，因此适合用邻接矩阵来实现Floyd算法。

算法基于这样一个事实：如果存在顶点k，使得以k作为中介点时顶点i和顶点j的当前最短距离缩短，则使用顶点k作为顶点i和顶点j的中介点，即当`dis[i][k]+dis[k][j]<dis[i][j]`时，令`dis[i][j]=dis[i][k]+dis[k][j]`（其中dis[i][j]表示从顶点i到顶点j的最短距离）。
```
枚举顶点k∈[1,n]
    以顶点k作为中介点，枚举所有顶点对i和j(i∈[1,n], j∈[1,n])
        如果dis[i][k] + dis[k][j] < dis[i][j]成立
            赋值dis[i][j] = dis[i][k] + dis[k][j]
```
需要注意的是，不能把最外层的k循环放到内层(即产生i->j->k的三种循环)，会导致最后结果出错，因为如果当较后访问的dis[u][v]有了优化之后，前面访问的dis[i][j]会因为已经被访问而无法获得进一步优化(这里i、j先于u、v进行访问)

## 最小生成树
最小生成树(Minimum Spanning Tree, MST)是在一个给定的无向图G(V,E)中求一棵树，使得这棵树拥有图G中的所有顶点，且所有边都是来自图G中的边，并且满足整棵树的边权之和最小。它有三个性质
- 最小生成树是树，其边数等于顶点数减1，且树内一定不会有环
- 对给定的图G(V,E)，其最小生成树可以不唯一，但其边权之和一定是唯一的

### prim算法
Dijkstra算法和prim算法实际上是相同的思路，只不过是数组d[]的含义不同罢了。

prim算法的基本思想是对图G(V,E)设置集合S来存放已被访问的顶点，然后执行ｎ此下面的两个步骤(n为顶点个数)
1. 每次从集合V-S中选择与集合S最近的一个顶点(记为u)，访问u并将其加入集合S，同时把这条离集合S最近的边加入最小生成树中
2. 令顶点u作为集合S与集合V-S连接的接口，优化从u能到达的未访问顶点v与集合S的最短距离

和Dijkstra算法一样，时间复杂度为$O(V^2)$，其实邻接表实现的prim算法可以通过堆优化使时间复杂度降为O(VlogV+E)。另外$O(V^2)$的时间复杂度也说明，尽量在图的顶点数目少而边数较多的情况下(即稠密图)使用prim算法。
### kruskal算法
采用了“边贪心”的策略，基本思想为：在初始状态时隐去图中的所有边，这样图中每个顶点都自成一个连通块。之后执行下面的步骤：
1. 对所有边按边权从小到大进行排序
2. 按边权从小到大测试所有边，如果当前测试边所连接的两个顶点不在同一个连通块中，则把这条测试边加入当前最小生成树中；否则，将边舍弃。
3. 执行步骤2，直到最小生成树中的边数等于总顶点数减1或是测试完所有边时结束。而当结束时如果最小生成树的边数小于总顶点数减1，说明该图不连通。

```c
struct edge{
    int u, v;//边的两个端点编号
    int cost;//边权
}E[maxe];//最多有maxe条边

bool cmp(edge a, edge b){//让数组E按边权从大到小排序
    return a.cost < b.cost;
}

int kruskal(){
    令最小生成树的边权之和为ans、最小生成树的当前边数Num_Edge;
    将所有边按边权从小到大排序;
    for(从小到大枚举所有边){
        if(当前测试边的两个端点在不同的连通块中){
            将该测试边加入最小生成树中;
            ans += 测试边的边权;
            最小生成树的当前边数Num_Edge加1;
            当边数Num_Edge等于顶点数减1时结束循环;
        }
    }
    return ans;
}
```
1. 如何判断测试边的两个端点是否在不同的连通块中
2. 如何将测试边加入最小生成树中

把每个连通块当作一个集合，问题转换为判断两个端点是否在同一个集合中——并查集，通过并查集的查询操作来解决第一个问题；把测试边的两个端点所在集合合并，就能达到将边加入最小生成树的效果。

时间复杂度是$O(ElogE)$，其中E为图的边数。kruskal适合顶点数较多，边数较少的情况(稀疏图)。

## 拓扑排序
拓扑排序时将有向无环图G的所有顶点排成一个线性序列，使得对图G中的任意两个顶点u、v，如果存在边u->v，那么在序列中u一定在v前面。这个序列又叫拓扑序列。

原理：如果某一门课没有先导课程或是所有先导课程都已经学习完毕，那么这门课就可以学习了。如果有多门这样的课，那它们的学习顺序任意。对应到图中的求解方法：
1. 定义一个队列q，并把所有入度为0的结点加入队列。
2. 取队首结点，输出。然后删除所有从它出发的边，并令这些边到达的顶点的入度减1，如果某个顶点的入度减为0，则将其加入队列
3. 反复进行步骤2操作，直到队列为空。如果队列为空时入过队的结点数目恰好为N，说明拓扑排序成功，图G为有向无环图；否则，拓扑排序失败，图G中有环。

用邻接表实现拓扑排序，额外建立一个数组inDegree[maxv]来记录结点的入度，并在程序一开始读入图时记录好每个结点的入度。

拓扑排序很重要的应用是判断一个给定的图是否是有向无环图。如果返回true，说明是有向无环图。

注意，如果要求有多个入度为0的顶点，选择编号最小的顶点，那么把queue改成priority_queue，并保持队首元素(堆顶元素)是优先队列中最小的元素即可(用set也可以)。


## 关键路径
- 顶点活动（Activity On Vertex, AOV）网是指用顶点表示活动，而用边集表示活动间优先关系的有向图。
- 边活动（Activity On Edge, AOE）网是指用带权的边集表示活动，而用顶点表示事件的有向图，其中边权表示完成活动需要的时间

求解有向无环图(DAG)最长路径(关键路径)的方法：先求点，再夹边。

- 由于关键活动是那些不允许拖延的活动，因此这些活动的最早开始时间必须等于最迟开始时间。因此可以设置数组e和l，其中`e[r]`和`l[r]`分别表示活动$a_r$的最早开始时间和最迟开始时间。于是，求出这两个数组后，就可以通过判断e[r]==l[r]是否成立来确定活动r是否是关键活动。
- 求解数组e和l：事件(顶点)$V_i$经过活动(边)$a_r$之后到达事件$V_j$，事件的最早发生时间可以理解成旧活动的最早结束时间，事件的最迟发生时间可以理解成新活动的最迟开始事件。设置数组ve和vl，其中`ve[i]`和`vl[i]`分别表示事件i的最早发生时间和最迟发生时间，然后就可以将求解`e[r]`和`l[r]`转换成求解这两个新的数组。
  - 对活动(边)$a_r$来说，只要在事件(顶点)$V_i$最早发生时马上开始，就可以使得活动$a_r$的开始时间最早，因此`e[r]=ve[i]`。
  - 如果`l[r]`是活动$a_r$的最迟发生时间，那么`l[r]+length[r]`就是事件$V_j$的最迟发生时间(length[r]表示活动$a_r$的边权)。因此`l[r] = vl[j] - length[r]`。

步骤总结：
1. 按拓扑排序和逆拓排序分别计算各顶点(时间)的最早发生时间和最迟发生时间
2. 用上面的结果计算各边(活动)的最早发生时间和最迟发生时间
3. e[i->j]=l[1->j]的活动即为关键活动







#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
const int maxn = 100010;

int n, minDepth = maxn, num = 0;
double p, r, ans;
vector<int> node[maxn];

void DFS(int index, int depth){
    if(node[index].size() == 0){
        if(depth < minDepth){
            minDepth = depth;
            num = 1;
        }else if(depth == minDepth){
            num++;
        }
        return;
    }
    for (int i = 0; i < node[index].size(); i++)
    {
        DFS(node[index][i], depth + 1);
    }    
}

int main(){
    scanf("%d%lf%lf", &n, &p, &r);
    r = r / 100;
    int k, child;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &k);
        if(k != 0){
            for (int j = 0; j < k; j++)
            {
                scanf("%d", &child);
                node[i].push_back(child);
            }
        }
    }
    DFS(0, 0);
    ans = p * pow(1 + r, minDepth);
    printf("%.4f %d\n", ans, num);
    return 0;
}
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 1001;

struct Mouse{
    int weight;
    int rank;
} mouse[maxn];

int main(){
    int np, ng, order;
    queue<int> q;
    scanf("%d%d", &np,&ng);
    for (int i = 0; i < np; i++)
    {
        scanf("%d", &mouse[i].weight);
    }
    for (int i = 0; i < np; i++)
    {
        scanf("%d", &order);
        q.push(order);
    }
    int temp = np,group;//temp表示当前轮次的老鼠数,group表示老鼠分成的组数，当前轮排名为group+1
    while(q.size()!=1){//每一轮循环
        if(temp % ng == 0){
            group = temp / ng;
        }else{
            group = temp / ng + 1;
        }
        for (int i = 0; i < group; i++)//每一组循环
        {
            int max = q.front();//max记录本轮最大老鼠的order
            for (int j = 0; j < ng; j++){
                if(temp > 0){//可能不能整除
                    mouse[q.front()].rank = group + 1;
                    if(mouse[q.front()].weight > mouse[max].weight){
                        max = q.front();
                    }
                    q.pop();
                    temp--;
                }
                                
            }
            q.push(max);
        }
        temp = group;//不要忘记更新每轮老鼠数目
    }
    mouse[q.front()].rank = 1;
    for (int i = 0; i < np; i++)
    {
        if(i>0){
            printf(" %d", mouse[i].rank);
        }else{
            printf("%d", mouse[i].rank);
        }
    }
    

}
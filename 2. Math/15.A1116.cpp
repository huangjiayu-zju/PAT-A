#include<cstdio>
const int maxn = 10010;
int IDtoAward[maxn] = {0};//每个ID对应的奖项编号，初始化为0，表示不在排名中
char award[5][20] = {"Are you kidding?", "Mystery Award", "Minion", "Chocolate", "Checked"};
bool isPrime(int x){
    if(x <= 1){
        return false;
    }
    for (int i = 2; i * i <= x; i++){
        if(x % i == 0){
            return false;
        }
    }
    return true;
}

int main(){
    int n, ID;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &ID);
        if(i == 1){
            IDtoAward[ID] = 1;
        } else if(isPrime(i)){
            IDtoAward[ID] = 2;
        } else{
            IDtoAward[ID] = 3;
        }
    }
    
    int m, queryID;
    scanf("%d", &m);
    for (int i = 0; i < m; i++){
        scanf("%d", &queryID);
        printf("%04d: %s\n", queryID, award[IDtoAward[queryID]]);
        if(IDtoAward[queryID]){
            IDtoAward[queryID] = 4;
        }
    }
    return 0;
}
#include<cstdio>
const int N = 54;
char mp[5] = {'S', 'H', 'C', 'D', 'J'};//牌的编号与花色的对应关系
int start[N + 1], end[N + 1], next[N + 1];//start[i]表示操作前第i个位置的编号，next[]存放每个位置上的牌在操作后的位置

int main(){
    int K;
    scanf("%d", &K);
    for (int i = 1; i <= N; i++)
    {
        start[i] = i;   //初始化牌的编号
    }
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &next[i]);  //输入每个位置上的牌在操作后的位置
    }
    for (int step = 0; step < K; step++)
    {
        for (int i = 1; i <= N; i++)
        {
            end[next[i]] = start[i];   //把第i个位置的牌编号存放于位置next[i]
        }
        for (int i = 1; i <= N; i++)
        {
            start[i] = end[i];  //把数组end赋值给start数组以供下次操作使用
        }        
    }
    for (int i = 1; i <= N; i++){
        if(i != 1){
            printf(" ");
        }
        start[i]--; //牌号为x，mp[(x-1)/13]为这张牌对应的花色
        printf("%c%d", mp[start[i] / 13], start[i] % 13 + 1);
    }
    return 0;
}
#include <cstdio>
using namespace std;
const int maxn = 100010;
int sum[maxn];//表示从A[1]到A[i]的和值，严格递增
int n,S,nearS=100000010;//nearS是大于等于S的最接近S的和值

int upper_bound(int l,int r,int x){//在[l,R)中找到大于x的第一个位置
    int mid;
    while(l<r){
        mid = (l+r)/2;
        if(sum[mid]>x){
            r = mid;
        }
        else{
            l = mid+1;
        }
    }
    return l;
}

int main(){
    sum[0] = 0;
    scanf("%d%d",&n,&S);
    for (int i = 1; i <= n; i++)//序列下标以1开始
    {
        scanf("%d",&sum[i]);
        sum[i]+=sum[i-1];
    }
    for (int i = 1; i <= n; i++)//这个循环找出最接近S的nearS
    {
        int j = upper_bound(i,n+1,sum[i-1]+S);//求右端点，注意是n+1
        if(sum[j-1]-sum[i-1]==S){//查找成功，注意是j-1，因为sum[j]-sum[i-1]一定大于S
            nearS = S;//最接近S值的就是S
            break;//说明存在和为S的子序列，跳出循环，直接输出结果
        }
        else if(j<=n&&sum[j]-sum[i-1]<nearS){//存在大于S的解并小于nearS
            nearS = sum[j]-sum[i-1];//更新nearS
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int j = upper_bound(i,n+1,sum[i-1]+nearS);
        if(sum[j-1]-sum[i-1]==nearS){
            printf("%d-%d\n",i,j-1);//注意是j-1不是j
        }
    }
    return 0;
    

    
}
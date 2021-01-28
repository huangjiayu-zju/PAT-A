#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100010;//编号上限0-99999
const int maxm = 10010;//派对中人数上限
int coupleID[maxn];//伴侣编号
bool isInParty[maxn]={false};//标记每个ID是否在派对中
int numSingleDog=0, singleDog[maxm];//单身狗数量，单身狗数组

int main(){
    int n,m,ID;//情侣对数、派对人数、某个派对人ID
    scanf("%d",&n);
    memset(coupleID,-1,sizeof(coupleID));//情侣数组初始化为-1表示没有情侣
    for (int i = 0; i < n; i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        coupleID[a] = b;
        coupleID[b] = a;
    }
    scanf("%d",&m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d",&ID);
        isInParty[ID]=true;
    }
    for (int i = 0; i < maxn; i++)//遍历所有编号
    {//如果编号i在派对中，并且他没有伴侣或者伴侣不在派对中
        if(isInParty[i]&&(coupleID[i]==-1||isInParty[coupleID[i]]==false)){
            singleDog[numSingleDog++]=i;
        }    
    }
    sort(singleDog,singleDog+numSingleDog);//sort默认从小到大排序
    printf("%d\n",numSingleDog);
    for (int i = 0; i < numSingleDog ; i++)
    {
        printf("%05d",singleDog[i]);
        if(i<numSingleDog-1){
            printf(" ");
        }
    }
    return 0;   
}


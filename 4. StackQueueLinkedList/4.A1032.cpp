 #include<cstdio>
 #include<cstring>
using namespace std;
const int maxn = 100010;

struct Node{
    char data;
    int next;
    bool flag;//结点是否在第一条链表中出现
} node[maxn];

int main(){
    for (int i = 0; i < maxn; i++)
    {
        node[i].flag = false;
    }
    int s1,s2,n; 
    scanf("%d%d%d", &s1,&s2,&n);
    int address,next;
    char data;
    for (int i = 0; i < n; i++)
    {
        scanf("%d %c %d", &address, &data, &next);//scanf使用%c格式时可以读入空格，因此这里不能写成%d%c%d
        node[address].data = data;
        node[address].next = next;
    }
    int p = s1;
    while(p!=-1){
        node[p].flag = true;
        p = node[p].next;
    }
    p = s2;
    while(p!=-1){
        if(node[p].flag == 1){
            break;
        }
        p = node[p].next;
    }
    if(p!=-1){
        printf("%05d\n",p); 
    }else{
        printf("-1\n");
    }
    return 0;
    
}
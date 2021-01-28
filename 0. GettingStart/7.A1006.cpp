#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

struct pNode{
    char id[20];
    int hh, mm, ss;
} temp, ans1, ans2;//ans1存放最早签到时间，ans2存放最晚签到时间

bool great(pNode node1, pNode node2){
    if(node1.hh != node2.hh){
        return node1.hh > node2.hh;
    }
    if(node1.mm != node2.mm){
        return node1.mm > node2.mm;
    }
    return node1.ss > node2.ss;
}

int main(){
    int n;
    scanf("%d", &n);
    ans1.hh = 24, ans1.mm = 60, ans1.ss = 60;//把初始签到时间设成最大
    ans2.hh = 0, ans2.mm = 0, ans2.ss = 0;//把最晚签退时间设成最小
    for (int i = 0; i < n; i++){
        scanf("%s %d:%d:%d", &temp.id, &temp.hh, &temp.mm, &temp.ss);
        if(great(temp,ans1) == false){
            ans1 = temp;
        }
        scanf("%d:%d:%d", &temp.hh, &temp.mm, &temp.ss);
        if(great(temp,ans2) == true){
            ans2 = temp;
        }
    }
    printf("%s %s\n", ans1.id, ans2.id);
    return 0;
}
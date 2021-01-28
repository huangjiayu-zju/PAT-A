#include<iostream>
#include<string>
#include<map>
using namespace std;
const int maxn = 2010; //通话记录最多1000条

map<string, int> stringToInt;//姓名->编号
map<int, string> intToString;//编号->姓名
map<string, int> Gang;//团伙头id->人数
int G[maxn][maxn] = {0}, weight[maxn] = {0};//邻接矩阵G，点权weight
int n, k, numPerson = 0;//边数、下限、总人数
bool vis[maxn] = {false};//标记是否被访问

int change(string str){
    if(stringToInt.find(str) != stringToInt.end()){// 如果str已经出现过，则返回编号
        return stringToInt[str];
    }
    else{
        stringToInt[str] = numPerson;
        intToString[numPerson] = str;
        return numPerson++;
    }
}

//遍历单个连通块，nowVisit为当前访问编号，head为头目，numMember为成员人数，totalValue为连通块的总边权
void DFS(int nowVisit, int &head, int &numMember, int &totalValue){
    numMember++;    //成员人数加1
    vis[nowVisit] = true;   //标记为已访问
    if (weight[nowVisit] > weight[head]){   //更新头目
        head = nowVisit;
    }
    for (int i = 0; i < numPerson; i++) //枚举所有人
    {
        if(G[nowVisit][i] > 0){ 
            totalValue += G[nowVisit][i];   //更新总边权
            G[nowVisit][i] = G[i][nowVisit] = 0;    //删除这条边防止回头
            if(vis[i] == false){    //如果i未被访问，递归访问i
                DFS(i, head, numMember, totalValue);
            }
        }
    }
    
}

//遍历整个图，获取每个连通块信息
void DFSTrave(){
    for (int i = 0; i < numPerson; i++)
    {
        if(vis[i] == false){
            int head = i, numMember = 0, totalValue = 0;    //头目、成员数、总边权
            DFS(i, head, numMember, totalValue);    //遍历i所在的连通块
            if(numMember > 2 && totalValue > k){
                Gang[intToString[head]] = numMember;    //记录团伙信息
            }   
        }
    }
    
}

int main(){
    int w;
    string str1, str2;
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        cin >> str1 >> str2 >> w;
        int id1 = change(str1);
        int id2 = change(str2);
        weight[id1] += w;
        weight[id2] += w;
        G[id1][id2] += w;
        G[id2][id1] += w;
    }
    DFSTrave();//遍历整个图的所有连通块，获取Gang的信息
    cout << Gang.size() << endl;
    for (map<string, int>::iterator it = Gang.begin(); it != Gang.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}
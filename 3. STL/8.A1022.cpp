#include<iostream>
#include<cstdio>
#include<map>
#include<set>
#include<string>
using namespace std;

map<string, set<int>> mpTitle, mpAuthor, mpKey, mpPub, mpYear;

void query(map<string, set<int> >& mp, string& str){//在mp中查找str, 字符串和map作为参数最好加上引用，提高传递速度
    if(mp.find(str) == mp.end()){//找不到
        printf("Not Found\n");
    }
    else{
        for (set<int>::iterator it = mp[str].begin(); it != mp[str].end(); it++){
            printf("%07d\n", *it);
        }
    }
}

int main(){
    int n,m,id,type;
    string title,author,key,pub,year;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &id);
        char c = getchar();//接受掉id后的换行符
        getline(cin, title);
        mpTitle[title].insert(id);
        getline(cin, author);
        mpAuthor[author].insert(id);
        //读入一行会有多个关键词，需要特别处理
        while(cin>>key){
            mpKey[key].insert(id);
            c = getchar();//接受key之后的字符，空格或者是换行符
            if(c == '\n'){
                break;
            }
        }
        getline(cin, pub);
        mpPub[pub].insert(id);
        getline(cin, year);
        mpYear[year].insert(id);
    }
    string temp;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d: ", &type);
        getline(cin, temp);
        cout << type << ": " << temp << endl;
        if(type==1){
            query(mpTitle, temp);
        }
        else if(type==2){
            query(mpAuthor, temp);
        }
        else if(type==3){
            query(mpKey, temp);
        }
        else if(type==4){
            query(mpPub, temp);
        }
        else{
            query(mpYear, temp);
        }
    }
    return 0;
}
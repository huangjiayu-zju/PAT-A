#include<cstdio>
#include<cstring>
struct Node{
    char name[20], password[20];
    bool ischange;//true表示password已修改
}T[1010];

//crypt函数判断t的password是否需要修改，如果需要则对其修改并令计数器cnt加1
void crypt(Node& t, int& cnt){//注意加了引用
    int len = strlen(t.password);
    for (int i = 0; i < len; i++)
    {
        if(t.password[i] == '1'){
            t.password[i] = '@';
            t.ischange = true;
        }else if(t.password[i] == '0'){
            t.password[i] = '%';
            t.ischange = true;
        }else if(t.password[i] == 'l'){
            t.password[i] = 'L';
            t.ischange = true;
        }else if(t.password[i] == 'O'){
            t.password[i] = 'o';
            t.ischange = true;
        }
    }
    if(t.ischange){
        cnt++;
    } 
}

int main(){
    int n, cnt;//cnt记录需要修改的password个数
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s", T[i].name, T[i].password);
        T[i].ischange = false;//初始化为false
    }
    for (int i = 0; i < n; i++)
    {
        crypt(T[i], cnt);
    }
    if(cnt == 0){
        if(n == 1){
            printf("There is 1 account and no account is modified");
        }else{
            printf("There are %d accounts and no account is modified", n);
        }
    }else{
        printf("%d\n", cnt);
        for (int i = 0; i < n; i++)
        {
            if(T[i].ischange){
                printf("%s %s\n", T[i].name, T[i].password);
            }
        }
        
    }
    return 0;
}




#include<cstdio>
struct person{
    char name[11];
    char id[11];
    int score;
} M, F, temp;//M为男生最低分数的信息，F为女生最高分数的信息

void init(){
    M.score = 101;//初始化男生最低分为101
    F.score = -1;//初始化女生最高分为-1
}

int main(){
    init();//初始化
    int n;
    char gender;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s %c %s %d", temp.name, &gender, temp.id, &temp.score);
        if(gender == 'M' && temp.score < M.score){
            M = temp;
        }else if(gender == 'F' && temp.score > F.score){
            F = temp;
        }
    }
    if(F.score == -1){//没有女生
        printf("Absent\n");
    }else{
        printf("%s %s\n", F.name, F.id);
    }
    if(M.score == 101){//没有男生
        printf("Absent\n");
    }else{
        printf("%s %s\n", M.name, M.id);
    }
    if(M.score == 101 || F.score == -1){//没有女生或男生
        printf("NA\n");
    }else{
        printf("%d\n", F.score - M.score);
    }
    return 0;
}
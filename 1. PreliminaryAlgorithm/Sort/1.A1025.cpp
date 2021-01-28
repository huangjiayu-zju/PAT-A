#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Student
{
    char id[15];
    int score;
    int location_number;
    int local_rank; //考场排名，非总排名
} stu[30010];       //300*100

bool cmp(Student a, Student b)
{
    if (a.score != b.score)
        return a.score > b.score;
    else
        return strcmp(a.id, b.id) < 0;
}

int main()
{
    int n, k, num = 0; //新定义num为总考生数，记录每个考生数据
    //处理输入数据
    scanf("%d", &n);
    //先处理每个考场内的排名
    for (int i = 1; i <= n; i++) //i为考场号，从1开始
    {
        scanf("%d", &k);
        for (int j = 0; j < k; j++)
        {                                                 //将数据存储进结构体
            scanf("%s %d", stu[num].id, &stu[num].score); //注意这里要加&
            stu[num].location_number = i;
            num++;
        }
        //处理考场内排名
        //sort(stu[num-k],stu[num],cmp);
        sort(stu + num - k, stu + num, cmp);
        //数组排序完成后实现排名的计算，将第一个个体排名记为1，遍历剩余个体
        stu[num - k].local_rank = 1;
        for (int j = num - k + 1; j < num; j++)
        {
            if (stu[j].score == stu[j - 1].score)
                stu[j].local_rank = stu[j - 1].local_rank;
            else
                stu[j].local_rank = j + 1 - (num - k); //这里注意不能写成j+1
        }
    }
    printf("%d\n", num);

    sort(stu, stu + num, cmp);
    //然后输出总排名,先令r为1，然后遍历所有个体
    int r = 1;
    for (int i = 0; i < num; i++)
    { //如果不是第一个个体且当前分数不等于上一个个体的分数，则更新排名r
        if (i > 0 && stu[i].score != stu[i - 1].score)
            r = i + 1;
        //如果是第一个或者等于上一个个体分数，则直接输出r即可
        printf("%s %d %d %d\n", stu[i].id, r, stu[i].location_number, stu[i].local_rank);
    }

    return 0;
}
